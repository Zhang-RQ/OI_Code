#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E6+10;
const int INF=1<<30;

int fa[MAXN],a[MAXN],n,k,stk[MAXN],top;
int t[MAXN<<2],tg[MAXN<<2],dfn[MAXN],dfn_end[MAXN],dft;
vector<int> T[MAXN];

void dfs(int x)
{
	dfn[x]=++dft;
	for(int v:T[x])
		dfs(v);
	dfn_end[x]=dft;
}

void pushup(int x){t[x]=max(t[x<<1],t[x<<1|1]);}

void pushdown(int x)
{
	if(tg[x])
	{
		t[x<<1]+=tg[x];
		t[x<<1|1]+=tg[x];
		tg[x<<1]+=tg[x];
		tg[x<<1|1]+=tg[x];
		tg[x]=0;
	}
}

void build(int x,int l,int r)
{
	if(l==r) return t[x]=-INF,void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	pushup(x);
}

void change(int x,int l,int r,int cl,int cr,int val)
{
	if(cl<=l&&r<=cr) return t[x]+=val,tg[x]+=val,void();
	int mid=(l+r)>>1;pushdown(x);
	if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
	if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
	pushup(x);
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		while(top&&a[stk[top]]<a[i]) fa[stk[top]]=i,--top;
		stk[++top]=i;
	}
	for(int i=1;i<=n;i++)
		T[fa[i]].push_back(i);
	dfs(0);
	build(1,1,dft);
	for(int i=1;i<=k;i++)
	{
		change(1,1,dft,dfn[i],dfn_end[i],1);
		change(1,1,dft,dfn[i],dfn[i],INF);
	}
	printf("%d%c",t[1],"\n "[k!=n]);
	for(int i=k+1;i<=n;i++)
	{
		change(1,1,dft,dfn[i-k],dfn_end[i-k],-1);
		change(1,1,dft,dfn[i-k],dfn[i-k],-INF);
		change(1,1,dft,dfn[i],dfn_end[i],1);
		change(1,1,dft,dfn[i],dfn[i],INF);
		printf("%d%c",t[1],"\n "[i!=n]);
	}
}
