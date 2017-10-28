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

#define M 10010
#define N 500100
int head[M];
struct Node{
    int val,nxt,v;
}Edge[N];
struct A{
    int pnt,dis;
    A(){}
    A(int pnt,int dis):pnt(pnt),dis(dis){}
    bool operator < (const A a)const
    {
        return dis>a.dis;
    }
};
int cnte=0;
int dis[M];
bool inq[M];
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
void spfa(int s)
{
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;
    q.push(s);
    inq[s]=1;
    dis[s]=0;
    while(q.size())
    {
        int tmp=q.front();
        q.pop();inq[tmp]=0;
        for(int i=head[tmp];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[v]>dis[tmp]+Edge[i].val)
            {
                dis[v]=dis[tmp]+Edge[i].val;
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
}
void dij(int s)
{
    memset(dis,0x3f,sizeof(dis));
    priority_queue<A> q;
    q.push(A(s,0));
    dis[s]=0;
    while(q.size())
    {
        int x=q.top().pnt;
        int ds=q.top().dis;
        q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(ds+Edge[i].val<dis[v])
            {
                dis[v]=ds+Edge[i].val;
                q.push(A(v,dis[v]));
            }
        }
    }
}
int main()
{
    int n,m,s,u,v,val;
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>val;
        add(u,v,val);
    }
    //spfa(s);
    dij(s);
    for(int i=1;i<=n;i++)
    {
        if(dis[i]!=0x3f3f3f3f) printf("%d ",dis[i]);
        else printf("2147483647 ");
    }
    puts("");
}
