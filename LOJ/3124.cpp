#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int MAXN=1010;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

int n,siz[MAXN];
ll p[4][MAXN],f[MAXN][3*MAXN],nf[3*MAXN],inv[3*MAXN];
vector<pair<int,int> > T[MAXN];

void dfs(int x,int fa)
{
	siz[x]=1;
	f[x][1]=p[1][x];
	f[x][2]=2ll*p[2][x]%P;
	f[x][3]=3ll*p[3][x]%P;
	for(auto e:T[x])
		if(e.first!=fa)
		{
			int v=e.first;
			dfs(v,x);
			if(!e.second)
			{
				memset(nf,0,sizeof nf);
				for(int i=1;i<=3*siz[x];i++)
					for(int j=1;j<=3*siz[v];j++)
						nf[i+j]=(nf[i+j]+f[x][i]*f[v][j])%P;
				memcpy(f[x],nf,sizeof nf);
			}
			else
			{
				memset(nf,0,sizeof nf);
				//not choose
				ll s=0;
				for(int i=1;i<=3*siz[v];i++)
					Inc(s,f[v][i]);
				for(int i=1;i<=3*siz[x];i++)
					nf[i]=f[x][i]*s%P;
				//choose
				for(int i=1;i<=3*siz[x];i++)
					for(int j=1;j<=3*siz[v];j++)
						Dec(nf[i+j],f[x][i]*f[v][j]%P);
				memcpy(f[x],nf,sizeof nf);
			}
			siz[x]+=siz[v];
		}
	for(int i=1;i<=3*siz[x];i++)
		f[x][i]=f[x][i]*inv[i]%P;
}

int main()
{
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<=3*n;i++)
		inv[i]=(P-P/i)*inv[P%i]%P;
	for(int i=1,s;i<=n;i++)
	{
		scanf("%lld%lld%lld",&p[1][i],&p[2][i],&p[3][i]);
		s=p[1][i]+p[2][i]+p[3][i];
		s=ksm(s,P-2);
		p[1][i]=p[1][i]*s%P;
		p[2][i]=p[2][i]*s%P;
		p[3][i]=p[3][i]*s%P;
	}
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		T[v].emplace_back(u,1);
		T[u].emplace_back(v,0);
	}
	dfs(1,0);
	ll Ans=0;
	for(int i=1;i<=3*n;i++)
		Inc(Ans,f[1][i]);
	printf("%lld\n",Ans);
}
