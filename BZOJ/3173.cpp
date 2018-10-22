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

int n,p[MAXN],t[MAXN<<2],T[MAXN],a[MAXN];

void build(int x,int l,int r)
{
	t[x]=r-l+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}

int ask(int x,int l,int r,int k)
{
	t[x]--;
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(k<=t[x<<1]) return ask(x<<1,l,mid,k);
	else return ask(x<<1|1,mid+1,r,k-t[x<<1]);
}

void C(int x,int v)
{
	for(;x<=n;x+=x&(-x))
		t[x]=max(t[x],v);
}

int Q(int x)
{
	int ret=0;
	for(;x;x-=x&(-x))
		ret=max(ret,t[x]);
	return ret;
}

int main()
{
	scanf("%d",&n);build(1,1,n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=n;i;i--)
		p[i]=ask(1,1,n,a[i]+1);
	for(int i=1,Ans=0;i<=n;i++)
	{
		int v=Q(p[i])+1;
		C(p[i],v);
		printf("%d\n",Ans=max(Ans,v));
	}
}