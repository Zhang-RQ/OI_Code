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
using namespace std;

const int MAXN=510;
const int MAXM=1E5+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];

int head[MAXN],cnt_e,id[MAXN],X,n,siz[MAXN],tot,m,T,tt;
bool vis[MAXN],cut[MAXN];
ll ans=1;

inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

void dfs1(int x)
{
    vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==X||vis[v]) continue;
        dfs1(v);
    }
}

void dfs2(int x,int ID)
{
    vis[x]=1;
    if(id[x]) id[x]=-1;
    else id[x]=ID;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||cut[v]) continue;
        dfs2(v,ID);
    }
}

bool solve()
{
    ans=1;tt=n=m=cnt_e=0;tot=0;
    memset(head,0,sizeof head);
    memset(cut,0,sizeof cut);
    memset(vis,0,sizeof vis);
    memset(id,0,sizeof id);
    memset(siz,0,sizeof siz);
    scanf("%d",&m);
    if(m==0) return 0;
    for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u),n=max(n,max(u,v));
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof vis);
        vis[i]=1;X=i;
        dfs1(i%n+1);
        for(int j=1;j<=n;j++)
            if(!vis[j])
                {cut[i]=1;break;}
    }
    for(int i=1;i<=n;i++)
        if(cut[i])
        {
            memset(vis,0,sizeof vis);
            for(int j=head[i];j;j=Edge[j].nxt)
            {
                int v=Edge[j].v;
                if(cut[v]||vis[v]) continue;
                dfs2(v,++tot);
            }
        }   
    ++T;
    for(int i=1;i<=n;i++)
        if(id[i]!=-1)
            ++siz[id[i]];
    for(int i=1;i<=tot;i++)
        if(siz[i])
            ans*=siz[i],++tt;
    if(!tt) return printf("Case %d: %d %d\n",T,2,n*(n-1)/2),1;
    printf("Case %d: %d %lld\n",T,tt,ans);
    return 1;
}

int main()
{
    while(solve());
    #ifdef LOCAL
        system("pause");
    #endif
}