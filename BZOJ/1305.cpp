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
const int MAXN=510;
const int MAXM=1E5+10;
const int INF=0x3f3f3f3f;
struct node{
    int nxt,u,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    Edge[cnt_e].u=u;
    head[u]=cnt_e;
}
int lvl[MAXN],n,m,s=0,t=MAXN-1,k;
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
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
bool mp[51][51];
char str[101];
bool check(int x)// 男喜欢 1~50  不喜欢 51~100 女 喜欢  101~150 女 不喜欢 151~200
{
    memset(head,0,sizeof head);cnt_e=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(mp[i][j]) add(i,j+100,1),add(j+100,i,0);
            else add(i+50,j+150,1),add(j+150,i+50,0);
    for(int i=1;i<=n;i++)
    {
        add(s,i,x);add(i,s,0);
        add(i,i+50,k);add(i+50,i,0);
        add(i+150,i+100,k);add(i+100,i+150,0);
        add(i+100,t,x);add(t,i+100,0);
    }
    int ret=0;
    while(bfs())
        ret+=dfs(s,INF);
    return ret==n*x;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        for(int j=1;j<=n;j++)
            mp[i][j]=str[j]=='Y';
    }
    int L=0,R=50,ans=0;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(check(mid)) ans=mid,L=mid+1;
        else R=mid-1;
    }
    printf("%d\n",ans);
}
