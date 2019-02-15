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

ll tAns,Ans[MAXN],tag[MAXN];
int n,m,tot,bl[MAXN];
vector<int> G[MAXN],T[MAXN],C[MAXN*5],rt;

namespace Graph{
	int dfn[MAXN],low[MAXN],dft,stk[MAXN],top;

	void tarjan(int x,int fa)
	{
		if(!fa) bl[x]=x;
		else bl[x]=bl[fa];
		stk[++top]=x;
		dfn[x]=low[x]=++dft;
		for(int v:G[x])
			if(v!=fa)
			{
				if(dfn[v]) low[x]=min(low[x],dfn[v]);
				else
				{
					tarjan(v,x);
					low[x]=min(low[x],low[v]);
					if(low[v]>=dfn[x])
					{
						++tot;
						do{
							T[stk[top]].push_back(tot);
							T[tot].push_back(stk[top]);
							--top;
						}while(stk[top+1]!=v);
						T[tot].push_back(x);
						T[x].push_back(tot);
					}
				}
			}
	}
}

namespace Tree{
	int tot,cnt,pnt[MAXN],stk[MAXN],top,Fa[MAXN],rl[MAXN];
	int st[MAXN<<1][21],st_lca[MAXN<<1][21],lg2[MAXN<<1],pos[MAXN],dfn[MAXN],siz[MAXN],vsiz[MAXN],dft,dft2;
	ll siz2[MAXN];

	void dfs(int x,int fa,int dep)
	{
		Fa[x]=fa;
		siz[x]=1;
		dfn[x]=++dft2;
		pos[x]=++dft;
		st[dft][0]=dep;
		st_lca[dft][0]=x;
		for(int v:T[x])
			if(v!=fa)
			{
				dfs(v,x,dep+1);
				++dft;
				st[dft][0]=dep;
				st_lca[dft][0]=x;
				siz[x]+=siz[v];
			}
	}

	void dfs2(int x,int fa)
	{
		for(int v:T[x])
			if(v!=fa)
				dfs2(v,x),tag[x]+=tag[v];
		Ans[x]+=tag[x];
	}

	void init()
	{
		for(int x:rt) dfs(x,0,1);
		for(int i=2;i<=dft;i++) lg2[i]=lg2[i>>1]+1;
		for(int j=1;j<=lg2[dft];j++)
			for(int i=1;i+(1<<j)<=dft+1;i++)
				if(st[i][j-1]<st[i+(1<<(j-1))][j-1])
					st[i][j]=st[i][j-1],st_lca[i][j]=st_lca[i][j-1];
		        else st[i][j]=st[i+(1<<(j-1))][j-1],st_lca[i][j]=st_lca[i+(1<<(j-1))][j-1];
	}

	void afterwork()
	{
		for(int x:rt) dfs2(x,0);
	}

	int LCA(int x,int y)
	{
		x=pos[x],y=pos[y];
		if(x>y) swap(x,y);
		int len=lg2[y-x+1];
		return st[x][len]<st[y-(1<<len)+1][len]?st_lca[x][len]:st_lca[y-(1<<len)+1][len];
	}

	bool inside(int x,int y){return dfn[y]<=dfn[x]&&dfn[x]<=dfn[y]+siz[y]-1;}// x in y

	void solve()
	{
		for(int i=1;i<=cnt;i++) vsiz[pnt[i]]=1,rl[pnt[i]]=1;
		tot=cnt;
		sort(pnt+1,pnt+1+tot,[](int x,int y){return pos[x]<pos[y];});
		for(int i=tot-1;i;i--) pnt[++tot]=LCA(pnt[i],pnt[i+1]);
		sort(pnt+1,pnt+1+tot,[](int x,int y){return pos[x]<pos[y];});
		tot=unique(pnt+1,pnt+1+tot)-pnt-1;
		stk[top=1]=pnt[1];
		for(int i=2;i<=tot;i++)
		{
			while(!inside(pnt[i],stk[top]))
			{
				int fa=stk[top-1],x=stk[top];
				tag[Fa[x]]+=1ll*vsiz[x]*(cnt-vsiz[x]);
				tag[fa]-=1ll*vsiz[x]*(cnt-vsiz[x]);
				if(rl[x]) Ans[x]+=cnt-1;
				Ans[x]+=1ll*(vsiz[x]-rl[x])*(cnt-vsiz[x])+(1ll*(vsiz[x]-rl[x])*(vsiz[x]-rl[x])-siz2[x])/2;
				vsiz[fa]+=vsiz[x];
				siz2[fa]+=1ll*vsiz[x]*vsiz[x];
				--top;
			}
			stk[++top]=pnt[i];
		}
		while(top)
		{
			int fa=stk[top-1],x=stk[top];
			if(top>1)
			{
				tag[Fa[x]]+=1ll*vsiz[x]*(cnt-vsiz[x]);
				tag[fa]-=1ll*vsiz[x]*(cnt-vsiz[x]);
			}
			if(rl[x]) Ans[x]+=cnt-1;
			Ans[x]+=1ll*(vsiz[x]-rl[x])*(cnt-vsiz[x])+(1ll*(vsiz[x]-rl[x])*(vsiz[x]-rl[x])-siz2[x])/2;
			vsiz[fa]+=vsiz[x];
			siz2[fa]+=1ll*vsiz[x]*vsiz[x];
			--top;
		}
		for(int i=1;i<=tot;i++) vsiz[pnt[i]]=siz2[pnt[i]]=rl[pnt[i]]=0;
	}
}

using Tree::pnt;
using Tree::cnt;

int main()
 
{
	int Mx=0;
	scanf("%d%d",&n,&m);tot=n;
	for(int i=1,c;i<=n;i++) scanf("%d",&c),Mx=max(Mx,c),C[c].push_back(i);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<=n;i++) if(!Graph::dfn[i]) Graph::tarjan(i,0),rt.push_back(i);
	Tree::init();
	for(int i=1;i<=Mx;i++)
	{
		sort(C[i].begin(),C[i].end(),[](int x,int y){return bl[x]<bl[y];});
		int pcnt=0;
		for(int j=0;j<(int)C[i].size();j++)
		{
			pnt[++cnt]=C[i][j];
			if(j==(int)C[i].size()-1||(bl[C[i][j]]!=bl[C[i][j+1]]))
			{
				tAns+=pcnt*cnt;
				Tree::solve();
				pcnt+=cnt;
				cnt=0;
			}
		}
	}
	Tree::afterwork();
	for(int i=1;i<=n;i++) printf("%lld\n",Ans[i]+tAns);
}
