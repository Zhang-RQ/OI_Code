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

const int MAXN=15;

char str[60][1000];
int bl[MAXN],n,s,id[MAXN][MAXN],tot;
ll base[70],fac[MAXN],Ans,mp[70];

ll calc()
{
	ll t=0;int bit=0;memset(base,0,sizeof base);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(bl[i]!=bl[j])
				t|=1ll<<id[i][j];
	for(int i=1;i<=s;i++)
	{
		ll s=t&mp[i];
		for(int j=tot;~j;j--)
			if((s>>j)&1)
			{
				if(!base[j]) {base[j]=s;++bit;break;}
				else s^=base[j];
			}
	}
	return 1ll<<(s-bit);
}

void dfs(int x,int cnt)
{
	if(x>n) return Ans+=calc()*fac[cnt-1]*((cnt-1)&1?-1:1),void();
	for(int i=1;i<=cnt+1;i++) bl[x]=i,dfs(x+1,max(cnt,i));
}

int main()
{
	scanf("%d",&s);
	fac[0]=1;
	for(int i=1;i<=9;i++) fac[i]=fac[i-1]*i;
	for(int i=1;i<=s;i++)
		scanf("%s",str[i]+1);
	n=(sqrt(1+8*strlen(str[1]+1))+1)/2;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			id[i][j]=tot++;
	--tot;
	for(int i=1;i<=s;i++)
		for(int j=0;j<=tot;j++)
			mp[i]|=((ll)(str[i][j+1]-'0'))<<j;
	dfs(1,0);
	printf("%lld\n",Ans);
}
