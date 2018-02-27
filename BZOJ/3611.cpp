%:pragma GCC optimize(2)
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
const int MAXN=1000010;
const int MAXM=2000010;
const ll INF=1ll<<50;
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
int n,q,k,u,v,lg2[MAXN<<1],pnt[MAXN],stk[MAXN],top,tag[MAXN],siz[MAXN];
int dep[MAXN],st[MAXN<<1][21],lca[MAXN<<1][21],pos[MAXN],cnt;
ll dp[MAXN],minp[MAXN],maxp[MAXN],ansn,ansx;
bool cmp(int x,int y)
{
    return pos[x]<pos[y];
}
void dfsi(int x,int fa)
{
    lca[pos[x]=++cnt][0]=x;
    st[cnt][0]=dep[x];
    for(int i=T.head[x];i;i=T.Edge[i].nxt)
    {
        int v=T.Edge[i].v;
        if(v==fa) continue;
        dep[v]=dep[x]+1;
        dfsi(v,x);
        lca[++cnt][0]=x;
        st[cnt][0]=dep[x];
    }
}
void init()
{
    for(int i=2;i<=cnt;i++) lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[cnt];j++)
        for(int i=1;i+(1<<j)<=cnt;i++)
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
void dfs(int x)
{
    minp[x]=tag[x]?0:INF;
    maxp[x]=tag[x]?0:-INF;
    dp[x]=0;
    siz[x]=tag[x];
    for(int i=vT.head[x];i;i=vT.Edge[i].nxt)
    {
        int v=vT.Edge[i].v;
        dfs(v);
        siz[x]+=siz[v];
        dp[x]+=dp[v]+1ll*vT.Edge[i].w*siz[v]*(k-siz[v]);
        ansx=max(ansx,maxp[x]+maxp[v]+vT.Edge[i].w);
        ansn=min(ansn,minp[x]+minp[v]+vT.Edge[i].w);
        minp[x]=min(minp[v]+vT.Edge[i].w,minp[x]);
        maxp[x]=max(maxp[v]+vT.Edge[i].w,maxp[x]);
    }
    vT.head[x]=0;
}
void solve()
{
    top=0;
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
        scanf("%d",&pnt[i]),tag[pnt[i]]=1;
    sort(pnt+1,pnt+1+k,cmp);
    stk[++top]=1;
    vT.cnt_e=0;
    for(int i=1;i<=k;i++)
    {
        int lc=get_lca(stk[top],pnt[i]);
        while(1)
        {
            if(dep[lc]>=dep[stk[top-1]])
            {
                vT.add(lc,stk[top],dep[stk[top]]-dep[lc]),top--;
                if(stk[top]!=lc) stk[++top]=lc;
                break;
            }
            vT.add(stk[top-1],stk[top],dep[stk[top]]-dep[stk[top-1]]),top--;
        }
        stk[++top]=pnt[i];
    }
    while(--top)
        vT.add(stk[top],stk[top+1],dep[stk[top+1]]-dep[stk[top]]);
    ansx=-INF,ansn=INF;
    dfs(1);
    printf("%lld %lld %lld\n",dp[1],ansn,ansx);
    for(int i=1;i<=k;i++)
        tag[pnt[i]]=0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        T.add(u,v,1);
        T.add(v,u,1);
    }
    dep[1]=1;
    dfsi(1,0);
    init();
    scanf("%d",&q);
    while(q--) solve();
}
