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
#include<ctime>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int MAXM=1E6+10;
const int MAXS=1<<10;

int n,k;

struct __edge{
	int v,nxt;
}Edge[MAXM];

bool vis[MAXN];
int head[MAXN],cnt_e,siz[MAXN],mx_rt,rt,cnt1,fafatime;
int t1[MAXS],t2[MAXS],val[MAXN],ful;
ll Ans;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

inline void get_s(int* f,int *res)
{
	++fafatime;
	for(int s=0;s<=ful;s++)
		res[s]=f[s];
	for(int i=0;i<k;i++)
		for(int s=ful;~s;s--)
			if(!((s>>i)&1))
				res[s]+=res[s^(1<<i)];
}

void get_rt(int x,int fa,int sz)
{
	siz[x]=1;int mx=0;++cnt1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa||vis[v]) continue;
		get_rt(v,x,sz);mx=max(mx,siz[v]);
		siz[x]+=siz[v];
	}
	mx=max(mx,sz-siz[x]);
	if(mx<mx_rt) mx_rt=mx,rt=x;
}

void dfs_ins(int x,int fa,int s)
{
	s|=val[x];t1[s]++;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa||vis[v]) continue;
		dfs_ins(v,x,s);
	}
}

void dfs_que(int x,int fa,int s)
{
	s|=val[x];Ans+=t2[ful^s];
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa||vis[v]) continue;
		dfs_que(v,x,s);
	}
}

void solve(int x)
{
	vis[x]=1;
	memset(t1,0,sizeof t1);
	memset(t2,0,sizeof t2);
	t1[val[x]]++;get_s(t1,t2);
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(vis[v]) continue;
		dfs_que(v,x,0);
		dfs_ins(v,x,val[x]);
		get_s(t1,t2);
	}
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(vis[v]) continue;
		mx_rt=2333333;
		get_rt(v,x,siz[v]);
		solve(rt);
	}
}

void clear() {cnt_e=0;memset(vis,0,sizeof vis);memset(head,0,sizeof head);memset(siz,0,sizeof siz);}

int main()
{
	while(~scanf("%d%d",&n,&k))
	{
		Ans=0;clear();
		ful=(1<<k)-1;
		for(int i=1,x;i<=n;i++) scanf("%d",&x),val[i]=1<<(x-1);
		for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
		if(k==1) {printf("%lld\n",1ll*n*n);continue;}
		mx_rt=1<<30;get_rt(1,0,n);solve(rt);
		printf("%lld\n",Ans<<1);
	}
}