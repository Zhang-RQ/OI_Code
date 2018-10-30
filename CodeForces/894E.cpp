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
const int MAXM=1E6+10;

struct Graph{
	struct __edge{
		int nxt,v,w;
	}Edge[MAXM];

	int head[MAXN],cnt_e;

	inline void add(int u,int v,int w)
	{
		Edge[++cnt_e].v=v;
		Edge[cnt_e].nxt=head[u];
		Edge[cnt_e].w=w;
		head[u]=cnt_e;
	}
}G,Ge;

struct T{
	int u,v,w;
	T(int _u=0,int _v=0,int _w=0){u=_u;v=_v;w=_w;}
};

vector<T> E;
int n,m,dfn[MAXN],bl[MAXN],low[MAXN],dft,stk[MAXN],top,SCC,d[MAXN];
bool ins[MAXN];
ll val[MAXN],f[MAXN];

void tarjan(int x)
{
	low[x]=dfn[x]=++dft;stk[++top]=x;ins[x]=1;
	for(int i=Ge.head[x];i;i=Ge.Edge[i].nxt)
	{
		int v=Ge.Edge[i].v;
		if(!dfn[v]) tarjan(v),low[x]=min(low[v],low[x]);
		else if(ins[v]) low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		++SCC;
		while(stk[top]!=x)
		{
			ins[stk[top]]=0;
			bl[stk[top--]]=SCC;
		}
		top--;
		ins[x]=0;bl[x]=SCC;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		Ge.add(u,v,w);E.push_back(T(u,v,w));
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(T e:E)
		if(bl[e.u]==bl[e.v])
		{
			int k=floor((sqrt(1+8*e.w)-1)/2);
			val[bl[e.u]]+=e.w-1ll*k*(k+1)/2;
			val[bl[e.u]]+=1ll*e.w*k-(1ll*k*(k+1)*(2*k+1)/6-1ll*k*(k+1)/2)/2;
		}
		else G.add(bl[e.v],bl[e.u],e.w),++d[bl[e.u]];
	int s;
	scanf("%d",&s);
	queue<int> q;
	for(int i=1;i<=SCC;i++)
		if(!d[i]) q.push(i);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		f[x]+=val[x];
		for(int i=G.head[x];i;i=G.Edge[i].nxt)
		{
			int v=G.Edge[i].v;
			f[v]=max(f[v],f[x]+G.Edge[i].w);
			if(!--d[v]) q.push(v);
		}
	}
	printf("%lld\n",f[bl[s]]);
}