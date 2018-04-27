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
const int MAXN=1E3+5;
const int MAXM=2E3+5;
const int P=1E9+7;
struct node{
    int nxt,v,tp;
}Edge[MAXM];
int head[MAXN],cnt_e,siz[MAXN],n,T,x,y;
char s[110];
inline void add(int u,int v,int tp) //tp=1 u > v
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].tp=tp;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
ll fac[101],ifac[101];
ll f[101][101],g[101],pre[101][101],suf[101][101];
ll ksm(ll a,int b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;
        b>>=1;
    }
    return ret;
}
void init()
{
    fac[0]=1;
    for(int i=1;i<=100;i++) fac[i]=fac[i-1]*i%P;
    ifac[100]=ksm(fac[100],P-2);
    for(int i=99;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%P;
}
ll C(int a,int b) {return fac[a]*ifac[b]%P*ifac[a-b]%P;}
void dfs(int x,int fa)
{
    bool fd=0;
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        fd=1;dfs(v,x);
        siz[x]+=siz[v];
    }
    if(!fd)
    {
        f[x][1]=1;
        pre[x][1]=f[x][1];
        for(int i=2;i<=n;i++)
            pre[x][i]=(pre[x][i-1]+f[x][i])%P;
        suf[x][n]=f[x][n];
        for(int i=n-1;i>=1;i--)
            suf[x][i]=(suf[x][i+1]+f[x][i])%P;
        return;
    }
    int s=1;f[x][1]=1;
    for(int e=head[x];e;e=Edge[e].nxt)
    {
        int v=Edge[e].v;
        if(v==fa) continue;
        for(int i=1;i<=s+siz[v];i++) g[i]=0;
        if(!Edge[e].tp)
            for(int i=1;i<=s;i++)
                for(int j=1;j<=siz[v];j++)
                    (g[i+j-1]+=C(i+j-2,i-1)*C(s-i-j+siz[v]+1,s-i)%P*f[x][i]%P*suf[v][j]%P)%=P;
        else for(int i=1;i<=s;i++)
                for(int j=1;j<=siz[v];j++)
                    (g[i+j]+=C(i+j-1,i-1)*C(s-i+siz[v]-j,s-i)%P*f[x][i]%P*pre[v][j]%P)%=P;
        s+=siz[v];
        for(int i=1;i<=s;i++)  f[x][i]=g[i];
    }
    pre[x][1]=f[x][1];
    for(int i=2;i<=n;i++)
        pre[x][i]=(pre[x][i-1]+f[x][i])%P;
    suf[x][n]=f[x][n];
    for(int i=n-1;i>=1;i--)
        suf[x][i]=(suf[x][i+1]+f[x][i])%P;
}
int main()
{
    init();
    scanf("%d%s",&n,s+2);
    for(int i=2;i<=n;i++)
    {
        add(i>>1,i,s[i]=='>');
        add(i,i>>1,s[i]!='>');
    }
    dfs(1,0);
    printf("%lld\n",pre[1][n]);
}
