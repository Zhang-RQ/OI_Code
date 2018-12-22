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

const int P=1E9+7;
const int MAXM=1E6+10;

int n,m;
ll fac[MAXM],ifac[MAXM],f[MAXM],pre[MAXM],suf[MAXM];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll solve(ll x)
{
	ll Ans=0;pre[0]=suf[m+3]=1;
	for(int i=1;i<=m+2;i++)
		pre[i]=pre[i-1]*((x-i+P)%P)%P;
	for(int i=m+2;i;i--)
		suf[i]=suf[i+1]*((x-i+P)%P)%P;
	for(int i=1;i<=m+2;i++)
		Ans=(Ans+pre[i-1]*suf[i+1]%P*ifac[i-1]%P*ifac[m+2-i]%P*f[i]%P*((m+2-i)&1?-1:1)+P)%P;
	return Ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=m+2;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[m+2]=ksm(fac[m+2],P-2);
	for(int i=m+1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=1;i<=m+2;i++)
		f[i]=(f[i-1]+ksm(i,m))%P;
	printf("%lld\n",solve(n));
}