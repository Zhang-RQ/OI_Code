/*#include<cstdio>
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
ll N,M=0x3f3f3f3f3;
struct Matrix{
    ll val[5][5];
    friend Matrix operator * (Matrix a,Matrix b)
    {
        Matrix ret;
        ret={{0}};
        for(int i=1;i<=3;i++)
            for(int j=1;j<=3;j++)
                for(int k=1;k<=3;k++)
                    (ret.val[i][j]+=(a.val[i][k]*b.val[k][j])%M)%=M;
        return ret;
    }
    friend Matrix operator ^ (Matrix base,ll a)
    {
        Matrix ret;
        ret={{0}};
        for(int i=1;i<=3;i++)
            ret.val[i][i]=1;
        if(a<=0)
            return ret;
        while(a)
        {
            if(a&1) ret=ret*base;
            base=base*base;
            a>>=1;
        }
        return ret;
    }
};
int len10(int x)
{
    int ret=0;
    while(x)
        ret++,x/=10;
    return ret;
}
ll poww10(ll x)
{
    ll ret=1,base=10;
    while(x)
    {
        if(x&1) (ret*=base)%=M;
        (base*=base)%=M;
        x>>=1;
    }
    return ret%M;
}
ll calc(ll l,ll r)
{
    int len=len10(l);
    Matrix ans;
    ans.val[1][1]=ans.val[1][2]=l;
    ans.val[1][3]=1;
    Matrix base={{0}};
    base.val[1][1]=poww10(len);
    base.val[2][1]=base.val[2][2]=1;
    base.val[3][1]=base.val[3][2]=base.val[3][3]=1;
    ans=ans*(base^(r-l-1));
    ans=ans*base;
    return ans.val[1][1]%M;
}
int main()
{
    scanf("%lld%lld",&N,&M);
    ll ans=0;
    int len=len10(N);
    for(int i=1;i<=len-1;i++)
    {
        (ans*=poww10(((poww10(i)-1-poww10(i-1)+1)*i)%M))%=M;
        (ans+=calc(poww10(i-1),poww10(i)-1))%=M;
    }
    (ans*=poww10(((N-poww10(len-1)+1)*len)%M))%=M;
    (ans+=calc(poww10(len-1),N))%=M;
    printf("%lld\n",ans);
}*/
