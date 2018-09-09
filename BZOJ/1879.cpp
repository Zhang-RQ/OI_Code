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

const int P=1E6+3;
const int MAXN=16;

int C[MAXN][MAXN],n,k,st[MAXN],tot,len;
char str[MAXN][60];

int calc(int s)
{
	len=strlen(str[1]+1);
	int Ans=1;tot=0;
	for(int i=0;i<n;i++)
		if((s>>i)&1)
			st[++tot]=i+1;
	for(int i=1,cur;i<=len;i++)
	{
		cur=0;
		for(int j=1;j<=tot;j++)
			if(str[st[j]][i]!='?')
			{
				if(cur&&str[st[j]][i]!=cur) return 0;
				else cur=str[st[j]][i];
			}
		if(!cur) Ans=1ll*Ans*26%P;
	}
	return Ans;
}

void solve()
{
	ll Ans=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
	for(int s=0,cur;s<1<<n;s++)
	{
		cur=__builtin_popcount(s);
		if(cur>=k) (Ans+=(P+1ll*calc(s)*C[cur][k]%P*((cur-k)&1?-1:1))%P)%=P;
	}
	printf("%lld\n",Ans);
}

int main()
{
	for(int i=0;i<=15;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
	}
	int T;
	for(scanf("%d",&T);T--;solve());	
}