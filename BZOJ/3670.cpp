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

char s[MAXN];
int nxt[MAXN],num[MAXN];

void solve()
{
	scanf("%s",s+1);
	ll Ans=1;num[1]=1;nxt[1]=0;
	for(int i=2,j=0,k=0;s[i];i++)
	{
		while(j&&s[j+1]!=s[i]) j=nxt[j];
		if(s[j+1]==s[i]) ++j;
		nxt[i]=j;num[i]=num[j]+1;

		while(k&&s[k+1]!=s[i]) k=nxt[k];
		if(s[k+1]==s[i]) ++k;
		while(k>(i>>1)) k=nxt[k];
		Ans*=num[k]+1;Ans%=P;
	}
	printf("%lld\n",Ans);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}