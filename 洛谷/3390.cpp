#include<cstdio>
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
#define P 1000000007LL
typedef long long ll;
int n;
struct Matrix{
    ll val[110][110];
    Matrix operator *(const Matrix &a) const
    {
        Matrix ret;
        memset(ret.val,0,sizeof(ret.val));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++)
                    (ret.val[i][j]+=val[i][k]*a.val[k][j])%=P;
        return ret;
    }
};
Matrix ksm(const Matrix &a,ll b)
{
    Matrix base=a,ret;
    memset(ret.val,0,sizeof(ret.val));
    for(int i=1;i<=n;i++) ret.val[i][i]=1;
    while(b)
    {
        if(b&1) ret=ret*base;
        base=base*base;
        b>>=1;
    }
    return ret;
}
int main()
{
    Matrix a,b;
    ll k;
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%lld",&a.val[i][j]);
    b=ksm(a,k);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<n;j++)
            printf("%lld ",b.val[i][j]);
        printf("%lld\n",b.val[i][n]);
    }
}
