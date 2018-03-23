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
#define id(i,j) ((i-1)*100+j)
const int MAXN=3E4+5;
const int MAXM=2E6+5;
const int INF=1<<30;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1,s=0,t=MAXN-4;
inline void add(int u,int v,int w,int w2)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
    Edge[++cnt_e].v=u;
    Edge[cnt_e].nxt=head[v];
    Edge[cnt_e].w=w2;
    head[v]=cnt_e;
}
int lvl[MAXN];
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof lvl);
    q.push(s);lvl[s]=1;
    while(q.size())
    {
        int x=q.front();q.pop();
        // printf("%d\n",x);
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].w) continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[t]!=0;
}
int dfs(int x,int flow)
{
    if(x==t) return flow;
    int add_flow=0;
    for(int i=head[x];i&&add_flow<flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].w)  continue;
        int min_flow=dfs(v,min(flow-add_flow,Edge[i].w));
        if(!min_flow) lvl[v]=0;
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int n,m,a[MAXN],mx,txx;ll ans;
int main() //区间1~10000 寿司 10050~10200  寿司种类 10300~
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),add(i+20050,20300+a[i],INF,0),add(i+20050,t,a[i],0),mx=max(mx,a[i]);
    for(int i=1;i<=mx;i++) add(20300+i,t,m*i*i,0);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n-i+1;j++)
        {
            scanf("%d",&txx);
            if(txx>0) add(s,id(i,i+j-1),txx,0),ans+=txx;
            else add(id(i,i+j-1),t,-txx,0);
            for(int k=i;k<=i+j-1;k++) add(id(i,i+j-1),k+20050,INF,0);
            add(id(i,i+j-1),id(i,i+j-2),INF,0);
            add(id(i,i+j-1),id(i+1,i+j-1),INF,0);
        }
    }
    while(bfs()) ans-=dfs(s,INF);
    printf("%lld\n",ans);
}
