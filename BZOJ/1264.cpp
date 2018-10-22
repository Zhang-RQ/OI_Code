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

int t[MAXN<<2];

void pushdown(int x)
{
	if(t[x])
	{
		t[x<<1]=max(t[x],t[x<<1]);t[x<<1|1]=max(t[x],t[x<<1|1]);
		t[x]=0;
	}
}

void change(int x,int l,int r,int cl,int cr,int v)
{
	if(cl<=l&&r<=cr) return t[x]=max(t[x],v),void();
	int mid=(l+r)>>1;pushdown(x);
	if(cl<=mid) change(x<<1,l,mid,cl,cr,v);
	if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,v);
}

int query(int x,int l,int r,int p)
{
	if(l==r) return t[x];
	int mid=(l+r)>>1;pushdown(x);
	if(p<=mid) return query(x<<1,l,mid,p);
	else return query(x<<1|1,mid+1,r,p);
}

int n,N,a[MAXN],b[MAXN];
vector<int> v[MAXN];

int main()
{
	scanf("%d",&n);N=n*5;
	for(int i=1,x;i<=N;i++)
		scanf("%d",&x),v[x].push_back(i),b[i]=x;
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=N;i++)
		for(int j=4;~j;j--)
			change(1,0,N,v[a[i]][j],N,query(1,0,N,v[a[i]][j]-1)+1);
	printf("%d\n",query(1,0,N,N));
}