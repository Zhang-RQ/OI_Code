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

const int MAXN=1010;
const int MAXM=2010;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN],cnt_e,n,b,tot,col[MAXN];
int stk[MAXN],top,cap[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	int bot=top;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs(v,x);
		if(top-bot>=b)
		{
			++tot;cap[tot]=x;
			while(top!=bot) col[stk[top--]]=tot; 
		}
	}
	stk[++top]=x;
}

int main()
{
	scanf("%d%d",&n,&b);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfs(1,0);
	while(top) col[stk[top--]]=tot;
	printf("%d\n",tot);
	for(int i=1;i<=n;i++) printf("%d%c",col[i],i==n?'\n':' ');
	for(int i=1;i<=tot;i++) printf("%d%c",cap[i],i==tot?'\n':' ');
}