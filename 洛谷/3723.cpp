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
const int MAXN=262440;
const int P=998244353;
const int g=3;
int rev[MAXN],C,n,m,x[MAXN],y[MAXN],sumx,sumy,tot=1,lg2;
ll a[MAXN],b[MAXN],c[MAXN],ans=0,mx;
ll ksm(ll a,ll b)
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
void NTT(ll *a,int n,int f)
{
    for(int i=0;i<n;i++)
        if(rev[i]>i) swap(a[rev[i]],a[i]);
    for(int i=2;i<=n;i<<=1)
    {
        ll wn=ksm(g,f?(P-1)/i:(P-1)-(P-1)/i);
        for(int j=0;j<n;j+=i)
        {
            ll w=1;
            for(int k=0;k<(i>>1);k++)
            {
                ll u=a[j+k]%P,t=a[j+k+(i>>1)]*w%P;
                a[j+k]=(u+t)%P;
                a[j+k+(i>>1)]=(u-t+P)%P;
                w=w*wn%P;
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]),sumx+=x[i],ans+=x[i]*x[i];
    for(int i=1;i<=n;i++) scanf("%d",&y[i]),sumy+=y[i],ans+=y[i]*y[i];
    while(tot<=n+n) tot<<=1,lg2++;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    if(sumy-sumx>=0) C=(int)(1.0*(sumy-sumx)/n+0.5);
    if(sumy-sumx<0) C=(int)(1.0*(sumy-sumx)/n-0.5);
    ans+=1ll*n*C*C+2ll*C*(sumx-sumy);
    for(int i=0;i<n;i++) a[i]=x[i+1];
    for(int i=0;i<n;i++) b[i]=y[n-i];
    for(int i=0;i<n;i++) b[i+n]=y[n-i];
    NTT(a,tot,1);NTT(b,tot,1);
    for(int i=0;i<tot;i++) c[i]=a[i]*b[i]%P;
    NTT(c,tot,0);
    int inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++) (c[i]*=inv)%=P;
    for(int i=n-1;i<2*n-1;i++) mx=max(mx,c[i]);
    ans-=2*mx;
    printf("%lld\n",ans);
}
