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
typedef unsigned long long ull;
#define MAXN 100010
#define MAXM 200010
int dep[MAXN],fa[MAXN],pnt[MAXN];
int n,k,t;
bool vis[MAXN];
int head[MAXN];
struct Node{
    int v,nxt;
}Edge[MAXM];
int cnte=0;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    dep[s]=1;fa[s]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(v==fa[x])
                continue;
            dep[v]=dep[x]+1;
            fa[v]=x;
            q.push(v);
        }
    }
}
void dfs(int x,int depth,int from)
{
    if(depth>k)
        return;
    vis[x]=1;
    if(depth==k)
        return;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v!=from)
            dfs(v,depth+1,x);
    }
}
bool cmp(int a,int b)
{
    return dep[a]>dep[b];
}
int main()
{
    int u,v;
    fa[1]=1;
    int ans=0,tfa;
    scanf("%d%d%d",&n,&k,&t);
    for(int i=1;i<=n;i++)
        pnt[i]=i;
    for(int i=1;i<n;i++)
        scanf("%d%d",&u,&v),
        add(u,v),
        add(v,u);
    bfs(1);
    sort(pnt+1,pnt+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        if(!vis[pnt[i]])
        {
            tfa=pnt[i];
            for(int j=1;j<=k&&tfa!=1;j++)
                tfa=fa[tfa];
            ans++;
            vis[tfa]=1;
            dfs(tfa,0,0);
        }
    }
    printf("%d\n",ans);
}
