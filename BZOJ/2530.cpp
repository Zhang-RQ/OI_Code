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

const int MAXN=3010;

int n,m;
bool g[MAXN][MAXN],chk[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		g[u][v]=g[v][u]=1;
	}
	for(int i=1;i<=n;i++)
		if(!chk[i])
			for(int j=i+1;j<=n;j++)
				if(!chk[j]&&!g[i][j])
				{
					chk[i]=chk[j]=1;
					break;
				}
	for(int i=1,cnt=0;cnt<n/3;i++)
		if(!chk[i]) printf("%d\n",i),++cnt;
}