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
#include<iomanip>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=3E4+5;
const int MAXM=1E5+5;
const double PI=acos(-1);
struct node{
    int nxt,v;
}Edge[MAXM];
namespace FFT{
    struct Complex{
        double real,imag;
        Complex(){}
        Complex(double _real,double _imag):real(_real),imag(_imag){}
        inline Complex operator + (const Complex &rhs) const {return Complex(real+rhs.real,imag+rhs.imag);}
        inline Complex operator - (const Complex &rhs) const {return Complex(real-rhs.real,imag-rhs.imag);}
        inline Complex operator * (const Complex &rhs) const {return Complex(real*rhs.real-imag*rhs.imag,real*rhs.imag+imag*rhs.real);}
    }t1[65537],t2[65537];
    int rev[65537];
    inline void __FFT(Complex *c,int n,int f)
    {
        for(int i=0;i<n;i++)
            if(i>rev[i]) swap(c[i],c[rev[i]]);
        for(int i=2;i<=n;i<<=1)
        {
            Complex wn=Complex(cos(2*PI/i),f*sin(2*PI/i));
            for(int j=0;j<n;j+=i)
            {
                Complex w(1,0);
                for(int k=0;k<(i>>1);k++)
                {
                    Complex u=c[j+k],t=c[j+k+(i>>1)]*w;
                    c[j+k]=u+t;
                    c[j+k+(i>>1)]=u-t;
                    w=w*wn;
                }
            }
        }
    }
    inline void multiply(int *a,int *b,int *res,int n)
    {
        int tot=1,lg2=0;
        while(tot<=2*n) tot<<=1,lg2++;
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        for(int i=0;i<=n;i++) t1[i]=Complex(a[i],0);
        for(int i=0;i<=n;i++) t2[i]=Complex(b[i],0);
        for(int i=n+1;i<tot;i++) t1[i]=t2[i]=Complex(0,0);
        __FFT(t1,tot,1);__FFT(t2,tot,1);
        for(int i=0;i<tot;i++) t1[i]=t1[i]*t2[i];
        __FFT(t1,tot,-1);
        for(int i=0;i<tot;i++) res[i]=(int)(t1[i].real/tot+0.5);
    }
}
int head[MAXN],cnt_e,siz[MAXN],rt,rt_mx,t[MAXM],tp[MAXM],mxdis,tt[MAXM],ttt[MAXM],n,x,y;
long double ans;
bool vis[MAXN];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void get_rt(int x,int fa,int sz)
{
    int mx;mx=siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        get_rt(v,x,sz);
        siz[x]+=siz[v];
        mx=max(mx,siz[v]);
    }
    mx=max(mx,sz-siz[x]);
    if(mx<rt_mx) rt=x,rt_mx=mx;
}
void dfs(int x,int fa,int dis,int *T,int f)
{
    T[dis]+=f;mxdis=max(mxdis,dis);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        dfs(v,x,dis+1,T,f);
    }
}
void solve(int x)
{
    vis[x]=1;
    int tmp=mxdis=1;
    dfs(x,0,0,tp, 1);
    FFT::multiply(tp,tp,tt,mxdis);
    dfs(x,0,0,tp,-1);
    tmp=mxdis;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        mxdis=1;
        dfs(v,x,1,tp, 1);
        FFT::multiply(tp,tp,ttt,mxdis);
        dfs(v,x,1,tp,-1);
        for(int j=1;j<=mxdis<<1;j++) tt[j]-=ttt[j];
    }
    for(int i=0;i<=tmp<<1;i++) t[i]+=tt[i];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        rt=0;rt_mx=MAXN+10;
        get_rt(v,x,siz[v]);
        solve(rt);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++) scanf("%d%d",&x,&y),++x,++y,add(x,y),add(y,x);
    rt_mx=MAXN;
    get_rt(1,0,n);
    solve(rt);
    for(int i=1;i<=n;i++) ans+=1.0*t[i]/(i+1);
    cout<<fixed<<setprecision(4)<<ans+n<<endl;
}
