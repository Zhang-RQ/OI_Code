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
typedef long long ll;
typedef unsigned long long ull;
#define P 1000000007LL
struct Matrix{
    ll val[5][5];
    Matrix operator *(const Matrix &a) const
    {
        Matrix ret;
        memset(ret.val,0,sizeof(ret.val));
        for(int i=0;i<=2;i++)
            for(int j=0;j<=2;j++)
                for(int k=0;k<=2;k++)
                    (ret.val[i][j]+=val[i][k]*a.val[k][j])%=P;
        return ret;
    }
};
Matrix ksm(Matrix a,int b)
{
    Matrix ret,base=a;
    memset(ret.val,0,sizeof(ret.val));
    for(int i=0;i<=2;i++) ret.val[i][i]=1;
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
    Matrix A;
    A.val[0][0]=1;A.val[0][1]=0;A.val[0][2]=1;
    A.val[1][0]=1;A.val[1][1]=0;A.val[1][2]=0;
    A.val[2][0]=0;A.val[2][1]=1;A.val[2][2]=0;
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        Matrix ans;
        memset(ans.val,0,sizeof(ans.val));
        ans.val[0][0]=ans.val[1][0]=ans.val[2][0]=1;
        ans=ans*ksm(A,n-1);
        printf("%lld\n",ans.val[0][0]);
    }
}
