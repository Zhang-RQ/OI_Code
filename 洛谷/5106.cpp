#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXN=1E6+10;
const int P=1E9+7;

int n,k,vis[MAXN],phi[MAXN],pri[MAXN],tot;
int pre[MAXN];
ll Ans=1;

void sieve()
{
	phi[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i]) pri[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&pri[j]*i<=n;j++)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]) phi[i*pri[j]]=phi[i]*(pri[j]-1);
			else {phi[i*pri[j]]=phi[i]*pri[j];break;}
		}
	}
}

ll ksm(ll a,ll b,ll p)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=p) if(b&1) (ret*=a)%=p;
	return ret;
}

int main()
{
	scanf("%d%d",&n,&k);sieve();
	for(int i=1;i<=tot;i++)
	{
		int pr=pri[i],ph=pri[i]-1,cnt=0;
		for(ll j=pr;j<=n;j*=pr)
			pre[++cnt]=n/j;
		pre[0]=n;
		for(int i=0;i<cnt;i++) pre[i]-=pre[i+1];
		for(int i=1;i<=cnt;i++) pre[i]+=pre[i-1];
		for(int i=1;i<=cnt;i++)
		{
			(Ans*=ksm(ph,(ksm(pre[i],k,P-1)-ksm(pre[i-1],k,P-1)+P-1)%(P-1),P)%P)%=P;
			ph=1ll*ph*pr%P;
		}
	}
	printf("%lld\n",Ans);
}
