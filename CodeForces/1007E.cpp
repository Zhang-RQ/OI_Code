#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=210;
const ll INF=1ll<<60;

int n,t,k;
ll f[MAXN][MAXN][2][2],lim[MAXN],dlt[MAXN],beg[MAXN],sdlt[MAXN],sbeg[MAXN];

void upd(ll &x,ll y){if(y<x) x=y;}

//f[i][j][x][y] 
//if x==1 times is j-1/2  there must be a train that takes people from station i at time j
//if y==1 have init people

ll Ceil(ll x,ll y)
{
	return (x+y-1)/y;
}

int main()
{
	scanf("%d%d%d",&n,&t,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld%lld",&beg[i],&dlt[i],&lim[i]);
	++n;lim[n]=1ll*(t+1)*k;beg[n]=dlt[n]=k;
	for(int i=1;i<=n;i++)
	{
		sbeg[i]=sbeg[i-1]+beg[i];
		sdlt[i]=sdlt[i-1]+dlt[i];
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=t;j++)
			for(int x=0;x<2;x++)
				for(int y=0;y<2;y++)
					f[i][j][x][y]=INF;
	for(int i=0;i<=n;i++)
		f[i][0][0][0]=f[i][0][0][1]=0;
	for(int i=0;i<=t;i++)
		f[0][i][0][0]=f[0][i][0][1]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=t;j++)
			for(int y=0;y<2;y++)
			{
				//x=1
				
				if(y*beg[i]+(j-1)*dlt[i]<=lim[i]&&f[i-1][j-1][0][y]!=INF)//first train pass station i
				{
					ll t1=y*beg[i]+(j-1)*dlt[i],t2=y*sbeg[i-1]+(j-1)*sdlt[i-1]-f[i-1][j-1][0][y]*k;
					ll cost=t2/k+1;
					if(cost*k-t2<=t1)
						upd(f[i][j][1][y],f[i-1][j-1][0][y]+cost);
				}
				for(int r=1;r<j;r++)
					if(f[i][r][1][y]!=INF&&f[i-1][j-r][0][0]!=INF)
					{
						ll t1=y*sbeg[i]+(r-1)*sdlt[i]-f[i][r][1][y]*k;
						ll t2=(j-r)*dlt[i],cost1=0;
						if(t1+t2>lim[i])
						{
							cost1=Ceil(t1+t2-lim[i],k);
							if(cost1*k>t1)
								continue;
							t1-=cost1*k;
						}
						t1+=t2;
						ll t3=(j-r)*sdlt[i-1]-f[i-1][j-r][0][0]*k;
						ll cost2=t3/k+1;
						ll now=k*cost2-t3;
						if(now<=t1)
							upd(f[i][j][1][y],f[i][r][1][y]+f[i-1][j-r][0][0]+cost1+cost2);
					}
				//x=0
				if(y*beg[i]+j*dlt[i]<=lim[i]&&f[i-1][j][0][y]!=INF)
					upd(f[i][j][0][y],f[i-1][j][0][y]);
				for(int r=y?1:2;r<=j;r++)
					if(f[i][r][1][y]!=INF&&f[i][j-r+1][0][0]!=INF)
					{
						ll t1=y*sbeg[i]+(r-1)*sdlt[i]-f[i][r][1][y]*k,cost=0;
						ll t2=(j-r+1)*dlt[i];
						if(t1+t2>lim[i])
						{
							ll cost2=Ceil(t1+t2-lim[i],k);
							if(cost2*k>t1)
								continue;
							t1-=cost2*k;
							cost+=cost2;
						}
						upd(f[i][j][0][y],f[i][r][1][y]+f[i][j-r+1][0][0]+cost);
					}
			}
	printf("%lld\n",f[n][t][0][1]==INF?-1:f[n][t][0][1]);
}
