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
const int P=1E9+7;

int n,f[MAXN];
bool vis[MAXN];
ll Ans,fac[MAXN],ifac[MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void solve()
{
	memset(vis,0,sizeof vis);Ans=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&f[i]);
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			int cnt=1;
			int x=i;
			while(f[x]!=n+1)
			{
				vis[x]=1;
				++cnt;x=f[x];
			}
			vis[x]=1;
			(Ans*=ksm(cnt+1,cnt-1)*ifac[cnt]%P)%=P;
		}
	(Ans*=fac[n])%=P;
	printf("%lld\n",Ans);
}

int main()
{
	fac[0]=1;
	for(int i=1;i<=200000;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[200000]=ksm(fac[200000],P-2);
	for(int i=199999;i>=1;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	int T;
	for(scanf("%d",&T);T--;solve());
}