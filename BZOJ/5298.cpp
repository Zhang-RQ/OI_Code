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
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int siz,P,n,m,a,b;
ll C[110][110],powv[210];
inline uint add(uint a,uint b)
{
    uint ret=a+b;
    return ret>P?ret%P:ret;
}
struct Matrix{
    uint a[181][181];
    Matrix(){memset(a,0,sizeof a);}
    inline uint* operator [] (const int &i) {return a[i];}
    inline const uint* operator [] (const int &i) const {return a[i];}
    inline Matrix operator*(const Matrix& rhs) const
    {
        Matrix ret;
        for(int i=1;i<=siz;++i)
            for(int j=1;j<=siz;++j)
            {
                ll sum=0;
                for(int k=1;k<=siz;++k)
                {
                    sum+=1ll*a[i][k]*rhs[k][j];
                    if(sum>=P) sum%=P;
                }
                ret[i][j]=sum%P;
            }
        return ret;
    }
}base,ans;
inline Matrix ksm(Matrix a,int b)
{
    Matrix ret;
    for(int i=1;i<=siz;i++) ret[i][i]=1;
    while(b)
    {
        if(b&1) ret=ret*a;
        a=a*a;b>>=1;
    }
    return ret;
}
int main()
{
    scanf("%d%d%d%d",&n,&a,&b,&P);
    powv[0]=1;
    for(int i=1;i<=a;i++) powv[i]=powv[i-1]*n%P;
    for(int i=0;i<=100;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
    }
    siz=(a+b+1)<<1;
    for(int i=1;i<=a+b+1;i++)
    {
        base[i][i]=1;
        base[i+a+b+1][i]=1;
        for(int j=1;j<=i;j++)
            base[j][i+a+b+1]=C[i-1][j-1];
    }
    ans[1][1]=1;
    ans=ans*ksm(base,n);
    ll tans=0;
    for(int i=0;i<=a;i++)
    {
        if(i&1) tans=(tans-C[a][i]*(ans[1][i+b+1]+ans[1][i+b+1+(a+b+1)])%P*powv[a-i]%P+P)%P;
        else tans=(tans+C[a][i]*(ans[1][i+b+1]+ans[1][i+b+1+(a+b+1)])%P*powv[a-i]%P+P)%P;
    }
    printf("%lld\n",tans);
    #ifdef LOCAL
        system("pause");
    #endif
}