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

const int MAXN=3E5+10;
const int MAXM=3E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM<<1];

int head[MAXN],cnt_e,cnt,cov[MAXN],unc[MAXN],chk[MAXN],Mid,n,m;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	cov[x]=1<<30;unc[x]=-(1<<30);
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs(v,x);
		cov[x]=min(cov[x],cov[v]+1);
		unc[x]=max(unc[x],unc[v]+1);
	}
	if(chk[x]) unc[x]=max(unc[x],0);
	if(unc[x]==Mid) {++cnt;unc[x]=-(1<<30);cov[x]=0;}
	if(cov[x]+unc[x]<=Mid) unc[x]=-(1<<30);
	if(!fa&&unc[x]>=0) ++cnt;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&chk[i]);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	int L=0,R=n,Ans=-1;
	while(L<=R)
	{
		Mid=(L+R)>>1;cnt=0;dfs(1,0);
		if(cnt<=m) Ans=Mid,R=Mid-1;
		else L=Mid+1;
	}
	printf("%d\n",Ans);
}