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
#define int long long
#define MAXM 2000010
#define MAXN 1000010
int head[MAXM];
struct Node{
    int v,nxt;
}Edge[MAXN];
int cnte=0;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
struct node{
    int u,v;
    node(){}
    node(int u,int v):u(u),v(v){}
};
vector<node> v;
int fa[MAXN],val[MAXN],f[MAXN][2];
int n,t1,ans=0;
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void dfs(int x,int father)
{
    f[x][0]=0;f[x][1]=val[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) continue;
        dfs(v,x);
        f[x][1]+=f[v][0];
        f[x][0]+=max(f[v][0],f[v][1]);
    }
}
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&val[i],&t1);
        if(find(i)!=find(t1))
        {
            add(i,t1);add(t1,i);
            fa[find(i)]=find(t1);
        }
        else v.push_back(node(i,t1));
    }
    for(int i=0;i<(signed)v.size();i++)
    {
        int t=0;
        dfs(v[i].u,0);t=f[v[i].u][0];
        dfs(v[i].v,0);t=max(t,f[v[i].v][0]);
        ans+=t;
    }
    printf("%lld\n",ans);
}
