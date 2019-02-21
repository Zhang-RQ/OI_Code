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

const int MAXN=1E5+10;
const int P=10000;

int s[MAXN];
int nxt[MAXN],sig,T;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void solve()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	for(int i=2,j=0;i<=n;i++)
	{
		while(j&&s[j+1]!=s[i]) j=nxt[j];
		if(s[j+1]==s[i]) ++j;
		nxt[i]=j;
	}
	ll Ans=0;
	for(int i=n;i;i=nxt[i])
		(Ans+=ksm(sig,i))%=P;
	if(Ans<1000) printf("0");
	if(Ans<100) printf("0");
	if(Ans<10) printf("0");
	printf("%lld\n",Ans);
}

int main()
{
	for(scanf("%d%d",&sig,&T);T--;solve());
}
