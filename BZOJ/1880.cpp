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
typedef unsigned long long ull;
#define MAXM 2000     //点数
#define MAXN 2000100  //边数
struct node{
    int head[MAXM];
    int in[MAXM];
    struct Node{
        int val,nxt,v;
    }Edge[MAXN<<1];
    int cnte;
    inline void add(const int &u,const int &v,const int &val)
    {
        Edge[++cnte].nxt=head[u];
        Edge[cnte].v=v;
        Edge[cnte].val=val;
        head[u]=cnte;
        in[v]++;
    }
    inline void clear()
    {
        cnte=0;
        memset(in,0,sizeof(in));
        memset(head,0,sizeof(head));
        memset(Edge,0,sizeof(Edge));
    }
}G1,G2;
struct NODE{
    int u,v,val;
}E[MAXN<<2];
int dis[4][MAXN];
int n,m,s1,t1,s2,t2,u,v,val,ans=0;
void spfa(int *dis_,int s)
{
    bool inq[MAXM];
    memset(inq,0,sizeof(inq));
    queue<int> q;
    dis_[s]=0;
    inq[s]=1;q.push(s);
    while(q.size())
    {
        int x=q.front();
        q.pop();inq[x]=0;
        for(int i=G1.head[x];i;i=G1.Edge[i].nxt)
        {
            int v=G1.Edge[i].v;
            if(dis_[v]>dis_[x]+G1.Edge[i].val)
            {
                dis_[v]=dis_[x]+G1.Edge[i].val;
                if(!inq[v])
                    q.push(v),
                    inq[v]=1;
            }
        }
    }
}
void tsort()
{
    queue<int> q;
    int f[MAXM];
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)
        if(!G2.in[i])
            q.push(i);
    while(q.size())
    {
        int x=q.front();q.pop();
        ans=max(ans,f[x]);
        for(int i=G2.head[x];i;i=G2.Edge[i].nxt)
        {
            int v=G2.Edge[i].v;
            --G2.in[v];
            f[v]=max(f[v],f[x]+G2.Edge[i].val);
            if(!G2.in[v])
                q.push(v);
        }
    }
}
int x,y,z;
int main()
{
    memset(dis,0x3f,sizeof(dis));
    scanf("%d%d",&n,&m);
    scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        E[(i<<1)-1].u=x;E[(i<<1)-1].v=y;E[(i<<1)-1].val=z;
        E[i<<1].u=y;E[i<<1].v=x;E[i<<1].val=z;
        G1.add(x,y,z);
        G1.add(y,x,z);
    }
    spfa(dis[0],s1);spfa(dis[1],t1);
    spfa(dis[2],s2);spfa(dis[3],t2);
    G2.clear();
    for(int i=1;i<=(m<<1);i++)
    {
        if(dis[0][E[i].u]+E[i].val+dis[1][E[i].v]==dis[0][t1]&&
            dis[2][E[i].u]+E[i].val+dis[3][E[i].v]==dis[2][t2])
            G2.add(E[i].u,E[i].v,E[i].val);
    }
    tsort();
    G2.clear();
    swap(s2,t2);
    memset(dis[2],0x3f,sizeof(dis[2]));
    memset(dis[3],0x3f,sizeof(dis[3]));
    spfa(dis[2],s2);spfa(dis[3],t2);
    for(int i=1;i<=(m<<1);i++)
    {
        if(dis[0][E[i].u]+E[i].val+dis[1][E[i].v]==dis[0][t1]&&
            dis[2][E[i].u]+E[i].val+dis[3][E[i].v]==dis[2][t2])
            G2.add(E[i].u,E[i].v,E[i].val);
    }
    tsort();
    printf("%d\n",ans);
}
