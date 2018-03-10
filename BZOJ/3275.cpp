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
const int MAXN=3100;
const int MAXM=1E6+10;
const int INF=1<<30;
const double eps=1E-7;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
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
int lvl[MAXN],n,m,s=0,t=MAXN-1,T;
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof lvl);
    lvl[s]=1;q.push(s);
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].w)
                continue;
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
        if(lvl[v]!=lvl[x]+1||!Edge[i].w)
            continue;
        int min_flow=dfs(v,min(flow-add_flow,Edge[i].w));
        if(!min_flow) lvl[v]=0;
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
int val[3010];
ll tmp,ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&val[i]);
        ans+=val[i];
        if(val[i]&1) add(s,i,val[i],0);
        else add(i,t,val[i],0);
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            if((val[i]&1)==(val[j]&1)) continue;
            tmp=val[i]*val[i]+val[j]*val[j];
            if(((int)sqrt(tmp))*((int)sqrt(tmp))==tmp&&gcd(val[i],val[j])==1)
            {
                if(val[i]&1) add(i,j,INF,0);
                else add(j,i,INF,0);
            }
        }
    while(bfs())
        ans-=dfs(s,INF);
    printf("%lld\n",ans);
}
