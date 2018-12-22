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

const int MAXN=1E6+10;

int f[MAXN][3],a[MAXN],n;

int main()
{
	memset(f,0x3f,sizeof f);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]++;
	f[1][a[1]]=0;
	for(int i=2;i<=n;i++)
		for(int j=0;j<=2;j++)
			for(int k=j;k<=2;k++)
				if(a[i]==k) f[i][k]=min(f[i][k],f[i-1][j]);
				else if(a[i]>k&&j==0) f[i][k]=min(f[i][k],f[i-1][j]+a[i]-k);
				else if(a[i]<k&&j==2) f[i][k]=min(f[i][k],f[i-1][j]+k-a[i]);
	int Ans=min(min(f[n][0],f[n][1]),f[n][2]);
	if(Ans==0x3f3f3f3f) puts("BRAK");
	else printf("%d\n",Ans);
}