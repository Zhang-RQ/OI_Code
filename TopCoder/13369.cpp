#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=110;
const int P=1E9+7;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n,k,siz[MAXN];
ll f[MAXN][MAXN][MAXN],inv[MAXN],tmp[MAXN][MAXN],fac[MAXN],ifac[MAXN],g[MAXN],h[MAXN];
vector<int> T[MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll calc(int n)
{
	if(n<=2) return 1;
	return ksm(n,n-2);
}

ll C(int n,int m)
{
	if(n<0||m<0||n<m) return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

void dfs(int x)
{
	f[x][0][1]=1;
	siz[x]=1;
	for(int v:T[x])
	{
		dfs(v);
		memset(tmp,0,sizeof tmp);
		for(int j1=0;j1<siz[x];j1++)
			for(int j2=0;j2<siz[v];j2++)
				for(int k1=1;k1<=siz[x];k1++)
					for(int k2=1;k2<=siz[v];k2++)
					{
						Inc(tmp[j1+j2+1][k1],f[x][j1][k1]*f[v][j2][k2]%P);
						Inc(tmp[j1+j2][k1+k2],f[x][j1][k1]*f[v][j2][k2]%P*inv[k1]%P*inv[k2]%P*(k1+k2)%P);
					}
		memcpy(f[x],tmp,sizeof tmp);
		siz[x]+=siz[v];
	}
}

class TreeDistance{
public:
	int countTrees(vector<int> p,int k)
	{
		n=p.size()+1;
		fac[0]=ifac[0]=1;
		for(int i=1;i<=50;i++) fac[i]=fac[i-1]*i%P;
		ifac[50]=ksm(fac[50],P-2);
		for(int i=49;i;i--) ifac[i]=ifac[i+1]*(i+1)%P;
		for(int i=2,x;i<=n;i++) x=p[i-2],T[x+1].push_back(i);
		inv[1]=1;
		for(int i=2;i<=n;i++) inv[i]=Sub(P,P/i)*inv[P%i]%P;
		dfs(1);
		ll Ans=0;
		for(int i=1;i<n;i++)
			for(int j=1;j<=n;j++)
				Inc(g[i],f[1][i][j]*ksm(n,i-1)%P);
		reverse(g,g+n);
		h[n-1]=1;
		for(int i=n-2;~i;i--)
		{
			h[i]=g[i];
			for(int j=i+1;j<n;j++)
				Dec(h[i],h[j]*C(j,i)%P);
		}
		for(int i=n-1;i>=n-1-k;i--)
			Inc(Ans,h[i]);
		return Ans;
	}
};
