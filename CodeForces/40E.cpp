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

const int MAXN=1010;

bool rev,f=1;
int n,m,k,P;
int ln[MAXN],cntl[MAXN],C[MAXN][MAXN];
ll Ans=1;

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	if((n&1)^(m&1)) return puts("0"),0;
	if(n<m) swap(n,m),rev=1;
	for(int i=1;i<=n;i++) ln[i]=1;
	for(int i=1,x,y,v;i<=k;i++)
	{
		scanf("%d%d%d",&x,&y,&v);
		if(rev) swap(x,y);
		cntl[x]++;ln[x]*=v;
	}
	scanf("%d",&P);
	for(int i=0;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	}
	for(int i=1;i<=n;i++)
		if(cntl[i]==m&&ln[i]==1)
			return puts("0"),0;
	for(int i=1,t;i<=n;i++)
	{
		if(f&&cntl[i]==0) {f=0;continue;}
		t=0;
		for(int j=ln[i]==1?1:0;j<=m-cntl[i];j+=2)
			(t+=C[m-cntl[i]][j])%=P;
		(Ans*=t)%=P;
	}
	printf("%lld\n",Ans);
}