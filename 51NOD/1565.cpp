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
const int MAXN=262145<<1;
const double PI=acos(-1);
const double EPS=1E-8;
struct Complex{
    double real,imag;
    Complex(){}
    Complex(double _,double __){real=_;imag=__;}
    inline Complex operator + (const Complex &rhs) const {return Complex(real+rhs.real,imag+rhs.imag);}
    inline Complex operator - (const Complex &rhs) const {return Complex(real-rhs.real,imag-rhs.imag);}
    inline Complex operator * (const Complex &rhs) const {return Complex(real*rhs.real-imag*rhs.imag,real*rhs.imag+imag*rhs.real);}
}a[MAXN],b[MAXN];
int rev[MAXN],n,m,k,cc[4],mp[128],t[MAXN];
char s1[MAXN],s2[MAXN];
bool ss1[4][MAXN],ss2[4][MAXN];
void FFT(Complex *c,int n,int f)
{
    for(int i=0;i<n;i++) if(i>rev[i]) swap(c[i],c[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        Complex wn(cos(2*PI/i),f*sin(2*PI/i));
        for(int j=0;j<n;j+=i)
        {
            Complex w(1,0);
            for(int k=0;k<(i>>1);k++)
            {
                Complex u=c[j+k],t=c[j+k+(i>>1)]*w;
                c[j+k]=u+t;c[j+k+(i>>1)]=u-t;
                w=w*wn;
            }
        }
    }
    if(f==-1) for(int i=0;i<n;i++) c[i].real/=n;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s%s",s1,s2);
    mp['A']=0;mp['T']=1;mp['C']=2;mp['G']=3;
    for(int i=0;i<n;i++) s1[i]=mp[s1[i]];
    for(int i=0;i<m;i++) s2[i]=mp[s2[i]];
    cc[0]=cc[1]=cc[2]=cc[3]=k;
    for(int i=0;i<n;i++)
    {
        cc[0]++;cc[1]++;cc[2]++;cc[3]++;
        cc[s1[i]]=0;
        for(int j=0;j<4;j++) if(cc[j]<=k) ss1[j][i]=1;
    }
    cc[0]=cc[1]=cc[2]=cc[3]=k;
    for(int i=n-1;i>=0;i--)
    {
        cc[0]++;cc[1]++;cc[2]++;cc[3]++;
        cc[s1[i]]=0;
        for(int j=0;j<4;j++) if(cc[j]<=k) ss1[j][i]=1;
    }
    for(int i=0;i<m;i++) ss2[s2[i]][i]=1;
    int tot=1,lg2=0;
    while(n+m>=tot) tot<<=1,lg2++;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    for(int i=0;i<4;i++)
    {
        memset(a,0,sizeof a);memset(b,0,sizeof b);
        for(int j=0;j<n;j++) a[j].real=1.0*ss1[i][j];
        for(int j=0;j<m;j++) b[j].real=1.0*ss2[i][m-j-1];
        FFT(a,tot,1);FFT(b,tot,1);
        for(int j=0;j<tot;j++) a[j]=a[j]*b[j];
        FFT(a,tot,-1);
        for(int j=0;j<tot;j++) t[j]+=(int)(a[j].real+0.5);
    }
    int ans=0;
    for(int i=m-1;i<n+m-1;i++) if(t[i]==m) ans++;
    printf("%d\n",ans);
}
