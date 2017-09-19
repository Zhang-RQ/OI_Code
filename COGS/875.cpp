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
char mp[260][260];
int sum[260][260];
int cnt[260];
int main()
{
    freopen("range.in","r",stdin);
    freopen("range.out","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",mp[i]+1);
        for(int j=1;j<=n;j++)
        {
            mp[i][j]-='0';
            sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+mp[i][j];
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            for(int len=2;len-1<=min(n-i,n-j);len++)
            {
                if(mp[i][j]&&sum[i+len-1][j+len-1]-sum[i+len-1][j-1]-sum[i-1][j+len-1]+sum[i-1][j-1]==len*len)
                    cnt[len]++;
            }
        }
    for(int i=2;i<=n;i++)
    {
        if(cnt[i]) printf("%d %d\n",i,cnt[i]);
    }
}
