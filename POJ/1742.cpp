#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;

int A[110],C[110];
int n,m;
int DP[100010];//表示前i种硬币，当前金额为j的i的剩余数量

int main()
{
    while(~scanf("%d%d",&n,&m)&&n&&m)
    {
        int ans=0;
        for(int i=1;i<=n;i++)    scanf("%d",&A[i]);
        for(int i=1;i<=n;i++)    scanf("%d",&C[i]);
        memset(DP,-1,sizeof(DP));
        DP[0]=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<=m;j++)
            {
                if(DP[j]>=0) DP[j]=C[i];
                else if(j<A[i]||DP[j-A[i]]<=0) DP[j]=-1;
                else DP[j]=DP[j-A[i]]-1;
            }
        }
        for(int j=1;j<=m;j++) if(DP[j]>=0) ++ans;
        printf("%d\n",ans);
    }
}
