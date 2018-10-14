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

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

int k,cnt;
ll d[MAXN],n,x;
bool vis[MAXN];

int main()
{
	scanf("%lld%d",&n,&k);
	int lim=sqrt(n);
	for(int i=1;i<=lim;i++)
		if(n%i==0)
		{
			d[++cnt]=i;
			if(1ll*i*i!=n) d[++cnt]=n/i;
		}
	sort(d+1,d+1+cnt);
	for(int i=1;i<=k-1;i++)
	{
		scanf("%lld",&x);
		ll g=gcd(x,n);
		vis[lower_bound(d+1,d+1+cnt,g)-d]=1;
	}
	for(int i=cnt;i;i--)
		for(int j=i+1;j<=cnt;j++)
		{
			if(d[j]%d[i]==0)
				vis[i]|=vis[j];
			if(vis[i]) break;
		}
	scanf("%lld",&x);
	for(int i=1;i<=cnt;i++)
		if(!vis[i]&&x%d[i]==0)
			return printf("%lld\n",n/d[i]),0;
}