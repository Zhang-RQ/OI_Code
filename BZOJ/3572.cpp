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
const int MAXN=300010;
const int MAXM=300010;
const int INF=1E9+7;
int n,q,m,pnt[MAXN],stk[MAXN],top,cnt,bl[MAXN],dis[MAXN],ans[MAXN];
int jmp[MAXN][21],dep[MAXN],u,v,dfn[MAXN],siz[MAXN],mnt[MAXN],g[MAXN];
struct Graph{
    struct node{
        int nxt,v;
    }Edge[MAXM<<1];
    int head[MAXN],cnt_e;
    inline void add(int u,int v)
    {
        if(u==v) return;
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
    }
}T,vT;
int get_lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    if(dep[x]!=dep[y])
        for(int i=20;i>=0;i--)
            if(dep[jmp[x][i]]>=dep[y])
                x=jmp[x][i];
    for(int i=20;i>=0;i--)
        if(jmp[x][i]!=jmp[y][i])
            x=jmp[x][i],y=jmp[y][i];
    return x==y?x:jmp[x][0];
}
int Dis(int x,int y)
{
    return dep[x]+dep[y]-2*dep[get_lca(x,y)];
}
bool cmp(int x,int y)
{
    return dfn[x]<dfn[y];
}
void dfsi(int x,int fa)
{
    dfn[x]=++cnt;
    siz[x]=1;
    jmp[x][0]=fa;
    for(int i=T.head[x];i;i=T.Edge[i].nxt)
    {
        int v=T.Edge[i].v;
        if(v==fa) continue;
        dep[v]=dep[x]+1;
        dfsi(v,x);
        siz[x]+=siz[v];
    }
}
void dfs1(int x)
{
    dis[x]=mnt[x]?0:INF;
    if(mnt[x]) bl[x]=x;
    for(int i=vT.head[x];i;i=vT.Edge[i].nxt)
    {
        int v=vT.Edge[i].v;
        dfs1(v);
        int ds=dep[bl[v]]-dep[x];
        if(ds<dis[x]) dis[x]=ds,bl[x]=bl[v];
        else if(ds==dis[x]&&bl[x]>bl[v]) bl[x]=bl[v];
    }
}
void dfs2(int x)
{
    for(int i=vT.head[x];i;i=vT.Edge[i].nxt)
    {
        int v=vT.Edge[i].v,ds=dep[v]-dep[x];
        if(dis[v]>dis[x]+ds) dis[v]=dis[x]+ds,bl[v]=bl[x];
        else if(dis[v]==dis[x]+ds&&bl[x]<bl[v]) bl[v]=bl[x];
        dfs2(v);
    }
    ans[bl[x]]=max(ans[bl[x]],siz[x]);
    //printf("%d %d %d\n",x,bl[x],ans[bl[x]]);
}
void dfs(int x)
{
    //printf("x=%d\n",x);
    for(int i=vT.head[x];i;i=vT.Edge[i].nxt)
    {
        int v=vT.Edge[i].v;
        if(bl[x]!=bl[v])
        {
            int ds=Dis(bl[x],bl[v]),d2=ds/2-dis[v],z=v;
            if(ds&1)
            {
                for(int j=20;j>=0;j--)
                    if((1<<j)<=d2)
                        z=jmp[z][j],d2-=1<<j;
                ans[bl[x]]-=siz[z];
            }
            else
            {
                int tmp=d2;
                for(int j=20;j>=0;j--)
                    if((1<<j)<=d2)
                        z=jmp[z][j],d2-=1<<j;
                if(z!=x&&z!=v) d2=tmp-(bl[x]<bl[v]);
                else if(z==x) d2=tmp-1;
                z=v;
                for(int j=20;j>=0;j--)
                    if((1<<j)<=d2)
                        z=jmp[z][j],d2-=1<<j;
                ans[bl[x]]-=siz[z];
            }
            //printf("z=%d v=%d flag=%d dis=%d siz[z]=%d %d\n",z,v,ds&1,ds,siz[z],ans[6]);
            if(v!=z) ans[bl[v]]+=siz[z]-siz[v];
        }
        dfs(v);
    }
    vT.head[x]=0;
}
void init()
{
    for(int j=1;j<=20;j++)
        for(int i=1;i<=n;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
}
void solve()
{
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",&pnt[i]),mnt[g[i]=pnt[i]]=1;
    sort(pnt+1,pnt+1+m,cmp);
    top=0;vT.cnt_e=0;
    stk[++top]=1;
    for(int i=1;i<=m;i++)
    {
        int lca=get_lca(stk[top],pnt[i]);
        while(1)
        {
            if(dep[lca]>=dep[stk[top-1]])
            {
                vT.add(lca,stk[top--]);
                if(lca!=stk[top]) stk[++top]=lca;
                break;
            }
            vT.add(stk[top-1],stk[top]),top--;
        }
        stk[++top]=pnt[i];
    }
    while(--top)
        vT.add(stk[top],stk[top+1]);
    dfs1(1);
    dfs2(1);
    dfs(1);
    for(int i=1;i<=m;i++)
        printf("%d ",ans[g[i]]),mnt[g[i]]=0,ans[g[i]]=0;
    puts("");
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        T.add(u,v);T.add(v,u);
    }
    dep[1]=1;
    dfsi(1,0);
    init();
    scanf("%d",&q);
    while(q--) solve();
}
