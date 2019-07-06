#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3E5+10;

int n,a[MAXN],b[MAXN],pos[MAXN],t[MAXN<<2];
queue<int> q[MAXN];

void clear(queue<int> &q)
{
	queue<int> nq;
	swap(q,nq);
}

void pushup(int x) {t[x]=min(t[x<<1],t[x<<1|1]);}

void build(int x,int l,int r)
{
	if(l==r)
		return t[x]=a[l],void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	pushup(x);
}

void change(int x,int l,int r,int p)
{
	if(l==r)
		return t[x]=(1<<30),void();
	int mid=(l+r)>>1;
	if(p<=mid)
		change(x<<1,l,mid,p);
	else
		change(x<<1|1,mid+1,r,p);
	pushup(x);
}

int query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)
		return t[x];
	int mid=(l+r)>>1;
	if(qr<=mid)
		return query(x<<1,l,mid,ql,qr);
	else if(ql>mid)
		return query(x<<1|1,mid+1,r,ql,qr);
	else
		return min(query(x<<1,l,mid,ql,qr),query(x<<1|1,mid+1,r,ql,qr));
}

void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
		clear(q[i]);
	for(int i=1;i<=n;i++)
		q[a[i]].push(i);
	for(int i=1;i<=n;i++)
	{
		if(!q[b[i]].size())
			return puts("No"),void();
		pos[i]=q[b[i]].front();q[b[i]].pop();
	}
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		if(query(1,1,n,1,pos[i])!=b[i])
			return puts("No"),void();
		change(1,1,n,pos[i]);
	}
	puts("Yes");
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
