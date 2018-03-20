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
const int P=1004535809;
const int g=3;
const int MAXN=32780<<3;
int rev[MAXN];
ll tp1[MAXN],tp2[MAXN],tp3[MAXN];
int M,N,x,pos[8001<<3],G,S,tp,tlen=1,tlg2=0;
ll f[8001<<3],ans[8001<<3];
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
ll __ksm(ll a,ll b,ll P)
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
void __NTT(ll *a,int n,int flag)
{
    for(int i=0;i<n;i++)
        if(i>rev[i]) swap(a[i],a[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        ll wn=ksm(g,flag?(P-1)/i:P-1-(P-1)/i);
        for(int j=0;j<n;j+=i)
        {
            ll w=1;
            for(int k=0;k<(i>>1);k++)
            {
                ll u=a[j+k]%P;
                ll t=a[j+k+(i>>1)]*w%P;
                a[j+k]=(u+t)%P;
                a[j+k+(i>>1)]=(u-t+P)%P;
                w=w*wn%P;
            }
        }
    }
}
void NTT(int len,ll *a,ll *b,ll *c)// len!=2^k 0->len-1
{
    int lg2=tlg2,tot=tlen;
    for(int i=M-1;i<tot;i++) a[i]=b[i]=0;
    for(int i=0;i<tot;i++)  rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    __NTT(a,tot,1);
    __NTT(b,tot,1);
    for(int i=0;i<tot;i++)
        c[i]=a[i]*b[i]%P;
    __NTT(c,tot,0);
    int inv=ksm(tot,P-2);
    for(int i=M-1;i<=(M-2)<<1;i++)
        (c[i-(M-1)]+=c[i])%=P,c[i]=0;
    for(int i=0;i<tot;i++)
        (c[i]*=inv)%=P;
}
void qpow(ll *a,ll *res,int b)
{
    memset(res,0,sizeof *res);
    res[0]=1;
    while(b)
    {
        if(b&1)
        {
            memcpy(tp1,a,tlen*sizeof(ll));
            memcpy(tp2,res,tlen*sizeof(ll));
            NTT(tlen,tp1,tp2,tp3);
            memcpy(res,tp3,tlen*sizeof(ll));
        }
        memcpy(tp1,a,tlen*sizeof(ll));
        memcpy(tp2,a,tlen*sizeof(ll));
        NTT(tlen,tp1,tp2,tp3);
        memcpy(a,tp3,tlen*sizeof(ll));
        b>>=1;
    }
}
inline bool judge(int x,int p)
{
    for(int i=2;i*i<=p;i++)
        if((p-1)%i==0&&__ksm(x,(p-1)/i,p)==1) return 0;
    return 1;
}
void findg()
{
    if(M==2) {G=2;return;}
    G=2;
    for(;!judge(G,M);G++);
    for(int i=0;i<M-1;i++)
        pos[__ksm(G,i,M)]=i;
    // pos[1]=0;
}
int main()
{
    scanf("%d%d%d%d",&N,&M,&x,&S);
    while(tlen<=M*2) tlen<<=1,tlg2++;
    findg();
    for(int i=1;i<=S;i++)
    {
        scanf("%d",&tp);
        if(!tp)continue;
        f[pos[tp]]=1;
    }
    qpow(f,ans,N);
    printf("%lld\n",ans[pos[x]]%P);
}
