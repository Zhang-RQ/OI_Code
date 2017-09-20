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
int mp[110][110],F[110][110];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
        {
            int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=i;j++)
                scanf("%d",&mp[i][j]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=i;j++)
            {
                F[i][j]=max(F[i-1][j],F[i-1][j-1])+mp[i][j];
            }
        int ans=0;
        for(int i=1;i<=n;i++) ans=max(ans,F[n][i]);
        printf("%d\n",ans);
    }
}
