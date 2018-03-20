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
const double eps=1e-6;
const double PPI=acos(-1)*2.0;
const int MAXN=100010;
const int N=262440;
struct Complex{
    double real,imag;
    Complex(){}
    Complex(double _real,double _imag):real(_real),imag(_imag){}
    inline Complex operator + (const Complex &rhs){return Complex(real+rhs.real,imag+rhs.imag);}
    inline Complex operator - (const Complex &rhs){return Complex(real-rhs.real,imag-rhs.imag);}
    inline Complex operator * (const Complex &rhs){return Complex(real*rhs.real-imag*rhs.imag,real*rhs.imag+imag*rhs.real);}
    inline Complex operator * (const double &rhs) {return Complex(real*rhs,imag*rhs);}
}t1[N],t2[N],t3[N];
ll ans=0,res[60010];
int rev[N],blocksize=2000,tot,a[MAXN],belong[MAXN],R[60010],L[60010],st[10010],ed[10010];
int pre[60010];
int n,mx;
void init_block()
{
    for(int i=1;i<=n;i++) belong[i]=(i-1)/blocksize+1;
    for(int i=1;i<=n;i++)
    {
        if(!st[belong[i]]) st[belong[i]]=i;
        ed[belong[i]]=i;
    }
    tot=belong[n];
    for(int i=1;i<=tot;i++)
        for(int j=st[i];j<=ed[i];j++)
            R[a[j]]++;
}
void __FFT(Complex *c,int n,int f)
{
    for(int i=0;i<n;i++)
        if(i>rev[i]) swap(c[i],c[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        Complex wn=Complex(cos(PPI/i),f*sin(PPI/i));
        for(int j=0;j<n;j+=i)
        {
            Complex w=Complex(1,0);
            for(int k=0;k<(i>>1);k++)
            {
                Complex u=c[j+k],t=c[j+k+(i>>1)]*w;
                c[j+k]=u+t;c[j+k+(i>>1)]=u-t;
                w=w*wn;
            }
        }
    }
}
void FFT() //L*R
{
    int ct=1,lg2=0;
    while(ct<=mx+mx) ct<<=1,lg2++;
    for(int i=0;i<ct;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    for(int i=0;i<=mx;i++) t1[i]=Complex(L[i],0);
    for(int i=mx+1;i<ct;i++) t1[i]=Complex(0,0);
    for(int i=0;i<=mx;i++) t2[i]=Complex(R[i],0);
    for(int i=mx+1;i<ct;i++) t2[i]=Complex(0,0);
    __FFT(t1,ct,1);__FFT(t2,ct,1);
    for(int i=0;i<ct;i++) t3[i]=t1[i]*t2[i];
    __FFT(t3,ct,-1);
    for(int i=0;i<ct;i++) res[i]=(ll)(t3[i].real/ct+0.5);
}
void calc(int pos)
{
    for(int i=st[belong[pos]];i<=pos-1;i++) if(a[i]<=a[pos]*2) ans+=R[a[pos]*2-a[i]];
    for(int i=pos+1;i<=ed[belong[pos]];i++) if(a[i]<=a[pos]*2) ans+=L[a[pos]*2-a[i]]+pre[a[pos]*2-a[i]];
    if(belong[pos]!=1&&belong[pos]!=tot) ans+=res[a[pos]*2];
    pre[a[pos]]++;
}
void solve()
{
    init_block();
    for(int i=1;i<=tot;i++)
    {
        memset(pre,0,(mx+1)*sizeof(int));
        for(int j=st[i];j<=ed[i];j++) R[a[j]]--;
        if(i!=1&&i!=tot) FFT();
        for(int j=st[i];j<=ed[i];j++)  calc(j);
        for(int j=st[i];j<=ed[i];j++) L[a[j]]++;
    }
    printf("%lld\n",ans);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),mx=max(mx,a[i]);
    mx++;
    solve();
    return 0;
}
