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
const int MAXN=22;
const int P=100000007;
const double EPS=1E-7;
int f[21][1<<20];
int n,x[MAXN],y[MAXN],stk[MAXN];
int ful[MAXN][MAXN];
ll ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&x[i],&y[i]);
    for(int i=1,xx,yy,_xx,_yy;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            for(int k=1;k<=n;k++)
            {
                if(i==k||j==k) continue;
                xx=x[k]-x[i];yy=y[k]-y[i];
                _xx=x[k]-x[j];_yy=y[k]-y[j];
                if(fabs(1.0*(xx*_xx)+(yy*_yy)+sqrt(xx*xx+yy*yy)*sqrt(_xx*_xx+_yy*_yy))<EPS)
                    ful[i][j]|=1<<(k-1);
            }
        }
    for(int i=0;i<n;i++)
        f[i+1][1<<i]=1;
    for(int s=0,cnt;s<1<<n;s++)
    {
        cnt=0;
        for(int i=0;i<n;i++)
            if((s>>i)&1)  ++cnt;
        for(int i=1;i<=n;i++)
        {
            if(!((s>>(i-1))&1)) continue;
            for(int j=1;j<=n;j++) // i-->j
            {
                if(i==j||((s>>(j-1))&1)) continue;
                if((s&ful[i][j])==ful[i][j])
                    (f[j][s|1<<(j-1)]+=f[i][s])%=P;
            }
            if(cnt>=4) (ans+=f[i][s])%=P;
        }
    }
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}