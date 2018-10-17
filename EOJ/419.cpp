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
	int l,r,v;
	ll s;
}t[MAXN<<6];

int rt[MAXN],n,q,cnt,pre[MAXN],stk[MAXN],top,a[MAXN];

void insert(int &x,int l,int r,int p,int y)
{
	x=++cnt;
	t[x]=t[y];
	t[x].s+=p;
	t[x].v++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p,t[y].l);
	else insert(t[x].r,mid+1,r,p,t[y].r);
}

pair<int,ll> query(int x,int l,int r,int ql,int qr,int y)
{
	if(ql<=l&&r<=qr) return make_pair(t[x].v-t[y].v,t[x].s-t[y].s);
	int mid=(l+r)>>1;
	if(qr<=mid) return query(t[x].l,l,mid,ql,qr,t[y].l);
	else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr,t[y].r);
	pair<int,ll> L=query(t[x].l,l,mid,ql,qr,t[y].l),R=query(t[x].r,mid+1,r,ql,qr,t[y].r);
	return make_pair(L.first+R.first,L.second+R.second);
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		while(top&&a[stk[top]]<=a[i]) --top;
		if(top) pre[i]=stk[top];
		stk[++top]=i;
		if(pre[i]) insert(rt[i],1,n,pre[i],rt[i-1]);
		else rt[i]=rt[i-1];
	}
	for(int i=1,l,r;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		pair<int,ll> res=query(rt[r],1,n,l,n,rt[l-1]);
		printf("%lld\n",res.second-1ll*l*res.first+res.first);
	}
}