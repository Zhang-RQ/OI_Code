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

int n,m;
int f[MAXN][MAXN][2];

int main()
{
	scanf("%d%d",&n,&m);
	f[0][0][1]=1;
	for(int i=1;i<=n;i++)
		f[0][i][0]=1;
	for(int i=0;i<m;i++)
		for(int j=0;j<=n;j++)
		{
			if(!j)
				Inc(f[i][j][1],f[i][j][0]),
				f[i][j][0]=0;
			//WB
			if(j)
				Inc(f[i+1][j][j==1],f[i][j][0]),
				Inc(f[i+1][j][1],f[i][j][1]);
			//BW
			if(n-j)
				Inc(f[i+1][j][0],f[i][j][0]),
				Inc(f[i+1][j][1],f[i][j][1]);
			//WW
			if(j)
				Inc(f[i+1][j-1][j==1],f[i][j][0]),
				Inc(f[i+1][j-1][1],f[i][j][1]);
			//BB
			if(n-j)
				Inc(f[i+1][j+1][0],f[i][j][0]),
				Inc(f[i+1][j+1][1],f[i][j][1]);
		}
	ll Ans=0;
	for(int i=0;i<=n;i++)
		Inc(Ans,f[m][i][1]);
	printf("%lld\n",Ans);
}
