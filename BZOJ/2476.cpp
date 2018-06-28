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

const int P=987654321;

int n;

struct Matrix{
    ll a[2][2];
    Matrix(){memset(a,0,sizeof a);}
    ll* operator [] (const int &i) {return a[i];}
    const ll * operator [] (const int &i) const {return a[i];}
    inline Matrix operator * (const Matrix &rhs) const 
    {
        Matrix ret;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
            {
                for(int k=0;k<2;k++)
                    ret[i][j]+=1ll*a[i][k]*rhs[k][j]%P;
                ret[i][j]%=P;
            }
        return ret;
    }
}M,A,res;

Matrix ksm(Matrix a,int b)
{
    Matrix ret,base=a;
    ret[0][0]=ret[1][1]=1;
    for(;b;base=base*base,b>>=1) if(b&1) ret=ret*base;
    return ret;
}

int main()
{
    A[0][0]=A[1][0]=1;
    M[0][0]=3;M[0][1]=P-1;
    M[1][0]=1;M[1][1]=0;
    while(scanf("%d",&n)&&n)
    {
        if(n&1) {puts("0");continue;}
        n>>=1;
        res=ksm(M,n-1)*A;
        printf("%lld\n",(res[1][0]-(n-1)+P)%P);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}