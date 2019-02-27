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

const int P=998244353;
const int MAXK=1050;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll Add(ll x,ll y){x+=y;return x>=P?x-P:x;}

ll Sub(ll x,ll y){x-=y;return x<0?x+P:x;}

void Inc(ll &x,ll y){x+=y;if(x>=P) x-=P;}

void Dec(ll &x,ll y){x-=y;if(x<0) x+=P;}

int n,k,x,y,tk;
ll g[MAXK][MAXK],s[MAXK][MAXK],p,c[2*MAXK],f[MAXK];//f[n]=sum c[n-i]*f[i]

struct Poly{
	ll a[2*MAXK];

	Poly(){memset(a,0,sizeof a);}
	
	ll& operator [](int x){return a[x];}
	const ll& operator [] (int x) const {return a[x];}

	Poly operator * (const Poly &rhs) const
	{
		Poly ret;
		for(int i=0;i<tk;i++)
			for(int j=0;j<tk;j++)
				Inc(ret[i+j],a[i]*rhs[j]%P);
		for(int i=2*tk-2;i>=tk;i--)
		{
			for(int j=1;j<=tk;j++)
				Inc(ret[i-j],ret[i]*c[j]%P);
			ret[i]=0;
		}
		return ret;
	}
};

Poly ksm(ll b)
{
	Poly ret,a;ret[0]=1;a[1]=1;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

ll solve(int k)
{
	memset(g,0,sizeof g);
	memset(s,0,sizeof s);
	for(int i=k+1;~i;i--) s[0][i]=1;
	for(int i=1;i<=k;i++)
	{
		for(int j=k/i;j>=1;j--)
		{
			for(int o=1;o<=i;o++)
				Inc(g[i][j],s[o-1][j+1]*s[i-o][j]%P*ksm(p,j)%P*Sub(1,p)%P);
			s[i][j]=Add(s[i][j+1],g[i][j]);
		}
	}
	tk=k+1;
	for(int i=1;i<=k;i++)
		c[i+1]=s[i][1]*Sub(1,p)%P;
	f[0]=1;c[1]=Sub(1,p);
	for(int i=1;i<=tk;i++)
	{
		f[i]=0;
		for(int j=0;j<i;j++)
			Inc(f[i],f[j]*c[i-j]%P);
	}
	if(n+1<tk) return f[n+1]*ksm(Sub(1,p),P-2)%P;
	Poly tmp=ksm(n+1);
	ll ret=0;
	for(int i=0;i<tk;i++)
		Inc(ret,tmp[i]*f[i]%P);
	return ret*ksm(Sub(1,p),P-2)%P;
}

int main()
{
	scanf("%d%d%d%d",&n,&k,&x,&y);
	p=1ll*x*ksm(y,P-2)%P;
	printf("%lld\n",Sub(solve(k),solve(k-1)));
}
