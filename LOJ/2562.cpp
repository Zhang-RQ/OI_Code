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

const int MAXN=2E5+10;

int n,m,q,tot;
vector<int> G[MAXN],T[MAXN];

namespace Graph{
	int dfn[MAXN],low[MAXN],dft,stk[MAXN],top;

	void tarjan(int x,int fa)
	{
		stk[++top]=x;
		dfn[x]=low[x]=++dft;
		for(int v:G[x])
		{
			if(v==fa) continue;
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
	int dfn[MAXN],siz[MAXN],dep[MAXN],depv[MAXN],jmp[MAXN][19];
	int pnt[MAXN],cnt,stk[MAXN],top,dft;

	void dfs(int x,int fa)
	{
		siz[x]=1;
		jmp[x][0]=fa;
		dep[x]=dep[fa]+1;
		depv[x]=depv[fa]+(x<=n);
		dfn[x]=++dft;
		for(int v:T[x])
			if(v!=fa)
				dfs(v,x),siz[x]+=siz[v];
	}

	int LCA(int x,int y)
	{
		if(dep[x]<dep[y]) swap(x,y);
		for(int j=18;~j;j--)
			if(dep[jmp[x][j]]>=dep[y])
				x=jmp[x][j];
		if(x==y) return x;
		for(int j=18;~j;j--)
			if(jmp[x][j]!=jmp[y][j])
				x=jmp[x][j],y=jmp[y][j];
		return jmp[x][0];
	}

	bool cmp(int x,int y){return dfn[x]<dfn[y];}

	bool inside(int x,int y){return dfn[y]<=dfn[x]&&dfn[x]<=dfn[y]+siz[y]-1;}//x in y

	void init()
	{
		dfs(1,0);
		for(int j=1;j<=18;j++)
			for(int i=1;i<=n;i++)
				jmp[i][j]=jmp[jmp[i][j-1]][j-1];
	}

	int solve()
	{
		int _cnt=cnt,Ret=0;
		sort(pnt+1,pnt+1+cnt,cmp);
		cnt=unique(pnt+1,pnt+1+cnt)-pnt-1;
		for(int i=cnt-1;i;i--)
			pnt[++cnt]=LCA(pnt[i],pnt[i+1]);
		sort(pnt+1,pnt+1+cnt,cmp);
		cnt=unique(pnt+1,pnt+1+cnt)-pnt-1;
		stk[top=1]=pnt[1];
		for(int i=2;i<=cnt;i++)
		{
			while(top&&!inside(pnt[i],stk[top])) --top;
			Ret+=depv[pnt[i]]-depv[stk[top]];
			stk[++top]=pnt[i];
		}
		return Ret-_cnt+(pnt[1]<=n);
	}
}

void clear()
{
	for(int i=1;i<=tot;i++) T[i].clear(),G[i].clear();
	Graph::dft=tot=Graph::top=Tree::dft=0;
	memset(Graph::dfn,0,sizeof Graph::dfn);
}

void solve()
{
	read(n,m);tot=n;
	for(int i=1,u,v;i<=m;i++) read(u,v),G[u].push_back(v),G[v].push_back(u);
	Graph::tarjan(1,0);Tree::init();
	read(q);
	for(int i=1,s;i<=q;i++)
	{
		read(s);
		Tree::cnt=s;
		for(int j=1;j<=s;j++) read(Tree::pnt[j]);
		printf("%d\n",Tree::solve());
	}
	clear();
}

int main()
{
	int T;
	for(read(T);T--;solve());
}