//Wrong Answer

#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b)
		return x=1,y=0,void();
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}

ll S1(int n,int k){return 1ll*n*(n+1)/2%k;}

ll S2(int n,int k){return 1ll*n*(n+1)*(2*n+1)/6%k;}

ll calc(int x,int y,int n,int m,int k)
{
	if(y==1)
		swap(x,y),swap(n,m);
	if(x!=1)
		throw "Fuck Off";
	if(n==1)
	{
		if(m<=y)
			return S1(m,k)*n%k;
		else
			return (S1(y,k)+1ll*(m-y)*y)%k;
	}
	if(m<=y)
		return S1(m,k)*n%k;
	if(m<=n+y-2)
	{
		int d=m-y;
		return (S1(y,k)*n%k+1ll*n*y%k*d%k+S1(d,k)*n%k-(S2(d,k)+S1(d,k))/2%k+k)%k;
	}
	else
	{
		int d=n-2;
		ll part1=(S1(y,k)*n%k+1ll*n*y%k*d%k+S1(d,k)*n%k-(S2(d,k)+S1(d,k))/2%k+k)%k;
		//printf("part1=%lld\n",part1);
		return (part1+(m-y-n+2)*(1ll*y*n%k+S1(n-1,k))%k)%k;
	}
}

void solve()
{
	int n,m,k;
	int Ansx=1<<29,Ansy=1<<29;
	scanf("%d%d%d",&n,&m,&k);
	int lim=max(n,m);
	for(int i=1;i<=lim;i++)
	{
		ll t=(k-calc(1,i,n,m,k))%k;
		ll d=gcd(1ll*n*m,k),x,y,mod=k/d;
		if(t%d)
			continue;
		exgcd(1ll*n*m,k,x,y);
		x=(x*t/d%mod+mod)%mod;
		int tansx=1+x,tansy=i+x;
		if(tansx+tansy<Ansx+Ansy)
			Ansx=tansx,Ansy=tansy;
		else if(tansx+tansy==Ansx+Ansy&&tansx<Ansx)
			Ansx=tansx,Ansy=tansy;
	}
	for(int i=1;i<=lim;i++)
	{
		ll t=(k-calc(i,1,n,m,k))%k;
		ll d=gcd(1ll*n*m,k),x,y,mod=k/d;
		if(t%d)
			continue;
		exgcd(1ll*n*m,k,x,y);
		x=(x*t/d%mod+mod)%mod;
		int tansx=i+x,tansy=1+x;
		if(tansx+tansy<Ansx+Ansy)
			Ansx=tansx,Ansy=tansy;
		else if(tansx+tansy==Ansx+Ansy&&tansy<Ansy)
			Ansx=tansx,Ansy=tansy;
	}
	if(Ansx==1<<29)
		printf("-1\n");
	else
		printf("%d %d\n",Ansy,Ansx);
}

int main()
{
	//printf("calc=%lld\n",calc(1,46,100,99,1E9));
	//return 0;
	while(0)
	{
		int n,m,x,y;
		scanf("%d%d%d%d",&n,&m,&x,&y);
		printf("Calc=%lld\n",calc(x,y,n,m,1E9));
	}
	int T;
	for(scanf("%d",&T);T--;solve());
}
