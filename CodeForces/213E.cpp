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

const int P=998244353;
const int MAXN=2E5+10;
const int base=10;

map<ll,int> mp;

int n,m,a[MAXN],b[MAXN],pos[MAXN],siz[MAXN<<2],Ans;
ll pw[MAXN],spw[MAXN];
ll t[MAXN<<2];

void pushup(int x){t[x]=(t[x<<1]*pw[siz[x<<1|1]]%P+t[x<<1|1])%P;siz[x]=siz[x<<1]+siz[x<<1|1];}

void change(int x,int l,int r,int p,int val,int vv)
{
	if(l==r) return t[x]=val,siz[x]+=vv,void();
	int mid=(l+r)>>1;
	if(p<=mid) change(x<<1,l,mid,p,val,vv);
	else change(x<<1|1,mid+1,r,p,val,vv);
	pushup(x);
}

int main()
{
	scanf("%d%d",&n,&m);pw[0]=1;spw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*base%P,spw[i]=(spw[i-1]+pw[i])%P;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]),pos[b[i]]=i;
	ll hsh=0;
	for(int i=1;i<=n;i++) hsh=(hsh*base%P+a[i])%P;
	for(int i=1;i<=m;i++)
	{
		change(1,1,m,pos[i],i,1);
		if(i>=n)
		{
			if((t[1]-(i-n)*spw[n-1]%P+P)%P==hsh)
				++Ans;
			change(1,1,m,pos[i-n+1],0,-1);
		}
	}
	printf("%d\n",Ans);
}