#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1E5+5;
const int MAXM=1E5+5;
struct node{
    int nxt,v,w,c;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,int w,int c)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].c=c;
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
int pre[MAXN],preedge[MAXN],dis[MAXN];
bool inq[MAXN];
int s=0,t=MAXN-1,n,m,val,u,v,flow[MAXN];
bool spfa()
{
    queue<int> q;
    memset(flow,0,sizeof flow);
    memset(dis,0x3f,sizeof dis);
    memset(inq,0,sizeof inq);
    q.push(s);inq[s]=1;flow[s]=0x3f3f3f3f;dis[s]=0;
    while(q.size())
    {
        int x=q.front();q.pop();inq[x]=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            if(!Edge[i].w) continue;
            int v=Edge[i].v;
            if(dis[v]>dis[x]+Edge[i].c)
            {
                dis[v]=Edge[i].c+dis[x];
                pre[v]=x;preedge[v]=i;
                flow[v]=min(flow[x],Edge[i].w);
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
    return dis[t]!=0x3f3f3f3f;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&val),add(s,i,1,0),add(i,s,0,0),add(s,i+1000,1,val),add(i+1000,s,0,-val),add(i+1000,t,1,0),add(t,i+1000,0,0);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&val);
        if(u>v) swap(u,v);
        add(u,v+1000,1,val);add(v+1000,u,0,-val);
    }
    int min_cost=0;
    while(spfa())
    {
        int x=t,flw=flow[t];
        while(x!=s)
        {
            Edge[preedge[x]].w-=flw;
            Edge[preedge[x]^1].w+=flw;
            x=pre[x];
        }
        min_cost+=dis[t]*flw;
    }
    printf("%d\n",min_cost);
}
