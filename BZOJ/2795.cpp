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

const int base=131;
const int MAXN=5E5+10;

char str[MAXN];
bool vis[MAXN];
ull hsh[MAXN],pw[MAXN];
int n,pri[MAXN],tot,mnd[MAXN],p[233],cnt,q;

ull get_hsh(int l,int r){return hsh[r]-hsh[l-1]*pw[r-l+1];}

void sieve()
{
	mnd[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i]) pri[++tot]=i,mnd[i]=i;
		for(int j=1;j<=tot&&i*pri[j]<=n;j++)
		{
			vis[i*pri[j]]=1;
			mnd[i*pri[j]]=pri[j];
			if(!(i%pri[j])) break;
		}
	}
}

int main()
{
	scanf("%d%s",&n,str+1);pw[0]=1;
	for(int i=1;i<=n;i++) hsh[i]=hsh[i-1]*base+str[i],pw[i]=pw[i-1]*base;
	sieve();scanf("%d",&q);
	for(int i=1,l,r,len;i<=q;i++)
	{
		scanf("%d%d",&l,&r);len=r-l+1;cnt=0;
		while(len!=1)
		{
			p[++cnt]=mnd[len];
			int f=mnd[len];
			while(!(len%f)) len/=f;
		}
		len=r-l+1;
		for(int j=1;j<=cnt;j++)
			while((!(len%p[j]))&&get_hsh(l,r-len/p[j])==get_hsh(l+len/p[j],r))
				len/=p[j];
		printf("%d\n",len);
	}
}