%:pragma GCC optimize(3)
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
double F[5][5010];
int main()
{
    int r,b;
    int p=0;
    scanf("%d%d",&r,&b);
    for(int i=1;i<=r;i++)
    {
        p^=1;
        F[p][0]=i;
        for(int j=1;j<=b;j++)
        {
            F[p][j]=max(0.0,(F[p^1][j]+1)*(1.0*i/(i+j))+(F[p][j-1]-1)*(1.0*j/(i+j)));
        }
    }
    int tmp=F[p][b]*1e6;
    printf("%lf\n",tmp/1e6);
}
