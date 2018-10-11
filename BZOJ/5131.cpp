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

ll i,l,r,k,p,m;

struct Mat{
	ll v[3][3];
	Mat(){memset(v,0,sizeof v);}
	ll* operator [] (int i){return v[i];}
	const ll* operator [] (int i) const {return v[i];}
	Mat operator * (const Mat &rhs) const 
	{
		Mat ret;
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
				for(int k=1;k<=2;k++)
					ret[i][j]+=v[i][k]*rhs[k][j]%p;
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
				ret[i][j]%=p;
		return ret;
	}
}I,trans;

Mat ksm(Mat a,ll b)
{
	Mat ret=I;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,y,x);y-=(a/b)*x;
}

ll calc(ll n,ll p,ll r) {return n/p+(n%p>=r);}

void solve()
{
	scanf("%lld%lld%lld%lld%lld%lld",&i,&l,&r,&k,&p,&m);
	Mat res=ksm(trans,k-1);
	ll t=(m-i%p*res[1][1]%p+p)%p,d=gcd(res[2][1],p);
	if(t%d) return puts("0"),void();
	ll x,y,M=p/d;exgcd(res[2][1],p,x,y);
	x=x*t/d%M;x=(x%M+M)%M;
	ll Ans=calc(r,M,x)-(l?calc(l-1,M,x):0);
	printf("%lld\n",Ans);
}

int main()
{
	I[1][1]=I[2][2]=1;
	trans[2][1]=trans[1][2]=trans[2][2]=1;
	int T;
	for(scanf("%d",&T);T--;solve());
}