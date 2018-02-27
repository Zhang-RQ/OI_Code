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
const int MAXN=550010;
const int MAXM=550010;
struct Graph{
    struct node{
        int nxt,v,w;
    }Edge[MAXM];
    int head[MAXN],cnt_e;
    inline void add(int u,int v,int w)
    {
        if(u==v) return;
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        Edge[cnt_e].w=w;
        head[u]=cnt_e;
    }
}T,vT;
int cnt;
int fa[MAXN],lg2[MAXN<<1],pos[MAXN],st[MAXN<<1][21],lca[MAXN<<1][21],dep[MAXN];
int n,m,k,pnt[MAXN],u,v,w,tk,stk[MAXN],top;
ll f[MAXN],val[MAXN];
bool cmp(int x,int y)
{
    return pos[x]<pos[y];
}
void dfs(int x,int depth)
{
    dep[x]=depth;
    lca[pos[x]=++cnt][0]=x;
    st[cnt][0]=depth;
    for(int i=T.head[x];i;i=T.Edge[i].nxt)
    {
        int v=T.Edge[i].v;
        if(v==fa[x]) continue;
        fa[v]=x;val[v]=min(val[x],(ll)T.Edge[i].w);
        dfs(v,depth+1);
        lca[++cnt][0]=x;
        st[cnt][0]=depth;
    }
}
void init()
{

    for(int i=2;i<=cnt;i++) lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[cnt];j++)
        for(int i=1;i+(1<<(j-1))<=cnt;i++)
            st[i][j]=st[i][j-1]<st[i+(1<<(j-1))][j-1]?st[i][j-1]:st[i+(1<<(j-1))][j-1],
            lca[i][j]=st[i][j-1]<st[i+(1<<(j-1))][j-1]?lca[i][j-1]:lca[i+(1<<(j-1))][j-1];
}
int get_lca(int x,int y)
{
    x=pos[x];y=pos[y];
    if(x>y) swap(x,y);
    int len=lg2[y-x+1];
    return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
}
void dp(int x)
{
    f[x]=val[x];
    ll tmpans=0;
    for(int i=vT.head[x];i;i=vT.Edge[i].nxt)
    {
        int v=vT.Edge[i].v;
        dp(v);
        tmpans+=(ll)f[v];
    }
    vT.head[x]=0;
    if(tmpans!=0) f[x]=min(tmpans,f[x]);
}
void solve()
{
    scanf("%d",&k);
    for(int i=1;i<=k;i++) scanf("%d",&pnt[i]);
    tk=k;
    k=1;
    sort(pnt+1,pnt+1+tk,cmp);
    for(int i=2;i<=tk;i++)
        if(get_lca(pnt[i],pnt[k])!=pnt[k])
            pnt[++k]=pnt[i];
    vT.cnt_e=0;top=0;
    stk[++top]=1;
    for(int i=1;i<=k;i++)
    {
        int lc=get_lca(stk[top],pnt[i]);
        while(1)
        {
            if(dep[lc]>=dep[stk[top-1]])
            {
                vT.add(lc,stk[top--],0);
                if(stk[top]!=lc) stk[++top]=lc;
                break;
            }
            vT.add(stk[top-1],stk[top],0),top--;
        }
        stk[++top]=pnt[i];
    }
    while(--top)
        vT.add(stk[top],stk[top+1],0);
    dp(1);
    printf("%lld\n",f[1]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        T.add(u,v,w);
        T.add(v,u,w);
    }
    val[1]=1ll<<60;
    dfs(1,1);
    init();
    scanf("%d",&m);
    while(m--)
        solve();
}
