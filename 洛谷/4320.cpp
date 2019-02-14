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

const int MAXN=1E6+10;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
	inline void read(T& x)
	{
		x=0;static char ch=get_char();
		while(!isdigit(ch)) ch=get_char();
		while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
	}

#if __cplusplus >= 201103L
	template<typename T,typename ...Args>
	inline void read(T& x,Args& ...args)
	{
		read(x);
		read(args...);
	}
#endif
}

using namespace FastIO;

int n,e,q,tot;
vector<int> G[MAXN],T[MAXN];

namespace Graph{
	int dfn[MAXN],low[MAXN],dft,stk[MAXN],top;

	void tarjan(int x,int fa)
	{
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
						T[x].push_back(tot);
						T[tot].push_back(x);
					}
				}
			}
	}
}

namespace Tree{
	int dep[MAXN],sum[MAXN],siz[MAXN],son[MAXN],top[MAXN],fa[MAXN];

	void dfs1(int x,int fa)
	{
		Tree::fa[x]=fa;
		siz[x]=1;
		sum[x]=sum[fa]+(x<=n);
		dep[x]=dep[fa]+1;
		for(int v:T[x])
			if(v!=fa)
			{
				dfs1(v,x);
				siz[x]+=siz[v];
				if(siz[son[x]]<siz[v]) son[x]=v;
			}
	}

	void dfs2(int x,int tp)
	{
		top[x]=tp;
		if(son[x]) dfs2(son[x],tp);
		for(int v:T[x])
			if(v!=son[x]&&v!=fa[x])
				dfs2(v,v);
	}

	int LCA(int x,int y)
	{
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		return x;
	}

	void init()
	{
		dfs1(1,0);dfs2(1,1);
	}
}

int main()
{
	read(n,e);tot=n;
	for(int i=1,u,v;i<=e;i++) read(u,v),G[u].push_back(v),G[v].push_back(u);
	Graph::tarjan(1,0);Tree::init();
	read(q);
	for(int i=1,u,v;i<=q;i++)
	{
		read(u,v);
		int LCA=Tree::LCA(u,v);
		printf("%d\n",Tree::sum[u]+Tree::sum[v]-Tree::sum[LCA]-Tree::sum[Tree::fa[LCA]]);
	}
}
