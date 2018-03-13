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
const int P=1E9+9;
ll C[2010][2010],f[2010][2010],g[2010],fac[2010];
int a[2010],b[2010],n,k,lst[2010];
void init()
{
    for(int i=0;i<=2000;i++) C[i][0]=1;
    for(int i=1;i<=2000;i++)
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
    fac[0]=1;
    for(int i=1;i<=2000;i++)
        fac[i]=fac[i-1]*i%P;
}
int main()
{
    init();
    scanf("%d%d",&n,&k);
    k=(n+k)>>1;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    sort(a+1,a+1+n);sort(b+1,b+1+n);
    int l=1;
    for(int i=1;i<=n;i++)
    {
        while(l<=n&&a[i]>b[l]) l++;
        lst[i]=l-1;  // lst[i]表示最大的x使a[i]<b[x]
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=n;j++)
            f[i][j]=(f[i-1][j]+((lst[i]-(j-1))>0?f[i-1][j-1]*(lst[i]-(j-1)):0)%P)%P;
    for(int i=n;i>=k;i--)
    {
        ll sum=0;
        for(int j=i+1;j<=n;j++)
            (sum+=g[j]*C[j][i]%P)%=P;
        g[i]=(f[n][i]*fac[n-i]-sum+P)%P;
    }
    printf("%lld\n",g[k]);
}
