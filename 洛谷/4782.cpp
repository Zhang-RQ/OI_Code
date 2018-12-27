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

const int MAXN=2E6+10;
const int MAXM=4E6+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN],cnt_e,n,m,low[MAXN],dfn[MAXN],dft,ins[MAXN],stk[MAXN],top,SCC,bl[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
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
			ins[stk[top]]=0;
			bl[stk[top--]]=SCC;
		}
		ins[x]=0;bl[x]=SCC;--top;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,a,b;i<=m;i++)
	{
		scanf("%d%d%d%d",&x,&a,&y,&b);
		a^=1;b^=1;
		add(x+a*n,y+(b^1)*n);add(y+b*n,x+(a^1)*n);
	}
	for(int i=1;i<=2*n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
		if(bl[i]==bl[i+n]) return puts("IMPOSSIBLE"),0;
	puts("POSSIBLE");
	for(int i=1;i<=n;i++)
		printf("%d%c",bl[i]>bl[i+n],i==n?'\n':' ');
}