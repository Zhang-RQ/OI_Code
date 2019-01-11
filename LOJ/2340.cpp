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
#include<bitset>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int MAXN=25;

bool G[MAXN][MAXN];
int d[MAXN],W[MAXN],Cnt[1<<21];
int f[MAXN][1<<21],g[MAXN][1<<21],n,m,p,fa[MAXN],inv[2500],Sum[1<<21],Ans;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

int calc(int x)
{
	if(p==0) return 1;
	else if(p==1) return x;
	else if(p==2) return 1ll*x*x%P;
	return 0;
}

int chk_bit(int S,int b){return (S>>b)&1;}

int inc(int x,int y) {x+=y;return x>=P?x-P:x;}

int dec(int x,int y) {x-=y;return x<0?x+P:x;}

void FWT(int *a,int n)
{
	for(int i=2;i<=n;i<<=1)
		for(int j=0;j<n;j+=i)
			for(int k=0;k<(i>>1);k++)
			{
				int u=a[j+k],t=a[j+k+(i>>1)];
				a[j+k]=u;a[j+k+(i>>1)]=inc(u,t);
			}
}

void IFWT(int *a,int n)
{
	for(int i=2;i<=n;i<<=1)
		for(int j=0;j<n;j+=i)
			for(int k=0;k<(i>>1);k++)
			{
				int u=a[j+k],t=a[j+k+(i>>1)];
				a[j+k]=u;a[j+k+(i>>1)]=dec(t,u);
			}
}

int check(int S)
{
	bool f=0;
	int fir=0;
	for(int i=1;i<=n;i++)
		if(chk_bit(S,i-1))
			fa[i]=i;
	for(int i=1;i<=n;i++)
		if(chk_bit(S,i-1))
		{
			fir=i;
			d[i]=0;Sum[S]+=W[i];
			for(int j=1;j<=n;j++)
				if(chk_bit(S,j-1))
					if(G[i][j])
						d[i]++,fa[find(i)]=find(j);
			f|=d[i]&1;
		}
	for(int i=1;i<=n;i++)
		if(chk_bit(S,i-1))
			f|=(find(i)!=find(fir));
	return calc(Sum[S])*f;
}

int main()
{
	scanf("%d%d%d",&n,&m,&p);
	inv[1]=1;
	for(int i=2;i<=2200;i++)
		inv[i]=1ll*(P-(P/i))*inv[P%i]%P;
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),G[u][v]=G[v][u]=1;
	for(int i=1;i<=n;i++) scanf("%d",&W[i]);
	for(int s=0;s<(1<<n);s++) Cnt[s]=Cnt[s>>1]+(s&1),g[Cnt[s]][s]=check(s);
	for(int i=0;i<=n;i++) FWT(g[i],1<<n);
	f[0][0]=1;FWT(f[0],1<<n);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
			for(int s=0;s<(1<<n);s++)
				f[i][s]=inc(f[i][s],1ll*g[i-j][s]*f[j][s]%P);
		IFWT(f[i],1<<n);
		for(int s=0;s<(1<<n);s++)
			f[i][s]=1ll*f[i][s]*calc(inv[Sum[s]])%P*(Cnt[s]==i?1:0);
		if(i==n) Ans=f[n][(1<<n)-1];
		FWT(f[i],1<<n);
	}
	printf("%d\n",Ans);
}