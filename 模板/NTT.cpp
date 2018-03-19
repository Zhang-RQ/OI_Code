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
const int P=((7*17)<<23)+1;
const int g=3;
int rev[100010<<3];
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
void NTT(ll *a,int n,bool flag)
{
    for(int i=0;i<=n;i++)
        if(rev[i]>i) swap(a[i],a[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        ll wn=ksm(g,flag?(P-1)/i:P-1-(P-1)/i);
        for(int j=0;j<n;j+=i)
        {
            ll w=1;
            for(int k=0;k<(i>>1);k++)
            {
                ll t=w*a[j+k+(i>>1)]%P;
                ll u=a[j+k]%P;
                a[j+k+(i>>1)]=(u-t+P)%P;
                a[j+k]=(u+t)%P;
                w=wn*w%P;
            }
        }
    }
}
int n,m,tot,lg2;
ll a[100010<<3],b[100010<<3],c[100010<<3];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=0;i<=m;i++) scanf("%lld",&b[i]);
    for(tot=1;tot<=n+m;tot<<=1,lg2++);
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    NTT(a,tot,0);NTT(b,tot,0);
    for(int i=0;i<tot;i++)
        c[i]=a[i]*b[i]%P;
    NTT(c,tot,1);
    ll inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++)
        c[i]=c[i]*inv%P;
    for(int i=0;i<n+m+1;i++)
        printf("%lld ",c[i]);
    puts("");
}
