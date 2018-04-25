# include<iostream>
# include<cstring>
# include<cstdio>
# define LL long long
using namespace std;
const int MAX=3e3+1;
int n,m;
int qu[MAX];
LL sum[MAX],f[MAX],g[MAX];
int read()
{
    int x=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar());
    for(;isdigit(ch);x=x*10+ch-48,ch=getchar());
    return x;
}
double X(int i){return sum[i];}
double Y(int i){return g[i]+sum[i]*sum[i];}
double look(int x,int y) {return (Y(x)-Y(y))/(X(x)-X(y));}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i)
      sum[i]=sum[i-1]+read(),g[i]=sum[i]*sum[i];
    for(int l=1;l<m;++l)
      {
        int he=1,ta=1;
        qu[1]=l;
        for(int i=l+1;i<=n;++i)
          {
            while(he<ta&&look(qu[he],qu[he+1])<2*sum[i]) ++he;
            int tt=qu[he];
            f[i]=g[tt]+(sum[i]-sum[tt])*(sum[i]-sum[tt]);
            while(he<ta&&look(qu[ta],qu[ta-1])>look(qu[ta],i)) --ta;
            qu[++ta]=i;
          }
        for(int i=1;i<=n;i++)
          g[i]=f[i];
      }
    printf("%lld",-sum[n]*sum[n]+m*f[n]);
    return 0;
}
