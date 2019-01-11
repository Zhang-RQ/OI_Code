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

ll n,lim,pos[MAXN],g[MAXN];
bool vis[MAXN];
int pr[MAXN],pc,id[MAXN],cnt;

void sieve()
{
	for(int i=2;i<=lim;i++)
	{
		if(!vis[i]) pr[++pc]=i;
		for(int j=1;j<=pc&&1ll*i*pr[j]<=lim;j++)
		{
			vis[i*pr[j]]=1;
			if(!(i%pr[j])) break;
		}
	}
}

int ID(ll x){return id[x<=lim?x:MAXN-n/x];}

int main()
{
	scanf("%lld",&n);lim=sqrt(n);sieve();
	for(ll i=1,nxt=0;i<=n;i=nxt+1)
		nxt=n/(n/i),pos[++cnt]=n/i;
	for(int i=1;i<=cnt;i++)
		g[i]=pos[i]-1;
	for(int i=1;i<=cnt;i++)
		id[pos[i]<=lim?pos[i]:MAXN-n/pos[i]]=i;
	for(int j=1;j<=pc;j++)
		for(int i=1;i<=cnt;i++)
		{
			if(1ll*pr[j]*pr[j]>pos[i]) break;
			g[i]-=g[ID(pos[i]/pr[j])]-j+1;
		}
	printf("%lld\n",g[1]);
}