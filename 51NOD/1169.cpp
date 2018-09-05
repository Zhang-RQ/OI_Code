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

const int MAXN=1E2+10;
const int P=1E9+7;

int n,c[MAXN];
ll f[MAXN][2],pw[MAXN],Ans;

ll solve()
{
	memset(f,0,sizeof f);
	ll Ret=0;
	for(int i=30;~i;--i)
	{
		f[0][0]=1;
		for(int j=1;j<=n;j++)
		{
			if((c[j]>>i)&1)
			{
				f[j][0]=(f[j-1][1]*((c[j]&((1<<i)-1))+1)%P+f[j-1][0]*pw[i]%P)%P;
				f[j][1]=(f[j-1][0]*((c[j]&((1<<i)-1))+1)%P+f[j-1][1]*pw[i]%P)%P;
			}
			else
			{
				f[j][1]=f[j-1][1]*((c[j]&((1<<i)-1))+1)%P;
				f[j][0]=f[j-1][0]*((c[j]&((1<<i)-1))+1)%P;
			}
		}
		int fl=0;ll x=1;
		for(int j=n;j;j--)
		{
			if((c[j]>>i)&1)
				(Ret+=f[j-1][fl]*x%P)%=P,fl^=1;
			x=((c[j]&((1<<i)-1))+1)%P*x%P;
		}
		if(fl) break;
	}
	return Ret;
}

int main()
{
	pw[0]=1;
	for(int i=1;i<=30;i++) pw[i]=(pw[i-1]<<1)%P;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	Ans=solve();
	for(int i=1;i<=n;i++) c[i]--;
	Ans=(Ans-solve()+P)%P;
	printf("%lld\n",Ans);
}