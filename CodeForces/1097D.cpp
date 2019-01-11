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

int k;
ll n,Res,f[2][64],inv[64];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void inc(ll &x,ll y){x+=y;if(x>=P) x-=P;}

ll solve(pair<ll,int> x)
{
	memset(f,0,sizeof f);
	f[0][x.second]=1;
	for(int i=1,nw;i<=k;i++)
	{
		nw=i&1;
		memset(f[nw],0,sizeof f[nw]);
		for(int j=0;j<=x.second;j++)
			for(int l=0;l<=j;l++)
				inc(f[nw][l],f[!nw][j]*inv[j+1]%P);
	}
	ll ret=0,pw=1;
	for(int i=0;i<=x.second;i++)
		inc(ret,f[k&1][i]*pw%P),pw=pw*x.first%P;
	return ret;
}

int main()
{
	for(int i=0;i<64;i++) inv[i]=ksm(i,P-2);
	scanf("%lld%d",&n,&k);
	ll _n=n,Ans=1;
	for(int i=2;1ll*i*i<=n;i++)
		if(!(_n%i))
		{
			int tot=0;
			while(!(_n%i)) _n/=i,++tot;
			(Ans*=solve(make_pair(i,tot)))%=P;;
		}
	if(_n!=1) (Ans*=solve(make_pair(_n,1)))%=P;
	printf("%lld\n",Ans);
}