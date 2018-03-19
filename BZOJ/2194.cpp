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
ll a[262200],b[262200],c[262200];
int rev[262200];
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
int n,tot,lg2,inv;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%lld%lld",&a[i],&b[i]);
    reverse(b,b+n);
    for(tot=1;tot<=2*n;tot<<=1,lg2++);
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    NTT(a,tot,1);NTT(b,tot,1);
    for(int i=0;i<tot;i++)
        c[i]=a[i]*b[i]%P;
    NTT(c,tot,0);
    inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++)
        c[i]=c[i]*inv%P;
    for(int i=n-1;i<n*2-1;i++)
        printf("%lld\n",c[i]);
}
