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

const int MAXN=105;

char s[MAXN];
int n;
ll f[MAXN][2],Ans;

int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	s[++n]=s[1];
	f[1][0]=1;
	for(int i=2;i<=n;i++)
	{
		if(s[i-1]=='A') f[i][1]=f[i-1][0]+f[i-1][1];
		else f[i][1]=f[i-1][0];
		if(s[i]=='A'&&s[i-1]=='B') f[i][0]=f[i-1][1];
		else if(s[i]=='B') f[i][0]=f[i-1][0];
	}
	Ans+=f[n][0];
	memset(f,0,sizeof f);
	f[1][1]=1;
	for(int i=2;i<=n;i++)
	{
		if(s[i-1]=='A') f[i][1]=f[i-1][0]+f[i-1][1];
		else f[i][1]=f[i-1][0];
		if(s[i]=='A'&&s[i-1]=='B') f[i][0]=f[i-1][1];
		else if(s[i]=='B') f[i][0]=f[i-1][0];
	}
	Ans+=f[n][1];
	printf("%lld\n",Ans);
}