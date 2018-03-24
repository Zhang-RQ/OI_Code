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
const int MAXN=50010;
int n,m,P,c,phi[10010],k;
namespace Primes{
    int prime[10010],tot;
    bool vis[10010];
    void init()
    {
        for(int i=2;i<=10000;i++)
        {
            if(!vis[i]) prime[++tot]=i;
            for(int j=1;j<=tot&&i*prime[j]<=10000;j++)
            {
                vis[i*prime[j]]=1;
                if(i%prime[j]) break;
            }
        }
    }
}
int get_phi(int x)
{
    using Primes::tot;using Primes::prime;
    ll ret=x;
    for(int i=1;i<=tot&&prime[i]*prime[i]<=x;i++)
        if(x%prime[i]==0)
        {
            ret=ret-ret/prime[i];
            while(x%prime[i]==0) x/=prime[i];
        }
    if(x>1) ret=ret-ret/x;
    return ret;
}
int t[MAXN<<2],tag[MAXN<<2],a[MAXN],op,l,r;
inline int ksm(int a,int b,int _P,bool &ss)
{
    int ret=1;
    bool big=0;
    while(b)
    {
        if(b&1) ss|=(1ll*ret*a>=_P)|big,ret=1ll*ret*a%_P;
        if(1ll*a*a>=_P) big=1;
        a=1ll*a*a%_P;b>>=1;
    }
    return ret;
}
inline int calc(int x,int dep)
{
    int ret=x;
    if(ret>=phi[dep]) ret=ret%phi[dep]+phi[dep];
    while(dep)
    {
        --dep;
        bool ok=0;
        ret=ksm(c,ret,phi[dep],ok);
        if(ok) ret+=phi[dep];
    }
    return ret;
}
inline void pushup(const int &x)
{
    t[x]=(t[x<<1]+t[x<<1|1])%P;
    tag[x]=min(tag[x<<1],tag[x<<1|1]);
}
void build(int x,int l,int r)
{
    if(l==r) {t[x]=a[l];tag[x]=0;return;}
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    pushup(x);
}
void change(int x,int l,int r,int cl,int cr)
{
    if(tag[x]>=k) return;
    if(l==r)
    {
        tag[x]++;
        t[x]=calc(a[l],tag[x]);
        return;
    }
    int mid=(l+r)>>1;
    if(cl<=mid) change(x<<1,l,mid,cl,cr);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr);
    pushup(x);
}
int query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return t[x];
    int mid=(l+r)>>1;
    int ret=0;
    if(ql<=mid) (ret+=query(x<<1,l,mid,ql,qr))%=P;
    if(qr>mid)  (ret+=query(x<<1|1,mid+1,r,ql,qr))%=P;
    return ret%P;
}
int main()
{
    Primes::init();
    scanf("%d%d%d%d",&n,&m,&P,&c);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    phi[0]=P;
    while(phi[k]!=1) k++,phi[k]=get_phi(phi[k-1]);
    phi[++k]=1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&op,&l,&r);
        if(op==0) change(1,1,n,l,r);
        else  printf("%d\n",query(1,1,n,l,r)%P);
    }
}
