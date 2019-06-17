#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=110;
const int MAXM=10100;
const ll Infi=0x3f3f3f3f3f3f3f3f;

ll Floor(ll a, ll b)
{
	if(b<0)
		a=-a,b=-b;
	if(a>0)
		return a/b;
	else
		return -((-a+b-1)/b);
}

ll Ceil(ll a, ll b)
{
	return -Floor(-a, b);
}

int n,m,U[MAXM],V[MAXM],W[MAXM],T[MAXM],ok[MAXN][MAXN];
ll f[2][MAXN][2*MAXN];
vector<pair<ll,ll> > Rn[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d%d",&U[i],&V[i],&W[i],&T[i]),ok[U[i]][V[i]]=1;
	for(int i=1;i<=n;i++)
		ok[i][i]=1;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				ok[i][j]|=ok[i][k]&&ok[k][j];
	memset(f,0x3f,sizeof f);
	int lst=0;f[lst][1][MAXN]=0;
	for(int _=1;_<=n;_++)
	{
		memcpy(f[!lst],f[lst],sizeof f[lst]);
		for(int i=1;i<=m;i++)
			for(int j=-n;j<=n;j++)
				if(f[lst][U[i]][j+MAXN]!=Infi&&f[!lst][V[i]][j+T[i]+MAXN]>f[lst][U[i]][j+MAXN]+W[i])
					f[!lst][V[i]][j+T[i]+MAXN]=f[lst][U[i]][j+MAXN]+W[i];
		lst^=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int k=-n;k<=n;k++)
			if(f[lst][i][k+MAXN]!=Infi)
			{
				ll L=-Infi,R=Infi;
				for(int j=-n;j<=n;j++)
					if(f[!lst][i][j+MAXN]!=Infi)
					{
						if(j==k)
						{
							if(f[!lst][i][j+MAXN]<=f[lst][i][k+MAXN])
								L=Infi,R=-Infi;
							continue;
						}
						if(k>j)
							R=min(R,Ceil(f[!lst][i][j+MAXN]-f[lst][i][k+MAXN],k-j));
						else
							L=max(L,Floor(f[!lst][i][j+MAXN]-f[lst][i][k+MAXN],k-j));
					}
				if(L+1<R)
				{
					for(int p=1;p<=n;p++)
						if(ok[i][p])
							Rn[p].emplace_back(L,R);
				}
			}
	}
	for(int i=1;i<=n;i++)
	{
		sort(Rn[i].begin(),Rn[i].end());
		Rn[i].erase(unique(Rn[i].begin(),Rn[i].end()),Rn[i].end());
		ll L=Infi,R=-Infi,MxR=-Infi+1,flag=0;
		if(!Rn[i].size()||Rn[i][0].first!=-Infi)
		{
			puts("-1");
			continue;
		}
		for(size_t j=0;j<Rn[i].size();j++)
		{
			if(Rn[i][j].first>=MxR)
			{
				L=MxR,R=Rn[i][j].first;
				flag=1;break;
			}
			else
				MxR=max(MxR,Rn[i][j].second);
		}
		if((!flag&&MxR!=Infi)||R-L+1>1E18)
		{
			puts("-1");
			continue;
		}
		if(L>R)
			puts("0");
		else
			printf("%lld\n",R-L+1);
			
	}
}
