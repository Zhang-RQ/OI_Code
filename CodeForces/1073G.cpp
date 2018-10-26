#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4E5+10;

int n,q,nd[MAXN],a[MAXN],b[MAXN],pnt[MAXN];
char str[MAXN];

namespace SAM{
	int son[MAXN][26],par[MAXN],mx[MAXN];
	int cnt=1,rt=1,lst=1;
	vector<int> g[MAXN];
	
	void insert(int x)
	{
		x-='a';
		int np=++cnt,p=lst;
		mx[np]=mx[p]+1;
		while(p&&!son[p][x]) son[p][x]=np,p=par[p];
		if(!p) par[np]=rt;
		else
		{
			int q=son[p][x];
			if(mx[q]==mx[p]+1) par[np]=q;
			else
			{
				int nq=++cnt;
				mx[nq]=mx[p]+1;
				par[nq]=par[q];
				par[q]=par[np]=nq;
				memcpy(son[nq],son[q],sizeof son[q]);
				while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
			}
		}
		lst=np;
	}

	void init_suffix_tree()
	{
		for(int i=2;i<=cnt;i++)
			g[par[i]].push_back(i);
	}
}

namespace Tree_chain_division{
	using SAM::g;
	int top[MAXN],siz[MAXN],hson[MAXN],dfn[MAXN],dft,dep[MAXN];

	void dfs1(int x)
	{
		siz[x]=1;
		for(int v:g[x])
		{
			dfs1(v);
			if(siz[v]>siz[hson[x]])
				hson[x]=v;
			siz[x]+=siz[v];
		}
	}

	void dfs2(int x,int tp)
	{
		top[x]=tp;dfn[x]=++dft;
		dep[x]=dep[SAM::par[x]]+1;
		if(hson[x]) dfs2(hson[x],tp);
		for(int v:g[x])
			if(v!=hson[x])
				dfs2(v,v);
	}

	void init() {dfs1(SAM::rt);dfs2(SAM::rt,SAM::rt);}

	int LCA(int x,int y)
	{
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			x=SAM::par[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		return x;
	}
}

namespace Virtual_Tree{

	using Tree_chain_division::dfn;
	using Tree_chain_division::siz;
	using Tree_chain_division::LCA;
	
	int stk[MAXN],top,cnta[MAXN],cntb[MAXN],Rt;
	vector<int> vt[MAXN];
	ll Ans=0;

	bool inside(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+siz[x]-1;} // y in x

	void build_Vtree(int tot)
	{
		sort(pnt+1,pnt+1+tot,[](int a,int b)->bool{return dfn[a]<dfn[b];});
		int rtot=tot;
		for(int i=1;i<rtot;i++)
			pnt[++tot]=LCA(pnt[i],pnt[i+1]);
		sort(pnt+1,pnt+1+tot,[](int a,int b)->bool{return dfn[a]<dfn[b];});
		tot=unique(pnt+1,pnt+1+tot)-pnt-1;
		Rt=stk[top=1]=pnt[1];
		for(int i=2;i<=tot;i++)
		{
			while(!inside(stk[top],pnt[i])) --top;
			vt[stk[top]].push_back(pnt[i]);
			stk[++top]=pnt[i];
		}
	}

	void dfs(int x)
	{
		for(int v:vt[x])
			dfs(v),cnta[x]+=cnta[v],cntb[x]+=cntb[v];
		Ans+=1ll*SAM::mx[x]*cnta[x]*cntb[x];
		for(int v:vt[x])
			Ans-=1ll*SAM::mx[x]*cnta[v]*cntb[v];
	}

	void clear(int x)
	{
		for(int v:vt[x])
			clear(v);
		cnta[x]=cntb[x]=0;
		vt[x].clear();
	}

	void solve()
	{
		int k,l,tot=0;Ans=0;
		scanf("%d%d",&k,&l);
		for(int i=1;i<=k;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=l;i++)
			scanf("%d",&b[i]);
		for(int i=1;i<=k;i++)
			pnt[++tot]=nd[a[i]],cnta[nd[a[i]]]++;
		for(int i=1;i<=l;i++)
			pnt[++tot]=nd[b[i]],cntb[nd[b[i]]]++;
		build_Vtree(tot);
		dfs(Rt);clear(Rt);
		printf("%lld\n",Ans);
	}
}

int main()
{
	scanf("%d%d",&n,&q);
	scanf("%s",str+1);
	reverse(str+1,str+1+n);
	for(int i=1;i<=n;i++)
		SAM::insert(str[i]),nd[n-i+1]=SAM::lst;
	SAM::init_suffix_tree();
	Tree_chain_division::init();
	while(q--)
		Virtual_Tree::solve();
}