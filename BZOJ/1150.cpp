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
ll Ans;

struct dat{
	ll x,y;
	dat(ll _x=0,ll _y=0){x=_x;y=_y;}
	dat operator + (const dat &rhs) const {return dat(x+rhs.x,y+rhs.y);}
	bool operator < (const dat &rhs) const {return x<rhs.x||(x==rhs.x&&y<rhs.y);}
}f[MAXN][2];

dat check(int Mid)
{
	f[1][1]=dat(1ll<<60,0);
	for(int i=2;i<=n;i++)
	{
		f[i][0]=min(f[i-1][0],f[i-1][1]);
		f[i][1]=f[i-1][0]+dat(a[i]-a[i-1]-Mid,1);
	}
	return min(f[n][0],f[n][1]);
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int L=0,R=1E9;
	while(L<=R)
	{
		int mid=(L+R)>>1;dat T=check(mid);
		if(T.y<=k) Ans=T.x+1ll*k*mid,L=mid+1;
		else R=mid-1;
	}
	printf("%lld\n",Ans);
}