#include<cstdio>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E7+10;

bool vis[MAXN];
int pri[MAXN],cnt,n,m;
ll a[MAXN];

int main()
{
	scanf("%d%lld%d",&n,&a[1],&m);
	for(int i=2,t=14;i<=n;i++)
	{
		a[i]=a[i-1]+t;
		if(a[i]>m) a[i]-=m;
		t+=7;
		if(t>m) t-=m;
	}
	for(int i=2;i<MAXN;i++)
	{
		if(!vis[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<MAXN;j++)
		{
			vis[i*pri[j]]=1;
			if(!(i%pri[j])) break;
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		int lim=n/pri[i];
		for(int j=1;j<=lim;j++)
			a[j*pri[i]]+=a[j];
	}
	ll Ans=0;
	for(int i=1;i<=n;i++)
		Ans^=a[i];
	printf("%lld\n",Ans);
}