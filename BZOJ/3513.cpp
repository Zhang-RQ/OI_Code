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
const double PPI=2.0*acos(-1);
const int MAXN=524290<<1;
struct Complex{
    double real,imag;
    Complex(){}
    Complex(double _real,double _imag):real(_real),imag(_imag){}
    inline Complex operator + (const Complex &rhs) {return Complex(real+rhs.real,imag+rhs.imag);}
    inline Complex operator - (const Complex &rhs) {return Complex(real-rhs.real,imag-rhs.imag);}
    inline Complex operator * (const Complex &rhs) {return Complex(real*rhs.real-imag*rhs.imag,real*rhs.imag+imag*rhs.real);}
    inline Complex operator * (const double  &rhs) {return Complex(real*rhs,imag*rhs);}
}t1[MAXN],t2[MAXN],t3[MAXN];
int rev[MAXN],cnt[400010],n,x,mx,tot=1,lg2=0,T;
ll res[MAXN],sum,ans;
void FFT(Complex *c,int n,int f)
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
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        tot=1;lg2=0;ans=sum=0;mx=0;
        memset(cnt,0,sizeof cnt);memset(res,0,sizeof res);
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&x),cnt[x]++,mx=max(mx,x),res[x<<1]--;
        while(tot<=mx+mx+2) tot<<=1,lg2++;
        for(int i=0;i<tot;i++) t1[i]=t2[i]=Complex(0,0);
        for(int i=1;i<=mx;i++)
            t1[i]=t2[i]=Complex(cnt[i],0);
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        FFT(t1,tot,1);FFT(t2,tot,1);
        for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i];
        FFT(t3,tot,-1);
        for(int i=0;i<tot;i++) res[i]+=((ll)(t3[i].real/tot+0.5));
        for(int i=0;i<=mx;i++)
        {
            sum+=res[i]/2;
            ans+=cnt[i]*sum;
        }
        printf("%.7lf\n",1-6.0*ans/n/(n-1)/(n-2));
    }
}
