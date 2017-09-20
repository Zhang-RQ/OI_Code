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
typedef long long ll;

ll F1[1010][1010];//left up
ll F2[1010][1010];// right up
ll F3[1010][1010];//left down
ll F4[1010][1010];// right down
ll mp[1010][1010];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            F1[i][j]=max(F1[i-1][j],F1[i][j-1])+mp[i][j];
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
            F2[i][j]=max(F2[i-1][j],F2[i][j+1])+mp[i][j];
    for(int i=n;i>=1;i--)
        for(int j=1;j<=m;j++)
            F3[i][j]=max(F3[i+1][j],F3[i][j-1])+mp[i][j];
    for(int i=n;i>=1;i--)
        for(int j=m;j>=1;j--)
            F4[i][j]=max(F4[i+1][j],F4[i][j+1])+mp[i][j];
    ll ans=0;
    for(int i=2;i<n;i++)
        for(int j=2;j<m;j++)
        {
            ll tmp=max(F1[i][j-1]+F4[i][j+1]+F2[i-1][j]+F3[i+1][j],F1[i-1][j]+F4[i+1][j]+F2[i][j+1]+F3[i][j-1]);
            ans=max(ans,tmp);
        }
    printf("%lld\n",ans);
}
