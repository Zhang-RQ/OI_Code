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

const int P=2333;

int c[P][P],f[P][P];

void init()
{
    c[0][0]=1;
    for(int i=1;i<P;i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++)
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
    }
    for(int i=0;i<P;i++)
    {
        f[i][0]=c[i][0];
        for(int j=1;j<P;j++)
            f[i][j]=(f[i][j-1]+c[i][j])%P;
    }
}

inline int C(ll n,ll m)
{
    if(m<0||m>n) return 0;
    if(n<P) return c[n][m];
    return C(n/P,m/P)*c[n%P][m%P]%P;
}

inline int F(ll n,ll m)
{
    if(m<0) return 0;
    ll a=n/P,b=m/P;
    return (F(a,b-1)*f[n%P][P-1]+C(a,b)*f[n%P][m%P])%P;
}

inline void solve()
{
    ll n,m;
    scanf("%lld%lld",&n,&m);
    printf("%d\n",F(n,m));
}

int main()
{
    int T;init();
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}