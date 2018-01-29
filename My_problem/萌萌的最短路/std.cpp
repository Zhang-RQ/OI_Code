#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<algorithm>
#include<queue>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int __MAXN=1000010;
const int __MAXM=2000010;
int head[__MAXN],dis[__MAXN],vis[__MAXN];
struct Node{
    int val,nxt,v;
}Edge[__MAXM];
int cnte=0;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
struct cmp{
    bool operator () (int a,int b)
    {
        return dis[a]>dis[b];
    }
};
//__gnu_pbds::priority_queue<int,cmp,__gnu_pbds::pairing_heap_tag> pq;
priority_queue<int,vector<int>,cmp> pq;
void read(int &x)
{
    x=0;
    char ch=getchar();
    int f=1;
    while(!isdigit(ch))
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
        x=(x<<3)+(x<<1)+(ch^48),
        ch=getchar();
    x=x*f;
}
void dij(int s)
{
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    pq.push(s);
    int x=0,v=0;
    while(!pq.empty())
    {
        x=pq.top();pq.pop();
        if(!vis[x])
        {
            vis[x]=1;
            for(int i=head[x];i;i=Edge[i].nxt)
            {
                v=Edge[i].v;
                if(!vis[v]&&dis[v]>dis[x]+Edge[i].val)
                    dis[v]=dis[x]+Edge[i].val,
                    pq.push(v);
            }
        }
    }
}
int n,m,s,t,u,v,w;
int main()
{
    read(n),read(m),read(s);
    for(int i=1;i<=m;i++)
        read(u),read(v),read(w),
        add(u,v,w);
    dij(s);
    for(int i=1;i<=n;i++)
        printf("%d ",dis[i]==0x3f3f3f3f?-1:dis[i]);
    puts("");
}
