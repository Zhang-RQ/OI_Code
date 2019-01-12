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

const int MAXL=70;
const int P=1E9+7;

ll preS[MAXL];

ll S1(ll x){x%=P;return x*(x+1)/2%P;}

void solve()
{
	ll n=0,Ans=0;
	scanf("%lld",&n);
	int mx=63-__builtin_clzll(n);
	Ans=preS[mx-1];
	Ans+=S1(n^(1ll<<mx));
	printf("%lld\n",Ans*2%P);
}

int main()
{
	for(int i=1;i<=62;i++) preS[i]=(preS[i-1]+S1((1ll<<i)-1))%P;
	int T;
	for(scanf("%d",&T);T--;solve());
}