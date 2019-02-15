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

const int MAXN=1E5+10;

struct GRAPH{
	int head[MAXN],cnt_e;
	struct edge_t{int v,w,nxt;}Edge[MAXN<<1];

	void add(int u,int v,int w)
	{
		Edge[++cnt_e].v=v;
		Edge[cnt_e].w=w;
		Edge[cnt_e].nxt=head[u];
		head[u]=cnt_e;
	}

	int& operator () (int x) {return head[x];}
	edge_t& operator [] (int x) {return Edge[x];}
}T,G;

int n,m,q,tot;
map<int,int> idx[MAXN];
map<pair<int,int>,int> M;
vector<int> PCC[MAXN],pre[MAXN],suf[MAXN];

int Query_val(int u,int v)
{
	if(u>v) swap(u,v);
	return M[make_pair(u,v)];
}

namespace Graph{
	int dfn[MAXN],low[MAXN],dft,stk[MAXN],top;

	void tarjan(int x,int fa)
	{
		stk[++top]=x;
		dfn[x]=low[x]=++dft;
		for(int _=G(x);_;_=G[_].nxt)
		{
			int v=G[_].v;
			if(v!=fa)
			{
				if(dfn[v]) low[x]=min(low[x],dfn[v]);
				else
				{
					tarjan(v,x);
					low[x]=min(low[x],low[v]);
					if(low[v]>=dfn[x])
					{
						if(stk[top]==v) {T.add(x,v,G[_].w),T.add(v,x,G[_].w),--top;continue;}
						++tot;idx[tot][x]=0;
						PCC[tot].push_back(x);
						do{
							idx[tot][stk[top]]=PCC[tot].size();
							PCC[tot].push_back(stk[top]);
							--top;
						}while(stk[top+1]!=v);
					}
				}
			}
		}
	}
}

namespace Tree{
	int jmp[MAXN][18],sum[MAXN][18],dep[MAXN];

	void dfs(int x,int fa)
	{
		dep[x]=dep[fa]+1;
		for(int _=T(x);_;_=T[_].nxt)
		{
			int v=T[_].v;
			if(v==fa) continue;
			sum[v][0]=T[_].w;
			jmp[v][0]=x;
			dfs(v,x);
		}
	}

	void init()
	{
		dfs(1,0);
		for(int j=1;j<=17;j++)
			for(int i=1;i<=tot;i++)
				jmp[i][j]=jmp[jmp[i][j-1]][j-1],
				sum[i][j]=sum[i][j-1]+sum[jmp[i][j-1]][j-1];
	}

	int Query(int x,int y)
	{
		int Ret=0;
		if(dep[x]<dep[y]) swap(x,y);
		for(int j=17;~j;j--)
			if(dep[jmp[x][j]]>=dep[y])
				Ret+=sum[x][j],x=jmp[x][j];
		if(x==y) return Ret;
		for(int j=17;~j;j--)
			if(jmp[x][j]!=jmp[y][j])
				Ret+=sum[x][j],Ret+=sum[y][j],
				x=jmp[x][j],y=jmp[y][j];
		int LCA=jmp[x][0];
		if(LCA>n)
		{
			int L=idx[LCA][x],R=idx[LCA][y];
			if(L>R) swap(L,R);
			Ret+=min(pre[LCA][R]-pre[LCA][L],pre[LCA][L]+suf[LCA][R]);
		}
		else Ret+=sum[x][0]+sum[y][0];
		return Ret;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);tot=n;
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		if(u>v) swap(u,v);
		G.add(u,v,w);G.add(v,u,w);
		M[make_pair(u,v)]=w;
	}
	Graph::tarjan(1,0);
	for(int i=n+1;i<=tot;i++)
	{
		pre[i].resize(PCC[i].size());suf[i].resize(PCC[i].size());
		T.add(PCC[i][0],i,0);T.add(i,PCC[i][0],0);
		pre[i][0]=0;suf[i][PCC[i].size()-1]=Query_val(PCC[i][PCC[i].size()-1],PCC[i][0]);
		for(int _=1;_<(int)PCC[i].size();_++)
			pre[i][_]=pre[i][_-1]+Query_val(PCC[i][_-1],PCC[i][_]);
		for(int _=(int)PCC[i].size()-2;~_;_--)
			suf[i][_]=suf[i][_+1]+Query_val(PCC[i][_+1],PCC[i][_]);
		for(int _=1;_<(int)PCC[i].size();_++)
		{
			int val=min(pre[i][_],suf[i][_]);
			T.add(i,PCC[i][_],val);
			T.add(PCC[i][_],i,val);
		}
	}
	Tree::init();
	for(int i=1,u,v;i<=q;i++)
	{
		scanf("%d%d",&u,&v);
		printf("%d\n",Tree::Query(u,v));
	}
}
