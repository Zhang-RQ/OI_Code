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
#define M 10000
#define N 10000
int head[M],in[M],val[M];
int g[M],f[M];//g[x] choose x ,f[x] !choose x
int n,u,v,root;
struct Node{
    int v,nxt;
}Edge[N];
int cnt=0;
void add(int u,int v)
{
    Edge[++cnt].nxt=head[u];
    Edge[cnt].v=v;
    head[u]=cnt;
 }
void dfs(int x)
{
    g[x]=val[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        dfs(v);
        f[x]+=max(g[v],f[v]);
        g[x]+=f[v];
    }
}
int main()
{
     scanf("%d",&n);
     for(int i=1;i<=n;i++) scanf("%d",&val[i]);
     for(int i=1;i<=n;i++)
     {
         scanf("%d%d",&v,&u);
         if(v==0&&u==0) break;
         add(u,v);
         in[v]++;
     }
     for(int i=1;i<=n;i++) if(!in[i]) root=i;
     dfs(root);
     printf("%d\n",max(f[root],g[root]));
}
