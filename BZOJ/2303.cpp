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
const int P=1E9;

int n,m,k,x[MAXN],y[MAXN],v[MAXN],fa[MAXN<<1],dis[MAXN<<1]; //dis[x] refers to the dis between x and fa[x]

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

int find(int x)
{
	if(x==fa[x]) return x;
	int d=dis[x],rfa=fa[x];
	fa[x]=find(fa[x]);
	dis[x]=d^dis[rfa];
	return fa[x];
}

bool merge(int x,int y,int v)// y -> x
{
	int X=find(x),Y=find(y);
	if(X==Y) return (dis[x]^dis[y])==v;
	dis[Y]=dis[x]^dis[y]^v;
	fa[Y]=X;
	return true;
}

ll solve(int fl) // fl => (1,1)
{
	for(int i=1;i<=n+m;i++) fa[i]=i,dis[i]=0;
	fa[n+1]=1;
	for(int i=1;i<=k;i++)
	{
		if(x[i]==1&&y[i]==1)
		{
			if(fl!=v[i]) return 0;
		}
		else if(x[i]==1)
		{
			if(!merge(y[i]+n,1,v[i])) return 0;
		}
		else if(y[i]==1)
		{
			if(!merge(x[i],1,v[i])) return 0;
		}
		else if(x[i]%2||y[i]%2)
		{
			if(!merge(x[i],y[i]+n,fl^v[i])) return 0;
		}
		else if(!merge(x[i],y[i]+n,fl^v[i]^1)) return 0;
	}
	int cnt=0;
	for(int i=1;i<=n+m;i++) if(fa[i]==i) ++cnt;
	return ksm(2,cnt-1);
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++) scanf("%d%d%d",&x[i],&y[i],&v[i]);
	printf("%lld\n",(solve(0)+solve(1))%P);
}