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

ll n,m;
int P,K,c[16],b[16];

struct Matrix{
    ll val[16][16];
    ll* operator [] (const int &i) {return val[i];}
    const ll * operator [] (const int &i) const {return val[i];}
    inline Matrix operator *(const Matrix &a) const
    {
        Matrix ret;
        memset(ret.val,0,sizeof(ret.val));
        for(int i=0;i<=K;i++)
            for(int j=0;j<=K;j++)
            {
                for(int k=0;k<=K;k++)
                    ret[i][j]+=val[i][k]*a[k][j];
                ret[i][j]%=P;
            }
        return ret;
    }
    inline void print()
    {
        for(int i=0;i<=15;i++)
            for(int j=0;j<=15;j++)
                printf("%lld%c",val[i][j],j==15?'\n':' ');
        puts("");
    }
}S,B;

inline Matrix ksm(Matrix a,ll b)
{
    Matrix ret,base=a;
    memset(ret.val,0,sizeof(ret.val));
    for(int i=0;i<=K;i++) ret.val[i][i]=1;
    while(b)
    {
        if(b&1) ret=base*ret;
        base=base*base;
        b>>=1;
    }
    return ret;
}

ll calc(ll n)
{
    if(n<=K) return b[n];
    Matrix T=ksm(B,n-K)*S;
    return (T[0][1]+b[K])%P;
}

int main()
{
    scanf("%d",&K);
    for(int i=1;i<=K;i++) scanf("%d",&b[i]);
    for(int i=1;i<=K;i++) scanf("%d",&c[i]);
    scanf("%lld%lld%d",&m,&n,&P);
    for(int i=1;i<=K;i++) S[i][1]=b[K-i+1];
    for(int i=1;i<=K;i++) b[i]+=b[i-1];
    for(int i=1;i<=K;i++) B[0][i]=B[1][i]=c[i];
    for(int i=2;i<=K;i++) B[i][i-1]=1;
    B[0][0]=1;
    printf("%lld\n",((calc(n)-calc(m-1))%P+P)%P);
    #ifdef LOCAL
        system("pause");
    #endif
}