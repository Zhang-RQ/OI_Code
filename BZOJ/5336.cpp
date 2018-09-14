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

const int MAXS=1<<15;
const int P=1E9+7;

char str[20];
int n,k,s1[20],nxt[MAXS][3],ff[20],fff[20];
ll f[2][MAXS][3],Ans[20],tot;

inline int trans(int S,int c)
{
	for(int i=1;i<=k;i++)
		if((S>>(i-1))&1)
			ff[i]=ff[i-1]+1;
		else ff[i]=ff[i-1];
	for(int i=1;i<=k;i++)
	{
		fff[i]=max(ff[i],fff[i-1]);
		if(s1[i]==c)
			fff[i]=max(fff[i],ff[i-1]+1);
	}
	int ret=0;
	for(int i=1;i<=k;i++)
		if(fff[i]-fff[i-1])
			ret|=1<<(i-1);
	return ret;
}

int main()
{
	scanf("%d%d",&n,&k);
	scanf("%s",str+1);
	for(int i=1;i<=k;i++)
		if(str[i]=='N') s1[i]=0;
		else if(str[i]=='O') s1[i]=1;
		else s1[i]=2; 
	for(int s=0;s<1<<k;s++)
		for(int i=0;i<3;i++)
			nxt[s][i]=trans(s,i);
	f[0][0][0]=1;
	for(int i=0,now;i<n;i++)
	{
		now=i&1;
		for(int s=0;s<1<<k;s++)
			f[now^1][s][0]=f[now^1][s][1]=f[now^1][s][2]=0;
		for(int s=0;s<1<<k;s++)
		{
			(f[now^1][nxt[s][0]][1]+=f[now][s][0])%=P;
			(f[now^1][nxt[s][0]][1]+=f[now][s][1])%=P;
			(f[now^1][nxt[s][0]][1]+=f[now][s][2])%=P;
			
			(f[now^1][nxt[s][1]][0]+=f[now][s][0])%=P;
			(f[now^1][nxt[s][1]][2]+=f[now][s][1])%=P;
			(f[now^1][nxt[s][1]][0]+=f[now][s][2])%=P;
			
			(f[now^1][nxt[s][2]][0]+=f[now][s][0])%=P;
			(f[now^1][nxt[s][2]][0]+=f[now][s][1])%=P;
		}
	}
	for(int s=0;s<1<<k;s++)
		(Ans[__builtin_popcount(s)]+=f[n&1][s][0]+f[n&1][s][1]+f[n&1][s][2])%=P;
	for(int i=0;i<=k;i++) printf("%lld\n",Ans[i]);
}