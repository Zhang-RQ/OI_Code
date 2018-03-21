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
const double PPI=acos(-1)*2;
const int MAXN=262440<<1;
const int P=1000000007;
struct Complex{
    double real,imag;
    inline Complex(){}
    inline Complex(const double &_real,const double &_imag):real(_real),imag(_imag){}
    inline Complex operator + (const Complex &rhs){return Complex(real+rhs.real,imag+rhs.imag);}
    inline Complex operator - (const Complex &rhs){return Complex(real-rhs.real,imag-rhs.imag);}
    inline Complex operator * (const Complex &rhs){return Complex(real*rhs.real-imag*rhs.imag,real*rhs.imag+imag*rhs.real);}
    inline Complex operator * (const double &rhs) {return Complex(real*rhs,imag*rhs);}
}t1[MAXN],t2[MAXN],t3[MAXN];
int rev[MAXN],n,tot=1,lg2,hw[MAXN];
ll f[MAXN],sum,pw2[MAXN],ans;
char s[100010],s1[200010];
void FFT(Complex *c,int n,int f)
{
    for(int i=0;i<n;i++)
        if(i>rev[i]) swap(c[i],c[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        Complex wn(cos(PPI/i),f*sin(PPI/i));
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
}
void manacher()
{
    s1[0]=s1[1]='#';
    for(int i=1;i<=n;i++)
        s1[i<<1|1]='#',s1[i<<1]=s[i];
    int maxR=0,mid=0,lw=strlen(s1);
    for(int i=2;i<=lw;i++)
    {
        if(i<=maxR) hw[i]=min(maxR-i,hw[2*mid-i]);
        else hw[i]=1;
        while(s1[i+hw[i]]==s1[i-hw[i]]) hw[i]++;
        if(i+hw[i]>maxR)
        {
            maxR=i+hw[i];
            mid=i;
        }
    }
    for(int i=0;i<lw;i++)
        (sum+=hw[i]/2)%=P;
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    manacher();
    while(tot<=2*n) tot<<=1,lg2++;
    pw2[0]=1;
    for(int i=1;i<tot;i++)
        pw2[i]=(pw2[i-1]<<1)%P;
    for(int i=0;i<tot;i++)
         rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    for(int i=0;i<n;i++)
        t1[i]=Complex(s[i+1]=='a'?1:0,0);
    FFT(t1,tot,1);
    for(int i=0;i<tot;i++) t3[i]=t1[i]*t1[i];
    for(int i=0;i<n;i++)
        t2[i]=Complex(s[i+1]=='b'?1:0,0);
    FFT(t2,tot,1);
    for(int i=0;i<tot;i++)
        t3[i]=t3[i]+t2[i]*t2[i];
    FFT(t3,tot,-1);
    for(int i=0;i<tot;i++)
        f[i]=((ll)(t3[i].real/tot+0.5)+1)/2;
    for(int i=0;i<tot;i++)
        (ans+=pw2[f[i]]-1+P)%=P;
    ans=(ans-sum+P)%P;
    printf("%lld\n",ans);
}
