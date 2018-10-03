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


const int MAXN=2.5E5+10;
const int MAXM=5E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int n,m,t[MAXN<<1],pos1[MAXN],pos2[MAXN],dft;
int head[MAXN],cnt_e;
char s[10];

void adde(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	pos1[x]=++dft;
	for(int i=head[x];i;i=Edge[i].nxt)
		dfs(Edge[i].v,x);
	pos2[x]=++dft;
}

void add(int x,int v)
{
	for(;x<=dft;x+=x&(-x))
		t[x]+=v;
}

int ask(int x)
{
	int ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		if(u>v) swap(u,v);
		adde(u,v);
	}
	dfs(1,0);
	for(int i=2;i<=n;i++) add(pos1[i],1),add(pos2[i],-1);
	scanf("%d",&m);
	for(int i=1,u,v;i<=n+m-1;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='A')
		{
			scanf("%d%d",&u,&v);
			if(u>v) swap(u,v);
			add(pos1[v],-1);add(pos2[v],1);
		}
		else scanf("%d",&u),printf("%d\n",ask(pos1[u]));
	}
}