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

const int MAXN=1E7+10;

bool vis[MAXN];
int pri[MAXN],tot,t[MAXN],fir[MAXN],pw[MAXN];
ll f[MAXN];

void init()
{
	for(int i=2;i<MAXN;i++)
	{
		if(!vis[i]) pri[++tot]=i,t[i]=pw[i]=1,f[i]=1,fir[i]=0;
		for(int j=1;j<=tot&&i*pri[j]<MAXN;j++)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				pw[i*pri[j]]=pw[i]+1;
				if(fir[i]) f[i*pri[j]]=t[fir[i]]==pw[i*pri[j]]?-f[fir[i]]:0,t[i*pri[j]]=t[fir[i]]==pw[i*pri[j]]?t[fir[i]]:-1;
				else f[i*pri[j]]=1,t[i*pri[j]]=pw[i*pri[j]];
				fir[i*pri[j]]=fir[i];
				break;
			}
			else
			{
				pw[i*pri[j]]=1;
				fir[i*pri[j]]=i;
				t[i*pri[j]]=t[i]==1?1:-1;
				f[i*pri[j]]=t[i]==1?-f[i]:0;
			}
		}
	}
	for(int i=1;i<MAXN;i++) f[i]+=f[i-1];
}

void solve()
{
	int n,m;ll Ans=0;
	scanf("%d%d",&n,&m);
	if(n>m) swap(n,m);
	for(int d=1,pos=0;d<=n;d=pos+1)
	{
		pos=min(n/(n/d),m/(m/d));
		Ans+=(f[pos]-f[d-1])*(n/d)*(m/d);
	}
	printf("%lld\n",Ans);
}

int main()
{
	init();int T;
	for(scanf("%d",&T);T--;solve());	
}