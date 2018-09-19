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

const int MAXN=1E6+10;

int n,a[MAXN],b[MAXN],Ans1,Ans2;
ll m,sum[MAXN];

int check(int x)
{
	ll c=0;
	for(int i=1;i<=n;i++) b[i]=a[i];
	for(int i=2;i<=n;i++)
		if(b[i]-b[i-1]>x)
		{
			c+=b[i]-b[i-1]-x;
			b[i]=b[i-1]+x;
		}
	for(int i=n-1;i>=1;i--)
		if(b[i]-b[i+1]>x)
		{
			c+=b[i]-b[i+1]-x;
			b[i]=b[i+1]+x;
		}
	if(c>m) return -1;
	int L=1,R=1;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+b[i];
	ll tAns;
	for(int i=1;i<=n;i++)
	{
		while(b[R+1]>1ll*(R+1-i)*x) ++R;
		while(b[L]<=1ll*(i-L)*x) ++L;
		tAns=c+b[i];
		if(R>i) tAns+=-1ll*(R-i)*(x+x*(R-i))/2+sum[R]-sum[i];
		if(L<i) tAns+=-1ll*(i-L)*(x+x*(i-L))/2+sum[i-1]-sum[L-1];
		if(tAns<=m) return i;
	}
	return -1;
}

int main()
{
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int L=0,R=1E9;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		int pos=check(mid);
		if(pos==-1) L=mid+1;
		else R=mid-1,Ans1=mid,Ans2=pos;
	}
	printf("%d %d\n",Ans2,Ans1);
}