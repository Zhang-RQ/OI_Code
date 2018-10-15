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

const int MAXN=2E5+10;

int n,m;
int t[MAXN<<2],nxt[MAXN],a[MAXN],Ans[MAXN],cur;
int fafa[MAXN];
set<int> s;

struct Query{
	int l,r,id;
	bool operator < (const Query &rhs) const {return l<rhs.l;}
}Q[MAXN];

void pushdown(int x)
{
	if(t[x]!=0x3f3f3f3f)
	{
		t[x<<1]=min(t[x<<1],t[x]);
		t[x<<1|1]=min(t[x<<1|1],t[x]);
		t[x]=0x3f3f3f3f;
	}
}

void build(int x,int l,int r)
{
	t[x]=0x3f3f3f3f;
	if(l==r)
	{
		s.insert(a[l]);
		while(s.find(cur)!=s.end()) ++cur;
		return t[x]=cur,void();
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}

int ask(int x,int l,int r,int p)
{
	if(l==r) return t[x];
	int mid=(l+r)>>1;pushdown(x);
	if(p<=mid) return ask(x<<1,l,mid,p);
	else return ask(x<<1|1,mid+1,r,p);
}

void change(int x,int l,int r,int cl,int cr,int v)
{
	if(cl<=l&&r<=cr) return t[x]=min(t[x],v),void();
	int mid=(l+r)>>1;pushdown(x);
	if(cl<=mid) change(x<<1,l,mid,cl,cr,v);
	if(cr>mid) change(x<<1|1,mid+1,r,cl,cr,v);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
	for(int i=n;i;i--)
	{
		if(fafa[a[i]]) nxt[i]=fafa[a[i]];
		else nxt[i]=n+1;
		fafa[a[i]]=i;
	}
	sort(Q+1,Q+1+m);build(1,1,n);
	for(int i=1,j=1;i<=n;i++)
	{
		while(j<=m&&Q[j].l==i)
			Ans[Q[j].id]=ask(1,1,n,Q[j].r),j++;
		change(1,1,n,i,nxt[i]-1,a[i]);
	}
	for(int i=1;i<=m;i++)
		printf("%d%c",Ans[i],i==m?'\n':' ');
}