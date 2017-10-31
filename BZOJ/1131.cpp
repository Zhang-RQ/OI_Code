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
#define MAXM 1000010
#define MAXN 1000010
int head[MAXM];
struct Node{
    int v,nxt;
}Edge[MAXN<<1];
int cnte=0;
int n,m,anss;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
int siz[MAXN],dep[MAXN],t1,t2;
ll sum[MAXN];
ll ans;
void dfs_1(int x,int father)
{
    siz[x]=1;dep[x]=dep[father]+1;
    sum[1]+=dep[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) continue;
        dfs_1(v,x);
        siz[x]+=siz[v];
    }
}
void dfs_2(int x,int father)
{
    if(x!=1) sum[x]=sum[father]+n-2*siz[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) continue;
        dfs_2(v,x);
    }
}
int main()
{
    scanf("%d",&n);
    m=n-1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&t1,&t2);
        add(t1,t2);add(t2,t1);
    }
    dfs_1(1,0);
    dfs_2(1,0);
    for(int i=1;i<=n;i++)
    {
        if(sum[i]>ans)
        {
            ans=sum[i];
            anss=i;
        }
    }
    printf("%d\n",anss);
}
