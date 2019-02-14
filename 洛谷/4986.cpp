#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=262144;
const double PI=acos(-1);
const double EPS=1E-7;

struct Complex{
    double real,imag;
    
    Complex(double _real=0,double _imag=0) {real=_real;imag=_imag;}
    Complex operator + (const Complex &rhs) const {return Complex(real+rhs.real,imag+rhs.imag);}
    Complex operator - (const Complex &rhs) const {return Complex(real-rhs.real,imag-rhs.imag);}
    Complex operator * (const Complex &rhs) const {return Complex(real*rhs.real-imag*rhs.imag,real*rhs.imag+imag*rhs.real);}
};

double L,R;
int a[MAXN],b[MAXN],c[MAXN],la,lb,lc,n;
ll f[MAXN],df[MAXN];

namespace Poly_Mul{Complex t1[MAXN],t2[MAXN],t3[MAXN];}

int rev[MAXN];

void FFT(Complex *a,int n,int f)
{
    for(int i=0;i<n;i++)
	if(rev[i]>i)
	    swap(a[i],a[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
	Complex wn(cos(2*PI/i),-f*sin(2*PI/i));
	for(Complex *x=a,*y=a+(i>>1),*ed=a+n;x!=ed;x+=i,y+=i)
	{
	    Complex w(1,0);
	    for(int k=0;k<(i>>1);k++)
	    {
		Complex u=x[k],t=y[k]*w;
		x[k]=u+t;y[k]=u-t;
		w=w*wn;
	    }
	}
    }
}

void Mul(int *a,int *b,int *Res,int n,int m)
{
    using namespace Poly_Mul;
    int tot=1,lg2=0;
    while(tot<n+m) tot<<=1,lg2++;
    for(int i=0;i<tot;i++)
	rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    for(int i=0;i<tot;i++) t1[i].real=t1[i].imag=t2[i].real=t2[i].imag=0;
    for(int i=0;i<n;i++) t1[i].real=a[i];
    for(int i=0;i<m;i++) t2[i].real=b[i];
    FFT(t1,tot,1);FFT(t2,tot,1);
    for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i];
    FFT(t3,tot,-1);
    for(int i=0;i<n+m;i++) Res[i]=(int)(t3[i].real/tot+0.5);
}

double F(double x)
{
    double ret=f[0],_x=x;
    for(int i=1;i<n;i++) ret+=f[i]*x,x*=_x;
    return ret;
}

double dF(double x)
{
    double ret=df[0],_x=x;
    for(int i=1;i<n;i++) ret+=df[i]*x,x*=_x;
    return ret;
}


double solve(double x)
{
    double c=0;
    int T=40;
    while(T--)
    {
	c=F(x);
	if(fabs(c)<EPS) return x;
	x=x-c/dF(x);
	x=max(L,x);x=min(R,x);
    }
    throw "GG";
}

int main()
{
    scanf("%d%d%d%lf%lf",&la,&lb,&lc,&L,&R);la++;lb++;lc++;
    for(int i=0;i<la;i++) scanf("%d",&a[i]);
    for(int i=0;i<lb;i++) scanf("%d",&b[i]);
    for(int i=0;i<lc;i++) scanf("%d",&c[i]);
    Mul(a,a,a,la,la);Mul(b,b,b,lb,lb);Mul(c,c,c,lc,lc);
    n=la<<1;
    for(int i=0;i<n;i++) f[i]=c[i]-b[i]-a[i];
    for(int i=0;i<n;i++) df[i]=1ll*f[i+1]*(i+1);
    double Ans=0;
    try{Ans=solve((L+R)*0.5);}
    catch(const char *t){puts("Inconsistent!");return 0;}
    printf("%.10lf\n",Ans);
}
