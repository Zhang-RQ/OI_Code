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
const int MAXN=20010;
const int MAXM=20010;
int head[MAXN];
struct Node{
    int val,nxt,v;
}Edge[MAXM];
int cnte=0;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
int n,m,u,v,val,ops,dis[MAXN];
int ans=-1;
bool ins[MAXN],vis[MAXN];
void dfs(int x)
{
    if(ans!=-1)
        return;
    ins[x]=1;
    vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(dis[v]>dis[x]+Edge[i].val)
        {
            if(ins[v]&&dis[v]!=0x3f3f3f3f)
            {
                ans=1;
                return;
            }
            dis[v]=dis[x]+Edge[i].val;
            dfs(v);
        }
    }
    ins[x]=0;
}
int main()
{
    memset(dis,0x3f3f3f3f,sizeof(dis));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&ops,&u,&v);
        if(ops==3)
            add(u,v,0),
            add(v,u,0);
        else
        {
            scanf("%d",&val);
            if(ops==1)
                add(u,v,val);
            else
                add(u,v,-val);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
            dis[i]=0,
            dfs(i);
        if(ans!=-1)
        {
            puts("No");
            return 0;
        }
    }
    puts("Yes");
}
