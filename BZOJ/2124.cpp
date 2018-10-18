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
const int base=131;

int n,a[MAXN];
ull t[MAXN<<2],rt[MAXN<<2],pw[MAXN];

void pushup(int x,int l,int r)
{
	int mid=(l+r)>>1;
	t[x]=t[x<<1]*pw[r-mid]+t[x<<1|1];
	rt[x]=rt[x<<1|1]*pw[mid-l+1]+rt[x<<1];
}

ull query1(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return t[x];
	int mid=(l+r)>>1;
	if(qr<=mid) return query1(x<<1,l,mid,ql,qr);
	else if(ql>mid) return query1(x<<1|1,mid+1,r,ql,qr);
	return query1(x<<1,l,mid,ql,mid)*pw[qr-mid]+query1(x<<1|1,mid+1,r,mid+1,qr);
}

ull query2(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return rt[x];
	int mid=(l+r)>>1;
	if(qr<=mid) return query2(x<<1,l,mid,ql,qr);
	else if(ql>mid) return query2(x<<1|1,mid+1,r,ql,qr);
	return query2(x<<1,l,mid,ql,mid)+query2(x<<1|1,mid+1,r,mid+1,qr)*pw[mid-ql+1];
}

void change(int x,int l,int r,int p,int v)
{
	if(l==r) return t[x]=rt[x]=v,void();
	int mid=(l+r)>>1;
	if(p<=mid) change(x<<1,l,mid,p,v);
	else change(x<<1|1,mid+1,r,p,v);
	pushup(x,l,r);
}

void solve()
{
	memset(t,0,sizeof t);memset(rt,0,sizeof rt);
	scanf("%d",&n);pw[0]=1;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),pw[i]=pw[i-1]*base;
	for(int i=1;i<=n;i++)
	{
		int len=min(a[i]-1,n-a[i]);
		if(len)
		{
			if(query1(1,1,n,a[i]-len,a[i]-1)!=query2(1,1,n,a[i]+1,a[i]+len))
				return puts("Y"),void();
		}
		change(1,1,n,a[i],1);
	}
	puts("N");
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}