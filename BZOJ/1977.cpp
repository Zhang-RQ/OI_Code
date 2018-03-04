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
const int MAXN=1E5+5;
const int MAXM=1E5+5;
const int MAXM_=3E5+5;
struct node{
    int nxt,v,w;
}Edge[MAXM];
struct EEE{
    int u,v,w;
    bool us;
    inline friend bool operator <(EEE a,EEE b)
    {
        return a.w<b.w;
    }
}E[MAXM_];
int head[MAXN],cnt_e,fa[MAXN];
int st[2][MAXN][20],lg2[MAXN],jmp[MAXN][20],dep[MAXN];
ll ans,tans;
int n,m;
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
void dfs(int x,int fa,int depth)
{
    dep[x]=depth;
    jmp[x][0]=fa;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        if(Edge[i].v==fa) continue;
        st[0][Edge[i].v][0]=Edge[i].w;
        dfs(Edge[i].v,x,depth+1);
    }
}
void init()
{
    for(int i=2;i<=n;i++) lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i<=n;i++)
        {
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
            st[0][i][j]=max(st[0][i][j-1],st[0][jmp[i][j-1]][j-1]);
            st[1][i][j]=max(min(st[0][i][j-1],st[0][jmp[i][j-1]][j-1]),max(st[1][i][j-1],st[1][jmp[i][j-1]][j-1]));
        }
}
int query(int x,int y,int t)
{
    int ret=0;
    if(dep[x]!=dep[y])
    {
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=lg2[n];i>=0;i--)
            if(dep[jmp[x][i]]>=dep[y]) ret=max(ret,st[t][x][i]),x=jmp[x][i];
    }
    for(int i=lg2[n];i>=0;i--)
        if(jmp[x][i]!=jmp[y][i])
        {
            ret=max(ret,max(st[t][x][i],st[t][y][i]));
            x=jmp[x][i];
            y=jmp[y][i];
        }
    return ret;
}
int main()
{
    tans=1ll<<61;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
    sort(E+1,E+1+m);
    for(int i=1;i<=m;i++)
    {
        if(find(E[i].u)!=find(E[i].v))
        {
            fa[find(E[i].u)]=fa[find(E[i].v)];
            ans+=E[i].w;
            E[i].us=1;
            add(E[i].u,E[i].v,E[i].w);
            add(E[i].v,E[i].u,E[i].w);
        }
    }
    dfs(1,0,1);
    jmp[1][0]=1;
    init();
    for(int i=1;i<=m;i++)
        if(!E[i].us)
        {
            ll t1=E[i].w-query(E[i].u,E[i].v,0);
            ll t2=E[i].w-query(E[i].u,E[i].v,1);
            printf("%d %d %lld %lld\n",E[i].u,E[i].v,-t1+E[i].w,-t2+E[i].w);
            if(t1>0) tans=min(tans,t1);
            else if(t2>0) tans=min(tans,t2);
        }
    printf("%lld %lld\n",ans,ans+tans);
}
