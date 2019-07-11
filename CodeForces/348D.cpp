#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3010;
const int P=1E9+7;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n,m,f[MAXN][MAXN];
char mp[MAXN][MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	ll Ans1=0,Ans2=0,Ans3=0,Ans4=0;
	/*
	  [Ans1,Ans2]
	  [Ans3,Ans4]
	 */
	if(mp[2][1]!='#')
	{
		f[2][1]=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(mp[i][j]=='.')
					Inc(f[i][j],Add(f[i-1][j],f[i][j-1]));
		Ans1=f[n][m-1];Ans2=f[n-1][m];
	}
	if(mp[1][2]!='#')
	{
		memset(f,0,sizeof f);
		f[1][2]=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(mp[i][j]=='.')
					Inc(f[i][j],Add(f[i-1][j],f[i][j-1]));
		Ans3=f[n][m-1];Ans4=f[n-1][m];
	}
	printf("%lld\n",Sub(1ll*Ans1*Ans4%P,1ll*Ans2*Ans3%P));
}
