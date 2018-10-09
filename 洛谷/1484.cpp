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

const int MAXN=500010;

int n,k,a[MAXN];

struct dat{
	ll x,y;
	dat(ll _x=0,ll _y=0){x=_x;y=_y;}
	dat operator + (const dat &rhs) const {return dat(x+rhs.x,y+rhs.y);}
	bool operator < (const dat &rhs) const {return x<rhs.x||(x==rhs.x&&y>rhs.y);}
}f[MAXN][2];

bool check(ll x)
{
	for(int i=1;i<=n;i++)
	{
		f[i][0]=max(f[i-1][0],f[i-1][1]);
		f[i][1]=f[i-1][0]+dat(a[i]-x,1);
	}
	return max(f[n][0],f[n][1]).y<=k;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	ll L=0,R=1E9,Ans=0;
	while(L<=R)
	{
		ll mid=(L+R)>>1;
		if(check(mid))
			Ans=max(f[n][0],f[n][1]).x+k*mid,R=mid-1;
		else L=mid+1;
	}
	printf("%lld\n",Ans);
}