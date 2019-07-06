#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=924844033;
const int MAXN=2010;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n,k;
int f[2][MAXN][2];
ll fac[MAXN];

int main()
{
	scanf("%d%d",&n,&k);
	int lst=0;
	f[0][0][1]=1;fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%P;
	for(int r=1;r<=2*k;r++)
	{
		int tot=0,ed;
		for(int j=r;j<=n;j+=2*k)
			++tot,ed=j;
		if(!tot)
			break;
		for(int _=1;_<=tot;_++)
		{
			memset(f[!lst],0,sizeof f[!lst]);
			for(int j=0;j<=n;j++)
			{
				//f[lst][j][0]
				Inc(f[!lst][j+1][0],f[lst][j][0]);
				Inc(f[!lst][j+1][1],f[lst][j][0]);
				Inc(f[!lst][j][0],f[lst][j][0]);
				//f[lst][j][1]
				Inc(f[!lst][j+1][1],f[lst][j][1]);
				Inc(f[!lst][j][0],f[lst][j][1]);
			}
			lst^=1;
		}
		if(ed+k>n)
			for(int i=0;i<=n;i++)
				f[lst][i][1]=0;
		int fl=r+1<=k;
		for(int i=0;i<=n;i++)
			f[lst][i][fl]=Add(f[lst][i][0],f[lst][i][1]),
			f[lst][i][fl^1]=0;
	}
	ll Ans=0;
	for(int i=0;i<=n;i++)
		if(i&1)
			Dec(Ans,Add(f[lst][i][0],f[lst][i][1])*fac[n-i]%P);
		else
			Inc(Ans,Add(f[lst][i][0],f[lst][i][1])*fac[n-i]%P);
	printf("%lld\n",Ans);
}
