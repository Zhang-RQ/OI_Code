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

const int MAXN=1E6+10;
const int P=1E9+7;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

struct dat{
	int k,b;
	dat(int _k=0,int _b=0){k=_k;b=_b;}
	dat operator + (const dat &rhs) const {return dat((k+rhs.k)%P,(b+rhs.b)%P);}
	dat operator * (const int &rhs) const {return dat(1ll*k*rhs%P,1ll*b*rhs%P);}
}f[MAXN];

int n,p[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1,a,b;i<=n;i++) scanf("%d%d",&a,&b),p[i]=1ll*a*ksm(b,P-2)%P;
	for(int i=n-1;i>=0;i--)
		f[i]=f[i+1]*p[i+1]+dat(1,0)*((1-p[i+1]+P)%P)+dat(0,1);
	ll Ans=f[0].b*ksm((1-f[0].k+P)%P,P-2)%P;
	printf("%lld\n",Ans);
}