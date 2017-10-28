#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,i,j,k,l;
int a[55][55],f[55][55][55][55];

int max(int a,int b,int c,int d)
{
	if (a<b) a=b;
	if (a<c) a=c;
	if (a<d) a=d;
	return a;
}

int main()
{
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;++i)
	  for (j=1;j<=m;++j)
	    scanf("%d",&a[i][j]);
	for (i=1;i<=n;++i)
	  for (j=1;j<=m;++j)
	    for (k=1;k<=n;++k)
	      for (l=1;l<=m;++l)
	        if (i!=k||j!=l||i==n&&j==m&&k==n&&l==m)
	          f[i][j][k][l]=max(f[i-1][j][k-1][l],f[i][j-1][k][l-1],f[i-1][j][k][l-1],f[i][j-1][k-1][l])+a[i][j]+a[k][l];
	printf("%d",f[n][m][n][m]);
}

/*#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int f[60][60][60];
int val[60][60];
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&val[i][j]);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            for(int k=j+1;k<=n;k++)
                f[i][j][k]=max(f[i][j-1][k],f[i-1][j][k])+max(f[i][j][k+1],f[i+1][j][k])+val[j][i]+val[k][i];
    f[1][1][1]=f[1][1][2];
    f[m][n][n]=f[m][n-1][n];
    printf("%d %d\n",f[1][1][1],f[m][n][n]);
}
*/
