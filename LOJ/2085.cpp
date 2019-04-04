#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXV=1E6+10;
const int BLK=1E6;

int vis[MAXV],n,m,k;
int pr[MAXV],pc,phi[MAXV],pF[MAXV];
ll mu[MAXV],smu[MAXV];

vector<int> fac;
map<int,ll> MMu;
map<pair<int,int>,ll> MG;

int gcd(int a,int b){return !b?a:gcd(b,a%b);}

void sieve()
{
	mu[1]=1;phi[1]=1;
	for(int i=2;i<=BLK;i++)
	{
		if(!vis[i]) pr[++pc]=i,mu[i]=-1,phi[i]=i-1;
		for(int j=1;j<=pc&&pr[j]*i<=BLK;j++)
		{
			vis[i*pr[j]]=1;
			if(!(i%pr[j])) mu[i*pr[j]]=0,phi[i*pr[j]]=phi[i]*pr[j];
			else mu[i*pr[j]]=-mu[i],phi[i*pr[j]]=phi[i]*phi[pr[j]];
		}
	}
	for(int i=1;i<=BLK;i++)
		smu[i]=smu[i-1]+mu[i];
}

ll Mu(int n)
{
	if(n<=BLK) return smu[n];
	if(MMu.count(n)) return MMu[n];
	ll ret=1;
	for(int i=2,pos=0;i<=n;i=pos+1)
	{
		pos=n/(n/i);
		ret-=Mu(n/i)*(pos-i+1);
	}
	return MMu[n]=ret;
}

ll G(int n,int k)
{
	if(!n) return 0;
	if(k==1) return Mu(n);
	if(MG.count({n,k}))
		return MG[{n,k}];
	ll ret=0;
	for(int d:fac)
		if(k%d==0&&mu[d]!=0)
			ret+=G(n/d,d);
	return MG[{n,k}]=ret;
}

ll F(int n) {return 1ll*(n/k)*phi[k]+pF[n%k];}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
		if(k%i==0)
			fac.push_back(i);
	sieve();
	for(int i=1;i<k;i++)
		pF[i]=pF[i-1]+(gcd(i,k)==1);
	int lim=min(n,m);
	ll Ans=0;
	for(int d=1,pos=0;d<=lim;d=pos+1)
	{
		pos=min(n/(n/d),m/(m/d));
		Ans+=(n/d)*F(m/d)*(G(pos,k)-G(d-1,k));
	}
	printf("%lld\n",Ans);
}
