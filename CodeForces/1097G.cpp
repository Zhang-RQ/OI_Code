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

const int MAXN=2E5+10;
const int MAXK=210;
const int P=1E9+7;

int n,k,siz[MAXN];
vector<int> T[MAXN];
ll pw2[MAXN],f[MAXN][MAXK],S[MAXK][MAXK],fac[MAXK],tmp[MAXK],Anst[MAXK];

ll inc(ll x,ll y){x+=y;return x>=P?x-P:x;}

ll dec(ll x,ll y){x-=y;return x<0?x+P:x;}

void dfs(int x,int fa)
{
	siz[x]=1;f[x][0]=1;
	for(int v:T[x])
		if(v!=fa)
		{
			dfs(v,x);memcpy(tmp,f[x],sizeof tmp);
			for(int j=0;j<=min(siz[v],k);j++)
			{
				(f[x][j]+=f[v][j])%=P;
				if(j>=1) (f[x][j]+=f[v][j-1])%=P;
			}
			for(int j=0;j<=min(siz[x],k);j++)
				for(int l=0;l<=min(siz[v],k-j);l++)
				{
					(Anst[j+l]+=tmp[j]*f[v][l])%=P;
					(f[x][j+l]+=tmp[j]*f[v][l])%=P;
					(Anst[j+l+1]+=tmp[j]*f[v][l])%=P;
					(f[x][j+l+1]+=tmp[j]*f[v][l])%=P;
				}
			siz[x]+=siz[v];
		}
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),T[u].push_back(v),T[v].push_back(u);
	pw2[0]=1;S[0][0]=1;fac[0]=1;
	for(int i=1;i<=n;i++) pw2[i]=(pw2[i-1]<<1)%P;
	for(int i=1;i<=k;i++) fac[i]=fac[i-1]*i%P;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=i;j++)
			S[i][j]=(S[i-1][j-1]+j*S[i-1][j])%P;
	ll Ans=0;dfs(1,0);
	for(int i=0;i<=k;i++)
		(Ans+=Anst[i]*S[k][i]%P*fac[i]%P)%=P;
	printf("%lld\n",Ans);
}
