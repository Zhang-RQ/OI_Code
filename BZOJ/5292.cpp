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
const int MAXN=1510;
const int P=1E9+7;
int T,n,m,p,k;
ll f[MAXN];
struct dat{
    ll x,y;
     dat(ll _x=0,ll _y=0):x(_x),y(_y){}
    inline dat operator + (const dat &b){return dat((x+b.x)%P,(y+b.y)%P);}
    inline dat operator - (const dat &b){return dat((x-b.x+P)%P,(y-b.y+P)%P);}
    inline dat operator * (const ll &b)  {return dat(x*b%P,y*b%P);}
}dp[MAXN];
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;b>>=1;
    }
    return ret;
}
void solve1()
{
    if(k==1&&n!=1) return printf("-1\n"),void();
    f[0]=0;
    for(int i=1;i<n;i++)
        f[i]=f[max(i+1-k,0)]+1;
    f[n]=f[max(n-k,0)]+1;
    return printf("%lld\n",f[p]),void();
}
void solve()
{
    scanf("%d%d%d%d",&n,&p,&m,&k);
    if(k==0) return printf("-1\n"),void();
    if(!m) return solve1();
    ll invm=ksm(m,P-2),x=min(k,n);
    f[0]=ksm(m*ksm(m+1,P-2)%P,k);if(f[0]==0||f[0]==1) return printf("-1\n"),void();
    for(int i=1;i<=x;i++)f[i]=f[i-1]*(k-i+1)%P*ksm(i,P-2)%P*invm%P;
    ll finv=ksm(f[0],P-2);
    dp[0]=dat(0,0),dp[1]=dat(1,0);
    for(int i=1;i<n;i++)
    {
        dp[i+1]=dat(dp[i].x,dp[i].y-1)*(m+1);
        x=min(i,k);
        for(int j=0;j<=x;j++)dp[i+1]=dp[i+1]-(dp[i-j]*f[j])*m;
        x=min(i+1,k);
        for(int j=1;j<=x;j++)dp[i+1]=dp[i+1]-dp[i+1-j]*f[j];
        dp[i+1]=dp[i+1]*finv;
    }
    dat t=dat(0,1);x=min(n,k);
    for(int j=1;j<=x;j++)t=t+dp[n-j]*f[j];
    t=t*ksm(1-f[0]+P,P-2),t=t-dp[n];
    if(t.x==0&&dp[p].x) return printf("-1\n"),void();
    ll X=0;if(t.x)X=(P-t.y)*ksm(t.x,P-2)%P;
    return printf("%lld\n",(dp[p].x*X%P+dp[p].y)%P),void();
}
int main()
{
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}