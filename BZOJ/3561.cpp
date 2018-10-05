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
const int MAXN=5E5+10;

bool vis[MAXN];
int pri[MAXN],tot,mu[MAXN],f[MAXN],n,m,s[MAXN];
ll Ans=0;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void init()
{
	mu[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!vis[i]) pri[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&pri[j]*i<MAXN;j++)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]==0) {mu[i*pri[j]]=0;break;}
			else mu[i*pri[j]]=-mu[i];
		}
	}
}

int main()
{
	init();
	scanf("%d%d",&n,&m);
	if(n>m) swap(n,m);
	for(int i=1;i<=m;i++) f[i]=1;
	for(int d=1;d<=n;d++)
	{
		ll dlt=0;
		for(int j=1;j<=m/d;j++) f[j]=1ll*f[j]*j%P,s[j]=(s[j-1]+f[j])%P;
		for(int i=1;i<=n/d;i++)
			if(mu[i])
				(dlt+=1ll*mu[i]*ksm(i,2*d)%P*s[n/d/i]%P*s[m/d/i]%P+P)%=P;
		(Ans+=ksm(d,d)*dlt%P)%=P;
	}
	Ans%=P;
	(Ans+=P)%=P;
	printf("%lld\n",Ans);
}