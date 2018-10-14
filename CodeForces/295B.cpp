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

const int MAXN=510;

int n,a[MAXN];
ll d[MAXN][MAXN],Ans[MAXN];
bool vis[MAXN];

int main()
{
	memset(d,0x3f,sizeof d);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&d[i][j]);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),d[i][i]=0;
	for(int i=n;i;i--)
	{
		int p=a[i];vis[p]=1;
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(d[j][k]>d[j][p]+d[p][k])
					d[j][k]=d[j][p]+d[p][k];
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(d[j][k]<1E11&&vis[j]&&vis[k]) Ans[i]+=d[j][k];
	}
	for(int i=1;i<=n;i++)
		printf("%lld%c",Ans[i],i==n?'\n':' ');
}