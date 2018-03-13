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
const int MAXT=210;
ll f[MAXT];
struct Point{
    ll x,y;
    bool operator <(const Point &rhs) const
    {
        if(x!=rhs.x) return x<rhs.x;
        return y<rhs.y;
    }
}pnt[MAXT];
ll ksm(ll a,ll b,ll P)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;
        b>>=1;
    }
    return ret;
}
namespace P1{
    using namespace P1;
    const int P=1000003;
    ll fac[P],ifac[P];
    void init()
    {
        fac[0]=1;
        for(int i=1;i<P;i++)
            fac[i]=fac[i-1]*i%P;
        ifac[P-1]=ksm(fac[P-1],P-1,P);
        for(int i=P-2;~i;i--)
            ifac[i]=ifac[i+1]*(i+1)%P;
    }
    ll Lucas(ll n,ll m)
    {
        if(n<m) return 0;
        if(n<P&&m<P) return fac[n]*ifac[m]%P*ifac[n-m];
        return Lucas(n%P,m%P)*Lucas(n/P,m/P)%P;
    }
    void solve(int t)
    {
        init();
        for(int i=1;i<=t;i++)
        {
            ll sum=0;
            for(int j=1;j<i;j++)
                (sum+=Lucas(pnt[i].x-pnt[j].x+pnt[i].y-pnt[j].y,pnt[i].x-pnt[j].x)*f[j])%=P;
            f[i]=(Lucas(pnt[i].x+pnt[i].y,pnt[i].x)-sum+P)%P;
        }
        printf("%lld\n",f[t]);
    }
}
namespace P2{
    using namespace P2;
    const int P[]={3,5,6793,10007};
    ll fac[4][10007],ifac[4][10007];
    ll __Lucas(ll n,ll m,ll P_num)
    {
        if(n<m) return 0;
        if(n<P[P_num]&&m<P[P_num]) return fac[P_num][n]*ifac[P_num][m]%P[P_num]*ifac[P_num][n-m]%P[P_num];
        return __Lucas(n%P[P_num],m%P[P_num],P_num)*__Lucas(n/P[P_num],m/P[P_num],P_num)%P[P_num];
    }
    void init()
    {
        fac[0][0]=fac[1][0]=fac[2][0]=fac[3][0]=1;
        fac[0][1]=1;fac[0][2]=2;ifac[0][0]=ifac[0][1]=1;ifac[0][2]=2;
        for(int i=1;i<=3;i++)
        {
            for(int j=1;j<P[i];j++)
                fac[i][j]=fac[i][j-1]*j%P[i];
            ifac[i][P[i]-1]=ksm(fac[i][P[i]-1],P[i]-2,P[i]);
            for(int j=P[i]-2;~j;j--)
                ifac[i][j]=ifac[i][j+1]*(j+1)%P[i];
        }
    }
    ll Lucas(ll n,ll m)
    {
        return (__Lucas(n,m,0)*339887755%1019663265+__Lucas(n,m,1)*203932653%1019663265*2+__Lucas(n,m,2)*150105%1019663265*4484%1019663265+__Lucas(n,m,3)*101895%1019663265*6070%1019663265)%1019663265;
    }
    void solve(int t)
    {
        init();
        f[0]=1;
        for(int i=1;i<=t;i++)
        {
            ll sum=0;
            for(int j=1;j<i;j++)
                (sum+=Lucas(pnt[i].x-pnt[j].x+pnt[i].y-pnt[j].y,pnt[i].x-pnt[j].x)*f[j])%=1019663265;
            f[i]=(Lucas(pnt[i].x+pnt[i].y,pnt[i].x)-sum+1019663265)%1019663265;
        }
        printf("%lld\n",f[t]);
    }
}
ll n,m,t,P;
int main()
{
    scanf("%lld%lld%lld%lld",&n,&m,&t,&P);
    for(int i=1;i<=t;i++)
        scanf("%lld%lld",&pnt[i].x,&pnt[i].y);
    pnt[++t].x=n;pnt[t].y=m;
    sort(pnt+1,pnt+1+t);
    if(P==1019663265) P2::solve(t);
    else P1::solve(t);
}
