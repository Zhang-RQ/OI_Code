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
#include<complex>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=2221000;
const double PI=acos(-1);
struct Complex{
    double real,imag;
    Complex(){}
    Complex(double _real,double _imag):real(_real),imag(_imag){}
    inline Complex operator + (const Complex &rhs) const {return Complex(real+rhs.real,imag+rhs.imag);}
    inline Complex operator - (const Complex &rhs) const {return Complex(real-rhs.real,imag-rhs.imag);}
    inline Complex operator * (const Complex &rhs) const {return Complex(real*rhs.real-rhs.imag*imag,imag*rhs.real+rhs.imag*real);}
    inline Complex operator * (const double &rhs) const {return Complex(real*rhs,imag*rhs);}
};
Complex a[MAXN],b[MAXN];
int r[MAXN],n,m,x,tot,lg2,l2;
void FFT(Complex *c,int f,int l)
{
    for(int i=0;i<l;i++)
        if(i<r[i]) swap(c[i],c[r[i]]);
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

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)
        scanf("%d",&x),
        a[i]=Complex(x,0);
    for(int i=0;i<=m;i++)
        scanf("%d",&x),
        b[i]=Complex(x,0);
    for(tot=1;tot<=n+m;tot<<=1,lg2++);
    for(int i=0;i<tot;i++)
        r[i]=(r[i>>1]>>1)|((i&1)<<(lg2-1));
    FFT(a,1,tot);
    FFT(b,1,tot);
    for(int i=0;i<tot;i++)
        a[i]=a[i]*b[i];
    FFT(a,-1,tot);
    for(int i=0;i<n+m+1;i++)
        printf("%d ",(int)(a[i].real/tot+0.5));
    puts("");
}
