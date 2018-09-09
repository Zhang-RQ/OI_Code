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

struct node{
	int l,r;
	ll sum,add;
}t[MAXN<<7];

int cnt,a[MAXN],n,m,rt[MAXN],cur;
char str[10];

void build(int &x,int l,int r)
{
	x=++cnt;
	if(l==r) return t[x].sum=a[l],void();
	int mid=(l+r)>>1;
	build(t[x].l,l,mid);build(t[x].r,mid+1,r);
	t[x].sum=t[t[x].l].sum+t[t[x].r].sum;
}

void change(int &x,int l,int r,int cl,int cr,int val,int _x)
{
	x=++cnt;t[x]=t[_x];
	if(cl<=l&&r<=cr) return t[x].add+=val,void();
	int mid=(l+r)>>1;
	if(cl<=mid) change(t[x].l,l,mid,cl,cr,val,t[_x].l);
	if(cr>mid)  change(t[x].r,mid+1,r,cl,cr,val,t[_x].r);
	t[x].sum=t[t[x].l].sum+t[t[x].r].sum+(mid-l+1)*t[t[x].l].add+(r-mid)*t[t[x].r].add;
}

ll query(int x,int l,int r,int ql,int qr)
{
	if(ql==l&&r==qr) return t[x].sum+t[x].add*(qr-ql+1);
	int mid=(l+r)>>1;ll ret=(qr-ql+1)*t[x].add;
	if(qr<=mid) ret+=query(t[x].l,l,mid,ql,qr);
	else if(ql>mid)  ret+=query(t[x].r,mid+1,r,ql,qr);
	else ret+=query(t[x].l,l,mid,ql,mid)+query(t[x].r,mid+1,r,mid+1,qr);
	return ret;
}

void dfs(int x,int l,int r)
{
	printf("%d %d s=%lld a=%lld\n",l,r,t[x].sum,t[x].add);
	if(l==r) return;
	int mid=(l+r)>>1;
	dfs(t[x].l,l,mid);dfs(t[x].r,mid+1,r);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build(rt[0],1,n);
	for(int i=1,l,r,x;i<=m;i++)
	{
		scanf("%s",str+1);
		if(str[1]=='C')
		{
			scanf("%d%d%d",&l,&r,&x);++cur;
			change(rt[cur],1,n,l,r,x,rt[cur-1]);
		}
		if(str[1]=='Q')
		{
			scanf("%d%d",&l,&r);
			printf("%lld\n",query(rt[cur],1,n,l,r));
		}
		if(str[1]=='H')
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%lld\n",query(rt[x],1,n,l,r));
		}
		if(str[1]=='B')
		{
			scanf("%d",&x);
			cur=x;
		}
	}
}