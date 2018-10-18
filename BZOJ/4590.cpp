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

int n,k,a[MAXN];

ll check(ll p)
{
	ll ret=0,r=0;
	for(int i=1;i<=n;i++)
	{
		r=max(0ll,r+a[i]);
		if(r>=p) ++ret,r=0;
	}
	return ret;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	ll L=1,R=1E18,Ans1=0,Ans2=0;
	while(L<=R)
	{
		ll mid=(L+R)>>1;
		if(check(mid)<=k) Ans1=mid,R=mid-1;
		else L=mid+1;
	}
	L=1,R=1E18;
	while(L<=R)
	{
		ll mid=(L+R)>>1;
		if(check(mid)>=k) Ans2=mid,L=mid+1;
		else R=mid-1;
	}
	if(Ans1>Ans2||!Ans1||!Ans2) puts("-1");
	else printf("%lld %lld\n",Ans1,Ans2);
}