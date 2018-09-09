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
#include<ctime>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
        {
            x=0;static char ch=get_char();
            while(!isdigit(ch)) ch=get_char();
            while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
        }

    #if __cplusplus >= 201103L
        template<typename T,typename ...Args>
            inline void read(T& x,Args& ...args)
            {
                read(x);
                read(args...);
            }
    #endif
}

using namespace FastIO;

const int P=998244353;
const int MAXN=205;
const int MAXM=105;

ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

inline int inc(int x,const int &y) {x+=y;return x>P?x-P:x;}

inline int inv(int x){return ksm(x,P-2);}

int n,q,id[MAXN],m[MAXN];
int f[MAXN][2][MAXM],cur[MAXN];
int g[MAXN][MAXN],p[MAXN],INV[MAXN];

int main()
{
	read(n);
	for(int i=1;i<=n;i++)  read(m[i]),f[i][0][m[i]]=1;
    for(int i=1;i<=n;i++) INV[i]=inv(i);
	read(q);
	for(int i=1,op,u,v,ps,d,k;i<=q;i++)
	{
        read(op);
        if(op==0)
        {
            // read(id[1],u,v);
            read(id[1]);read(u);read(v);
            d=gcd(u,v);u/=d;v/=d;ps=1ll*inv(v)*u%P;
            cur[id[1]]^=1;
            for(int j=0;j<=m[id[1]];j++) f[id[1]][cur[id[1]]][j]=0;
            for(int j=1;j<=m[id[1]];j++)
            {
                if(!f[id[1]][cur[id[1]]^1][j]) continue;
                f[id[1]][cur[id[1]]][j]=inc(f[id[1]][cur[id[1]]][j],1ll*((1-ps+P)%P)*f[id[1]][cur[id[1]]^1][j]%P);
                f[id[1]][cur[id[1]]][j-1]=inc(f[id[1]][cur[id[1]]][j-1],1ll*ps*f[id[1]][cur[id[1]]^1][j]%P);
            }
            f[id[1]][cur[id[1]]][0]=inc(f[id[1]][cur[id[1]]^1][0],f[id[1]][cur[id[1]]][0]);
        }
        else
        {
            read(k);
            for(int j=1;j<=k;j++) read(id[j]);
            for(int j=1;j<=k;j++) p[j]=(1-f[id[j]][cur[id[j]]][0]+P)%P;//survive
            g[0][0]=1;
            for(int j=1;j<=k;j++)
            {
                for(int l=0;l<=j;l++)
                {
                    g[j][l]=0;
                    g[j][l]=inc(g[j][l],1ll*g[j-1][l]*((1-p[j]+P)%P)%P);
                    if(l) g[j][l]=inc(g[j][l],1ll*g[j-1][l-1]*p[j]%P);
                }
            }
            for(int j=1,Ans;j<=k;j++)
            {
                Ans=0;
                if(p[j]==1)
                    for(int l=0;l<=k-1;l++)
                        g[k-1][l]=g[k][l+1];
                else
                {
                    int Inv=inv(1-p[j]+P);
                    g[k-1][0]=1ll*g[k][0]*Inv%P;
                    for(int l=1;l<=k-1;l++)
                        g[k-1][l]=1ll*((g[k][l]-1ll*g[k-1][l-1]*p[j]%P+P)%P)*Inv%P;
                }
                for(int l=0;l<=k-1;l++) (Ans+=1ll*INV[l+1]*g[k-1][l]%P*p[j]%P)%=P;
                printf("%d%c",Ans,j==k?'\n':' ');
            }
        }
	}
    for(int i=1,Ans;i<=n;i++)
    {
        Ans=0;
        for(int j=1;j<=m[i];j++) (Ans+=1ll*j*f[i][cur[i]][j]%P)%=P;
        printf("%d%c",Ans,i==n?'\n':' ');
    }
}