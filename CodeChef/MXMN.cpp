#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int P=998244353;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

struct edge_t{
	int u,v,w;

	bool operator < (const edge_t &rhs) const {return w<rhs.w;}
}E1[MAXN],E2[MAXN];

int n,m,cnt1,cnt2,fa1[MAXN],fa2[MAXN];
ll Ans;

int find1(int x){return fa1[x]==x?x:fa1[x]=find1(fa1[x]);}

int find2(int x){return fa2[x]==x?x:fa2[x]=find2(fa2[x]);}

namespace T2{
	struct node_t{
		int l,r,siz;
		ll val;
	}t[MAXN*100];
	
	vector<int> T[MAXN];
	int siz[MAXN],Fa[MAXN],vis[MAXN],rt,mx_rt,cnt,ref[MAXN],fa_pnt[MAXN],son_pnt[MAXN];
	int st[20][MAXN<<1],lca[20][MAXN<<1],lg2[MAXN<<1],dft,pos[MAXN],anc[MAXN],val[MAXN];
	int DCT_rt;

	void dfs(int x,int fa,int dep)
	{
		lca[0][pos[x]=++dft]=x;
		st[0][pos[x]]=dep;
		for(int v:T[x])
			if(v!=fa)
			{
				dfs(v,x,dep+1);
				lca[0][++dft]=x;
				st[0][dft]=dep;
			}
	}

	int LCA(int x,int y)
	{
		x=pos[x];y=pos[y];
		if(x>y)
			swap(x,y);
		int len=lg2[y-x+1];
		return st[len][x]<st[len][y-(1<<len)+1]?lca[len][x]:lca[len][y-(1<<len)+1];
	}
	
	bool chk(int u,int v){return Fa[v]==u?vis[v]:vis[u];}

	void get_rt(int x,int fa,int sz)
	{
		siz[x]=1;
		for(int v:T[x])
			if(v!=fa&&!chk(x,v))
				get_rt(v,x,sz),siz[x]+=siz[v];
		int mx=max(siz[x],sz-siz[x]);
		if(!vis[x]&&Fa[x]&&mx<mx_rt)
			mx_rt=mx,rt=x;
	}

	int construct(int x)
	{
		vis[x]=1;
		int now=++cnt;
		ref[x]=ref[Fa[x]]=now;
		mx_rt=1<<30,rt=-1;
		fa_pnt[now]=Fa[x];
		get_rt(x,0,siz[x]);
		if(~rt)
			t[now].r=construct(rt),anc[t[now].r]=now;
		mx_rt=1<<30,rt=-1;
		get_rt(Fa[x],0,siz[Fa[x]]);
		if(~rt)
			t[now].l=construct(rt),anc[t[now].l]=now;
		return now;
	}

	int insert(int p)
	{
		int x=ref[p],ret=++cnt;
		if(p==fa_pnt[x])
			t[ret].val=val[p];
		else
			t[ret].siz=1;
		while(anc[x])
		{
			int tmp=++cnt;
			if(x==t[anc[x]].l)
			{
				t[tmp].l=ret;
				t[tmp].val+=val[LCA(p,fa_pnt[anc[x]])];
				ret=tmp;
			}
			else
			{
				t[tmp].r=ret;
				t[tmp].siz++;
				ret=tmp;
			}
			x=anc[x];
		}
		return ret;
	}

	int merge(int x,int y,ll exv)
	{
		if(!x||!y)
			return x|y;
		Inc(Ans,1ll*t[x].siz*t[y].val%P*exv%P);
		Inc(Ans,1ll*t[y].siz*t[x].val%P*exv%P);
		t[x].siz+=t[y].siz;
		Inc(t[x].val,t[y].val);
		t[x].l=merge(t[x].l,t[y].l,exv);
		t[x].r=merge(t[x].r,t[y].r,exv);
		return x;
	}

	void init(int root)
	{
		dfs(root,0,1);
		for(int i=2;i<=dft;i++)
			lg2[i]=lg2[i>>1]+1;
		for(int j=1;j<=lg2[dft];j++)
			for(int i=1;i+(1<<j)-1<=dft;i++)
				if(st[j-1][i]<st[j-1][i+(1<<(j-1))])
					st[j][i]=st[j-1][i],lca[j][i]=lca[j-1][i];
				else
					st[j][i]=st[j-1][i+(1<<(j-1))],
					lca[j][i]=lca[j-1][i+(1<<(j-1))];
		mx_rt=1<<30;rt=-1;
		get_rt(root,0,cnt2);
		DCT_rt=construct(rt);
	}
}

namespace T1{
	vector<int> T[MAXN];
	ll val[MAXN];

	int dfs(int x,int fa)
	{
		int p=x<=n?T2::insert(x):0;
		for(int v:T[x])
			if(v!=fa)
				p=T2::merge(p,dfs(v,x),val[x]);
		return p;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=2*n;i++)
		fa1[i]=fa2[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&E1[i].u,&E1[i].v,&E1[i].w);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&E2[i].u,&E2[i].v,&E2[i].w);
	sort(E1+1,E1+m+1);sort(E2+1,E2+m+1);
	cnt1=cnt2=n;
	for(int i=1;i<=m;i++)
	{
		int x=find1(E1[i].u),y=find1(E1[i].v);
		if(x!=y)
		{
			++cnt1;T1::val[cnt1]=E1[i].w;
			T1::T[cnt1].push_back(x);
			T1::T[cnt1].push_back(y);
			T1::T[x].push_back(cnt1);
			T1::T[y].push_back(cnt1);
			fa1[x]=fa1[y]=cnt1;
		}
	}
	for(int i=1;i<=m;i++)
	{
		int x=find2(E2[i].u),y=find2(E2[i].v);
		if(x!=y)
		{
			++cnt2;T2::val[cnt2]=E2[i].w;
			T2::T[cnt2].push_back(x);
			T2::T[cnt2].push_back(y);
			T2::T[x].push_back(cnt2);
			T2::T[y].push_back(cnt2);
			T2::Fa[x]=T2::Fa[y]=cnt2;
			fa2[x]=fa2[y]=cnt2;
		}
	}
	int rt1=find1(1),rt2=find2(1);
	T2::init(rt2);T1::dfs(rt1,0);
	printf("%lld\n",Ans);
}
