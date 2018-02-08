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
typedef std::complex<double> C;
using namespace std;
const int MAXN=263000;
const double PI=acos(-1);
C a[MAXN],b[MAXN];
int r[MAXN],n,lg2,tn;
double x;
void FFT(C *c,int f)
{
    for(int i=0;i<n;i++)
        if(i<r[i]) swap(c[i],c[r[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        C ww(std::cos(2*PI/i),std::sin(f*2*PI/i));
        for(int j=0;j<n;j+=i)
        {
            C w(1,0);
            for(int k=0;k<=i/2-1;k++)
            {
                C u=c[j+k];
                C t=w*c[j+k+i/2];
                c[j+k]=u+t;
                c[j+k+i/2]=u-t;
                w=w*ww;
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    tn=n;
    for(int i=0;i<n;i++)
    {
        scanf("%lf",&x);
        a[i]=C(x,0);
        if(i!=n-1) b[i]=C(-1.0/(n-i-1)/(n-i-1),0);
        else b[i]=C(0,0);
    }
    for(int i=n;i<=2*n-2;i++)
    {
        a[i]=C(0,0);
        b[i]=C(1.0/(n-i-1)/(n-i-1),0);
    }
    n=2*n-1;
    lg2=0;
    for(int t=1;t<n;t<<=1,lg2++);
    n=1<<lg2;
    for(int i=0;i<=n;i++)
        r[i]=(r[i>>1]>>1)|((i&1)<<(lg2-1));
    FFT(a,1);
    FFT(b,1);
    for(int i=0;i<n;i++)
        a[i]*=b[i];
    FFT(a,-1);
    for(int i=tn-1;i<tn*2-1;i++)
        printf("%lf\n",a[i].real()/n);
}
