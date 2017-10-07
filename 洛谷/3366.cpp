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

#define M 5010
#define N 200100
int head[M];
int fa[M];
struct Node{
    int val,nxt,v,u;
    bool operator < (Node &a)const
    {
        return val<a.val;
    }
}Edge[N<<1];
int cnte=0;
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].u=u;
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
int find(int x)
{
    if(x==fa[x]) return x;
    else return fa[x]=find(fa[x]);
}
int n,m;
int u,v,w;
int main()
{
    ll ans=0;int cnt=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    sort(Edge+1,Edge+1+cnte);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=(m<<1);i++)
    {
        int x=find(Edge[i].u);int y=find(Edge[i].v);
        if(x!=y)
        {
            fa[x]=y;
            cnt++;
            ans+=Edge[i].val;
        }
    }
    if(cnt!=n-1) puts("orz");
    else printf("%lld\n",ans);
}
