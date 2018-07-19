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

const int MAXN=2001;
const int MAXM=1E5+5;
const int INF=1<<30;

struct node{
    int nxt,v,w,c;
}Edge[MAXM];

int head[MAXN],cnt_e=1;

inline void add(int u,int v,int f,int c)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].c=c;
    Edge[cnt_e].w=f;
    head[u]=cnt_e;
}
inline void add2(int u,int v,int f,int c){add(u,v,f,c);add(v,u,0,-c);}

int pre[MAXN],preedge[MAXN],dis[MAXN];
bool inq[MAXN];
int s=0,t=MAXN-1,n,a,b,fa,fb,f,flow[MAXN];

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

int MFMC()
{
    int min_cost=0,mxf=0;
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
        mxf+=flw;
    }
    return min_cost;
}

int main()
{
    scanf("%d%d%d%d%d%d",&n,&a,&b,&f,&fa,&fb);
    for(int i=1,x;i<=n;i++) scanf("%d",&x),add2(s,i,x,0),add2(n+i,t,x,0),add2(i,i+a+1+n,INF,fa),add2(i,i+b+1+n,INF,fb),i<n?add2(i,i+1,INF,0):void(),add2(s,i+n,INF,f);
    printf("%d\n",MFMC());
}