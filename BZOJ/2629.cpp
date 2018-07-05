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

const int MAXN=262145;
const char ch[40]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S'};
// const int P=29;

char s[6666];
int lim[22],p,n[6666],len,lenp,tot,G;
int num[52000],ans[52000],rnum[MAXN];//g^num[i]%p=i
ll fac[MAXN],ifac[MAXN],f[MAXN],t[MAXN],res[MAXN];

inline ll ksm(ll a,ll b,const ll &P)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

namespace NTT{
    const int NTT_P=998244353;
    const int NTT_G=3;
    inline ll add(ll a,ll b) {a+=b;return a>NTT_P?a-NTT_P:a;}
    inline ll dec(ll a,ll b) {a-=b;return a<0?a+NTT_P:a;}
    int rev[MAXN];
    ll t1[MAXN],t2[MAXN],t3[MAXN];
    inline void NTT(ll *a,int n,bool f)
    {
        for(int i=0;i<n;i++)
            if(i>rev[i]) swap(a[i],a[rev[i]]);
        for(int i=2;i<=n;i<<=1)
        {
            ll wn=ksm(NTT_G,f?(NTT_P-1)/i:(NTT_P-1)-(NTT_P-1)/i,NTT_P);
            for(int j=0;j<n;j+=i)
            {
                ll w=1;
                for(int k=0;k<(i>>1);k++)
                {
                    ll u=a[j+k],t=a[j+k+(i>>1)]*w%NTT_P;
                    a[j+k]=add(u,t);a[j+k+(i>>1)]=dec(u,t);
                    (w*=wn)%=NTT_P;
                }
            }
        }
    }
    inline void multiply(ll *a,ll *b,ll *res,int n)
    {
        int tot=1,lg2=0;
        while((n<<1)>tot)  tot<<=1,lg2++;
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
        for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i];
        NTT(t1,tot,1);NTT(t2,tot,1);
        for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i]%NTT_P;
        NTT(t3,tot,0);
        ll inv=ksm(tot,NTT_P-2,NTT_P);
        for(int i=0;i<tot;i++) res[i]=(t3[i]*inv%NTT_P)%29;
    }
}


void calc()
{
    for(int k=len;k>1;)
    {
        for(int i=k;i>1;i--)
        {
            n[i-1]+=n[i]%p*10;
            n[i]/=p;
        }
        lim[++tot]=n[1]%p;
        n[1]/=p;
        for(;k>1&&!n[k-1];--k);
    }
}

int get_g(int x)
{
    if (x==2) return 1;
    for (int i=2;i;i++) {
        bool pd=1;
        for (int j=2;j*j<x;j++) 
         if (ksm(i,(x-1)/j,x)==1) {
            pd=false;
            break;
         } 
        if (pd) return i;
    }
    return 0;
}

void find_G()
{
    G=get_g(p);
    for (int i=0,j=1;i<p-1;i++,j=(j*G)%p) 
        num[j]=i,rnum[i]=j;
}

inline ll C(int n,int m) {return fac[n]*ifac[m]%p*ifac[n-m]%p;}

int main()
{
    scanf("%s%d",s+1,&p);
    int _p=p,sum=0,cnt=0;
    while(_p) ++lenp,_p/=10;
    len=strlen(s+1);
    for(int i=1;i<=len;i++) n[i]=s[i]-'0';
    for(int i=1;i<=len;i++)
    {
        cnt=cnt*10+n[i];
        cnt%=29;
    }
    reverse(n+1,n+1+len);
    calc();find_G();
    fac[0]=ifac[0]=1;
    for(int i=1;i<p;i++) fac[i]=fac[i-1]*i%p;
    ifac[p-1]=ksm(fac[p-1],p-2,p);
    for(int i=p-2;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%p;
    f[0]=1;++cnt;
    for(int i=1;i<=tot;i++)
    {
        if(!lim[i]) continue;
        memset(t,0,sizeof t);
        for(int j=0;j<=lim[i];j++)
            (t[num[C(lim[i],j)]]+=1)%=29;
        NTT::multiply(f,t,res,p+1);
        memset(f,0,sizeof f);
        for(int j=0;j<=(p<<1);j++) f[j%(p-1)]+=res[j];
        for(int j=0;j<=p-1;j++) f[j]%=29;
    }
    for(int i=0;i<p;i++) ans[rnum[i]]=f[i]%29,(sum+=ans[rnum[i]])%=29;
    ans[0]=((cnt-sum)%29+29)%29;
    for(int i=0;i<p;i++) printf("%c",ch[ans[i]]);
    puts("");
}