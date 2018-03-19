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
struct Complex{
    double real,imag;
    Complex(){}
    Complex(double _real,double _imag):real(_real),imag(_imag){}
    inline Complex operator + (const Complex &rhs) const {return Complex(real+rhs.real,imag+rhs.imag);}
    inline Complex operator - (const Complex &rhs) const {return Complex(real-rhs.real,imag-rhs.imag);}
    inline Complex operator * (const Complex &rhs) const {return Complex(real*rhs.real-rhs.imag*imag,imag*rhs.real+rhs.imag*real);}
    inline Complex operator * (const double &rhs) const {return Complex(real*rhs,imag*rhs);}
};
const double PI=acos(-1);
const int __P=((7*17)<<23)+1;
const int __g=3;
const int P=313;
int rev[262440<<2];
ll a[100010<<2],dp[100010<<2],tp1[262440<<2],tp2[262440<<2],tp3[262440<<2];
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=__P;
        (a*=a)%=__P;
        b>>=1;
    }
    return ret;
}
void __FFT(Complex *c,int l,int f)
{
    for(int i=0;i<l;i++)
        if(i<rev[i]) swap(c[i],c[rev[i]]);
    for(int i=2;i<=l;i<<=1)
    {
        Complex ww(cos(2.0*PI/i),sin(f*2.0*PI/i));
        for(int j=0;j<l;j+=i)
        {
            Complex w(1,0);
            for(int k=0;k<=i/2-1;k++)
            {
                Complex t=w*c[j+k+i/2];
                Complex u=c[j+k];
                c[j+k+i/2]=u-t;
                c[j+k]=u+t;
                w=ww*w;
            }
        }
    }
}
Complex tt[262440<<2],ttt[262440<<2],tttt[262440<<2];
void FFT(int len,ll *a,ll *b,ll *res)
{
    int lg2=0,tlen=len;
    while(tlen) lg2++,tlen>>=1;
    lg2--;
    for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    for(int i=0;i<len;i++) tt[i]=Complex(a[i],0),ttt[i]=Complex(b[i],0);
    __FFT(tt,len,1);__FFT(ttt,len,1);
    for(int i=0;i<len;i++) tttt[i]=ttt[i]*tt[i];
    __FFT(tttt,len,-1);
    for(int i=0;i<len;i++) res[i]=(ll)(tttt[i].real/len+0.5);
}
void solve(int L,int R)
{
    if(L==R)
    {
        (dp[R]+=a[R])%=P;
        return;
    }
    int mid=(L+R)>>1,len=max(mid-L+1,R-L+1),tot=1;
    for(tot=1;tot<=len;tot<<=1);
    solve(L,mid);
    for(int i=0;i<mid-L+1;i++)    tp1[i]=dp[i+L];
    for(int i=mid-L+1;i<tot;i++)  tp1[i]=0;
    for(int i=0;i<R-L+1;i++)      tp2[i]=a[i];
    for(int i=R-L+1;i<tot;i++)    tp2[i]=0;
    for(int i=0;i<tot;i++) tp3[i]=0;
    FFT(tot,tp1,tp2,tp3);
    for(int i=mid+1;i<=R;i++)
        (dp[i]+=tp3[i-L])%=P;
    solve(mid+1,R);
}
int n;
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        memset(dp,0,sizeof dp);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]%=P;
        dp[0]=1;
        solve(1,n);
        printf("%lld\n",dp[n]%P);
    }
}
