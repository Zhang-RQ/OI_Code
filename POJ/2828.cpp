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

int n,a[MAXN],b[MAXN],t[MAXN<<2],Ans[MAXN];

void pushup(int x){t[x]=t[x<<1]+t[x<<1|1];}

void build(int x,int l,int r)
{
	if(l==r) return t[x]=1,void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	pushup(x);
}

void update(int x,int l,int r,int k,int id)
{
	if(l==r) return Ans[l]=id,t[x]=0,void();
	int mid=(l+r)>>1;
	if(t[x<<1]>=k) update(x<<1,l,mid,k,id);
	else update(x<<1|1,mid+1,r,k-t[x<<1],id);
	pushup(x);
}

int main()
{
	while(~scanf("%d",&n))
	{
		build(1,1,n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&a[i],&b[i]);
		for(int i=n;i;i--)
			update(1,1,n,a[i]+1,b[i]);
		for(int i=1;i<=n;i++)
			printf("%d%c",Ans[i],i==n?'\n':' ');

	}
}