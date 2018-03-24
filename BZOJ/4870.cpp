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
int n,p,k,r;
struct Matrix{
    ll a[55][55];
    inline ll* operator [] (const int &x) {return a[x];}
    inline Matrix operator * (const Matrix &rhs)
    {
        Matrix ret;
        memset(&ret,0,sizeof ret);
        for(int i=0;i<=50;i++)
            for(int j=0;j<=50;j++)
                for(int k=0;k<=50;k++)
                    (ret[i][j]+=a[i][k]*rhs.a[k][j])%=p;
        return ret;
    }
}ans,tt;
inline Matrix ksm(Matrix a,ll b)
{
    Matrix ret;
    memset(&ret,0,sizeof ret);
    for(int i=0;i<=50;i++)
        ret[i][i]=1;
    while(b)
    {
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}
int main()
{
    scanf("%d%d%d%d",&n,&p,&k,&r);
    for(int i=0;i<=k-1;i++)
        tt[i][i]++,tt[i][(i-1+k)%k]++;
    ans[0][0]=1;
    ans=ksm(tt,1ll*n*k)*ans;
    printf("%lld\n",ans[r][0]%p);
}
