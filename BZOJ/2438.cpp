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
const int MAXM=3E5+10;

struct __edge{
	int u,v,nxt;
}Edge[MAXM];

vector<int> g[MAXN];
int head[MAXN],cnt_e,bl[MAXN],SCC,n,m,Ans;
int stk[MAXN],top,dfn[MAXN],low[MAXN],dft,siz[MAXN],d[MAXN];
bool ins[MAXN],f;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].u=u;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void tarjan(int x)
{
	stk[++top]=x;ins[x]=1;
	low[x]=dfn[x]=++dft;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
		else if(ins[v]) low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		++SCC;
		while(stk[top]!=x)
		{
			siz[SCC]++;
			bl[stk[top]]=SCC;
			ins[stk[top]]=0;
			--top;
		}
		siz[SCC]++;
		ins[x]=0;
		bl[x]=SCC;
		top--;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),add(u,v);
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=m;i++) if(bl[Edge[i].u]!=bl[Edge[i].v]) g[bl[Edge[i].u]].push_back(bl[Edge[i].v]),++d[bl[Edge[i].v]];
	for(int i=1;i<=SCC;i++)
		if(!d[i]) ++Ans;
	for(int i=1;i<=SCC;i++)
		if(!d[i]&&siz[i]==1)
		{
			bool fl=1;
			for(int j=0;j<g[i].size();j++)
				fl&=d[g[i][j]]>1;
			if(fl) {f=1;break;}
		}
	Ans-=f;
	printf("%lf\n",1-1.0*Ans/n);
}