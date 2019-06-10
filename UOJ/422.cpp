#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=6;
const int MAXM=105;
const int P=998244353;

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

char str[MAXM];
int n,m,mp[MAXN+1][MAXM];
int f[2][1<<MAXN][MAXN*MAXM*2];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		for(int j=1;j<=m;j++)
			mp[i][j]=str[j]=='*';
	}
	int lst=0,lim=n*(m-1)+m*(n-1),ful=(1<<n)-1;
	f[0][ful][0]=P-1;
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
		{
			memset(f[!lst],0,sizeof f[!lst]);
			if(mp[i][j])
			{
				for(int k=0;k<=lim;k++)
					for(int s=0;s<1<<n;s++)
						if(f[lst][s][k])
						{
							//choose
							int dlt=4-(i==1?1:((s>>(i-2))&1))-((s>>(i-1))&1)-(i==n)-(j==m);
							Inc(f[!lst][s|(1<<(i-1))][k+dlt],P-f[lst][s][k]);
							//not choose
							Inc(f[!lst][s&(ful^(1<<(i-1)))][k],f[lst][s][k]);
						}
			}
			else
			{
				for(int k=0;k<=lim;k++)
					for(int s=0;s<1<<n;s++)
						if(f[lst][s][k])
							Inc(f[!lst][s&(ful^(1<<(i-1)))][k],f[lst][s][k]);
			}
			lst^=1;
		}
	}
	ll Ans=0;
	for(int s=0;s<1<<n;s++)
		for(int k=1;k<=lim;k++)
			if(f[lst][s][k])
				Inc(Ans,1ll*f[lst][s][k]*lim%P*ksm(k,P-2)%P);
	printf("%lld\n",Ans);
}
