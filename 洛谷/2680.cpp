%:pragma GCC optimize(2)
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;

#define M 300010
#define N 300010
int head[M];
struct Node{
    int val,nxt,v;
}Edge[N<<1];
struct Node1{
    int u,v,lca,dis;
}lines[N];
int cnte=0,fath[N];
int sum[N],dep[N];
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
int st[N<<1][20],lca[N<<1][20];
int cnt=0,pos[N],lg2[N<<1];
int n,m,u,v,w,a,b;
void dfs(int x,int fa,int depth)
{
    fath[x]=fa;
    lca[pos[x]=++cnt][0]=x;
    dep[x]=st[pos[x]][0]=depth;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x,depth+Edge[i].val);
        st[++cnt][0]=depth;
        lca[cnt][0]=x;
    }
}
inline void work()
{
    lg2[1]=0;
    for(int i=2;i<=cnt;i++)
        lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[cnt];j++)
        for(int i=1;i<=cnt;i++)
        {
            if(st[i][j-1]>st[i+(1<<(j-1))][j-1])
            {
                st[i][j]=st[i+(1<<(j-1))][j-1];
                lca[i][j]=lca[i+(1<<(j-1))][j-1];
            }else
            {
                st[i][j]=st[i][j-1];
                lca[i][j]=lca[i][j-1];
            }
        }
}
inline int get_lca(int x,int y)
{
    x=pos[x];y=pos[y];
    if(x>y) swap(x,y);
    int len=lg2[y-x+1];
    if(st[x][len]>st[y-(1<<len)+1][len]) return lca[y-(1<<len)+1][len];
    else return lca[x][len];
}
void calc(int x,int fa)
{
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(fa==v) continue;
        calc(v,x);
        sum[x]=sum[x]+sum[v];
    }
}
bool check(int x)
{
    memset(sum,0,sizeof(sum));
    int maxdis=0;
    int cntc=0;
    int maxv=0;
    for(int i=1;i<=m;i++)
    {
        if(lines[i].dis>x)
        {
            cntc++;
            sum[lines[i].u]++;
            sum[lines[i].v]++;
            sum[lines[i].lca]-=2;
            maxdis=max(maxdis,lines[i].dis);
        }
    }
    calc(1,0);
    for(int i=1;i<=n;i++)
        if(sum[i]>=cntc&&dep[i]-dep[fath[i]]>=maxv) maxv=dep[i]-dep[fath[i]];
    if(maxdis-maxv>x) return 0;
    else return 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    dfs(1,0,0);
    work();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&lines[i].u,&lines[i].v);
        lines[i].lca=get_lca(lines[i].u,lines[i].v);
        lines[i].dis=dep[lines[i].u]+dep[lines[i].v]-2*dep[lines[i].lca];
    }
    int ans=0;
    int l=0,r=200000000;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
}
