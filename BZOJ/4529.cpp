%:pragma GCC optimize(2)
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
const double PI=acos(-1);
const double eps=0.5;
const int MAXN=1049000<<2;
struct Complex{
    double real,imag;
    Complex(){}
    Complex(double _real,double _imag):real(_real),imag(_imag){}
    inline Complex operator + (const Complex &rhs) const {return Complex(real+rhs.real,imag+rhs.imag);}
    inline Complex operator - (const Complex &rhs) const {return Complex(real-rhs.real,imag-rhs.imag);}
    inline Complex operator * (const Complex &rhs) const {return Complex(real*rhs.real-rhs.imag*imag,imag*rhs.real+rhs.imag*real);}
    inline Complex operator * (const double &rhs) const {return Complex(real*rhs,imag*rhs);}
};
int rev[MAXN],s1[3000100],s2[3000100],n,m,tot,lg2,ans,anss[3000100];
char str1[3000100],str2[3000100];
Complex a[MAXN],b[MAXN],c[MAXN];
double f[3000100];
inline void FFT(Complex *c,int _n,int flag)
{
    for(int i=0;i<_n;i++)
        if(rev[i]>i) swap(c[i],c[rev[i]]);
    for(int i=2;i<=_n;i<<=1)
    {
        Complex wn=Complex(cos(2.0*PI/i),sin(flag*2.0*PI/i));
        for(int j=0;j<_n;j+=i)
        {
            Complex w=Complex(1,0);
            for(int k=0;k<(i>>1);k++)
            {
                Complex t=c[j+k+(i>>1)]*w;
                Complex u=c[j+k];
                c[j+k]=u+t;
                c[j+k+(i>>1)]=u-t;
                w=w*wn;
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s%s",str1,str2);
    for(int i=0;i<n;i++)  s1[i]=str1[i]=='*'?0:str1[i]-'a'+1;
    for(int i=0;i<m;i++)  s2[i]=str2[i]=='*'?0:str2[i]-'a'+1;
    for(tot=1;tot<=n+m;tot<<=1,lg2++);
    for(int i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    reverse(s1,s1+n);

    for(int i=0;i<m;i++)  a[i]=Complex(s1[i]*s1[i]*s1[i],0),b[i]=Complex(s2[i],0);
    FFT(a,tot,1);FFT(b,tot,1);
    for(int i=0;i<tot;i++) c[i]=a[i]*b[i],a[i].real=a[i].imag=b[i].real=b[i].imag=0;

    for(int i=0;i<m;i++)  a[i]=Complex(s1[i]*s1[i],0),b[i]=Complex(s2[i]*s2[i],0);
    FFT(a,tot,1);FFT(b,tot,1);
    for(int i=0;i<tot;i++) c[i]=c[i]-a[i]*b[i]*2.0,a[i].real=a[i].imag=b[i].real=b[i].imag=0;

    for(int i=0;i<m;i++)  a[i]=Complex(s1[i],0),b[i]=Complex(s2[i]*s2[i]*s2[i],0);
    FFT(a,tot,1);FFT(b,tot,1);
    for(int i=0;i<tot;i++) c[i]=c[i]+a[i]*b[i];
    FFT(c,tot,-1);
    for(int i=0;i<tot;i++) f[i]=c[i].real/tot;


    // for(int i=0;i<tot;i++) printf("%lf ",c[i].real/tot);
    // puts("");
    for(int i=n-1;i<m;i++)  if(fabs(f[i])<eps)  anss[++ans]=i+2-n;
    printf("%d\n",ans);
    for(int i=1;i<=ans;i++) printf("%d ",anss[i]);
    puts("");
}
