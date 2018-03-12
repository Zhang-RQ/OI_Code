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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int P=1000000007;
int C[2010][2010],a[1010],n,m;
ll ans=0;
void init()
{
    for(int i=0;i<=2009;i++)
        C[i][0]=1;
    for(int i=1;i<=2009;i++)
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
}
int main()
{
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    for(int i=0,f=1;i<=n;i++,f=-f)
    {
        ll now=1;
        for(int j=1;j<=m;j++)
            now=now*C[a[j]+n-1-i][n-1-i]%P;
        ans=(ans+f*now*C[n][i])%P;
    }
    ans=(ans+P)%P;
    printf("%lld\n",ans);
}
