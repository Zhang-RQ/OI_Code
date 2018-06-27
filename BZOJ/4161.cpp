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

const int P=1000000007;
const int MAXN=4010;

int n,k,ans;
int f[MAXN],h[MAXN];

struct Matrix{
    int a[MAXN];
    Matrix (){memset(a,0,sizeof a);}
    int& operator [] (const int &i) {return a[i];}
    int operator [] (const int &i) const {return a[i];}
    inline Matrix operator * (const Matrix &rhs) const 
    {
        Matrix ret;
        for(int i=0;i<k;i++)
            for(int j=0;j<k;j++)
                (ret[i+j]+=1ll*a[i]*rhs[j]%P)%=P;
        for(int i=2*k-2;i>=k;ret[i--]=0) // notice ret[i--]=0
            for(int j=1;j<=k;j++)
                (ret[i-j]+=1ll*ret[i]*f[j]%P)%=P;
        return ret;
    }
}res;

Matrix ksm(Matrix a,int b) // 严格来说，不是快速幂
{
    Matrix ret;
    ret[0]=1;
    for(;b;a=a*a,b>>=1) if(b&1) ret=ret*a;
    return ret;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++) scanf("%d",&f[i]),f[i]=f[i]>0?f[i]:f[i]+P;
    for(int i=0;i<k;i++) scanf("%d",&h[i]),h[i]=h[i]>0?h[i]:h[i]+P;
    if(n<k) printf("%d\n",h[n]);
    res[1]=1;ans=0;
    res=ksm(res,n);
    for(int i=0;i<k;i++)  ans=(ans+1ll*res[i]*h[i]%P)%P;
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}