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
typedef unsigned int uint;
using namespace std;
const uint P=998244353;
const int MAXN=1E5+5;
const int MAXM=2.1E5+5;
struct dat{
    uint x,y;
    dat(){}
    dat(uint _,uint __):x(_),y(__) {}
    inline dat operator + (const dat &rhs) const {return dat((x+rhs.x)%P,(y+rhs.y)%P);}
    inline dat operator * (const uint &rhs) const {return dat((ull)x*rhs%P,(ull)y*rhs%P);}
}k[MAXN][2];
struct Graph_1{
    struct __edge{
        int nxt,v;
    }Edge[MAXM];
    int head[MAXN],cnt_e;
    inline void add(int u,int v)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
    }
}T;
struct Graph_2{
    struct __edge{
        int nxt,v;
        dat a,b;
    }Edge[MAXM];
    int head[MAXN],cnt_e;
    inline void add(int u,int v,dat a,dat b)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].a=a;
        Edge[cnt_e].b=b;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
    }
}vT;
struct Edge{int u,v;}E[30];
uint p[MAXN][2],siz[MAXN],dfn[MAXN],n,m,cnt,dft,f[MAXN][2],ans;
bool mark[MAXN],vis[MAXN],fg[MAXN][2];
void dfs(uint x,uint fa)
{
    dfn[x]=++dft;
    for(uint i=T.head[x];i;i=T.Edge[i].nxt)
    {
        uint v=T.Edge[i].v;
        if(v==fa) continue;
        if(!dfn[v]) dfs(v,x),siz[x]+=siz[v];
        else 
        {
            mark[x]=1;
            if(dfn[v]>dfn[x]) E[++cnt].u=x,E[cnt].v=v;
        }
    }
    mark[x]|=siz[x]>=2;
    siz[x]=mark[x]||siz[x];
}
int dfs2(uint x)
{
    uint pos=0,w;
    vis[x]=p[x][0]=p[x][1]=1;
    for(uint i=T.head[x];i;i=T.Edge[i].nxt)
    {
        uint v=T.Edge[i].v;
        if(vis[v]) continue;
        w=dfs2(v);
        if(!w) p[x][0]=((ull)p[v][0]+p[v][1])*p[x][0]%P,p[x][1]=(ull)p[v][0]*p[x][1]%P;
        else if(mark[x]) vT.add(x,w,k[v][0]+k[v][1],k[v][0]);
        else k[x][0]=k[v][0]+k[v][1],k[x][1]=k[v][0],pos=w;
    }
    if(mark[x]) k[x][0]=dat(1,0),k[x][1]=dat(0,1),pos=x;
    else k[x][0]=k[x][0]*p[x][0],k[x][1]=k[x][1]*p[x][1];
    return pos;
}
void dfs3(int x,int fa)
{
    f[x][0]=fg[x][1]?0:p[x][0];
    f[x][1]=fg[x][0]?0:p[x][1];
    for(uint i=vT.head[x];i;i=vT.Edge[i].nxt)
    {
        uint v=vT.Edge[i].v;
        if(v==fa) continue;
        dfs3(v,x);
        ull p=f[v][0],q=f[v][1];
        f[x][0]=f[x][0]*((p*vT.Edge[i].a.x%P+q*vT.Edge[i].a.y%P)%P)%P;
        f[x][1]=f[x][1]*((p*vT.Edge[i].b.x%P+q*vT.Edge[i].b.y%P)%P)%P;
    }
}
char B[1<<26],*S=B;

int F()
{
	for(;*S<'-';++S);
	int x=(*S++)-'0';
	for(;*S>='0';x=x*10+(*S++)-'0');
	return x;
}
int main()
{
    fread(B,1,1<<26,stdin);
    // scanf("%d%d",&n,&m);
    n=F();m=F();
    for(uint i=1,u,v;i<=m;i++)
    {
        u=F();v=F();
        // scanf("%d%d",&u,&v);
        T.add(u,v);T.add(v,u);
    }
    dfs(1,0);mark[1]=1;dfs2(1);
    for(uint s=0;s<1<<cnt;s++)
    {
        for(uint i=0;i<cnt;i++)
            if((s>>i)&1) fg[E[i+1].u][1]=fg[E[i+1].v][0]=1;
            else fg[E[i+1].u][0]=1;
        dfs3(1,0);
        (ans+=(f[1][0]+f[1][1])%P)%=P;
        for(uint i=0;i<cnt;i++)
            if((s>>i)&1) fg[E[i+1].u][1]=fg[E[i+1].v][0]=0;
            else fg[E[i+1].u][0]=0;
    }
    printf("%u\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}