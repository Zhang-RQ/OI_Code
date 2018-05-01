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
const int MAXN=262150<<2;
const int P=998244353;
const int g=3;
inline ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;b>>=1;
    }
    return ret;
}
int rev[MAXN];
ll t1[MAXN],t2[MAXN],res[MAXN],a[MAXN],t[MAXN],tx[MAXN];
inline void NTT(ll *a,int n,int f)
{
    for(int i=0;i<n;i++) if(i>rev[i]) swap(a[i],a[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        ll wn=ksm(g,f?(P-1)/i:P-1-(P-1)/i);
        for(int j=0;j<n;j+=i)
        {
            ll w=1;
            for(int k=0;k<(i>>1);k++)
            {
                ll u=a[j+k]%P,t=a[j+k+(i>>1)]*w%P;
                a[j+k]=(u+t)%P;a[j+k+(i>>1)]=(u-t+P)%P;
                (w*=wn)%=P;
            }
        }
    }
}
void multiply(ll *a,ll *b,ll *res,int n)  //x^0...x^(n-1)
{
    int tot=1,lg2=0;
    while(tot<=n*2) tot<<=1,lg2++;
    for(int i=0;i<n;i++) t1[i]=a[i];
    for(int i=0;i<n;i++) t2[i]=b[i];
    for(int i=n;i<tot;i++) t1[i]=t2[i]=0;
    for(int i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    NTT(t1,tot,1);NTT(t2,tot,1);
    for(int i=0;i<tot;i++) res[i]=t1[i]*t2[i]%P;
    NTT(res,tot,0);
    ll inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++) (res[i]*=inv)%=P;
}
void solve(int n)
{
    res[0]=ksm(a[0],P-2);
    int l=1;  //mod x^l
    while(l<n)
    {
        for(int i=0;i<l;i++) t[i]=res[i];
        for(int i=0;i<l;i++) (res[i]*=2)%=P;
        multiply(t,t,t,l);
        multiply(a,t,tx,l<<1);
        for(int i=0;i<(l<<1);i++)  res[i]=(res[i]-tx[i]+P)%P;
        l<<=1;
    }
}
int main()
{
    int n=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%lld",&a[i]);
    solve(n);
    for(int i=0;i<n;i++) printf("%lld ",res[i]);
    puts("");
}
