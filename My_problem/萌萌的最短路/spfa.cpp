#include<algorithm>
#include <iostream>
#include  <cstdlib>
#include  <cstring>
#include  <climits>
#include   <cstdio>
#include   <string>
#include    <cmath>
#include    <stack>
#include    <deque>

using namespace std;
const int INF=0x3f3f3f3f;
const int __MAXN=1000010;
const int __MAXM=2000010;
int head[__MAXN];
int dis[__MAXN];
int n,m;
int cnt;
bool vis[__MAXN];
int sum,tot;
struct node{
    int net;
    int to;
    int w;
}a[__MAXM];

inline void add(int i,int j,int w)
{
    a[++cnt].to=j;
    a[cnt].net=head[i];
    a[cnt].w=w;
    head[i]=cnt;
}

inline void spfa(int s)
{
    deque<int>q;
    for(int i=1;i<=n;i++)
        dis[i]=INF;
    dis[s]=0;
    vis[s]=true;
    q.push_back(s);
    tot=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop_front();
        vis[u]=false;
        tot--;
        sum-=dis[u];
        for(int i=head[u];~i;i=a[i].net)
        {
            int v=a[i].to;
            if(dis[v]>dis[u]+a[i].w)
            {
                dis[v]=dis[u]+a[i].w;
                if(!vis[v])
                {
                    vis[v]=true;
                    if(q.empty()||dis[v]>dis[q.front()]||dis[v]*tot<=sum)
                    q.push_back(v);
                    tot++;
                    sum+=dis[v];
                }
            }
        }
    }
}

int main()
{
    memset(head,-1,sizeof(head));
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
    }
    spfa(1);
    for(int i=1;i<=n;i++)
        printf("%d ",dis[i]==0x3f3f3f3f?-1:dis[i]);
    puts("");
    return 0;
}
