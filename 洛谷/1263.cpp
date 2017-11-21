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
const int MaxN=210;
#define MAXM 1000010
#define MAXN 90010
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM<<1];
int cnte=1;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
int row[MaxN][MaxN],line[MaxN][MaxN];
int mp[MaxN][MaxN];
int cnt=1,n,m,s=0,t=90001;
int lvl[MAXN];
int x[MAXM],y[MAXM];
bool bfs()
{
    memset(lvl,0,sizeof(lvl));
    queue<int> q;
    q.push(s);
    lvl[s]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].flow)
                continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[t]!=0;
}
int dfs(int x,int cur_flow)
{
    if(x==t)
        return cur_flow;
    int add_flow=0;
    for(int i=head[x];i&&add_flow<cur_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].flow)
            continue;
        int min_flow=dfs(v,min(cur_flow-add_flow,Edge[i].flow));
        Edge[i].flow-=min_flow;
        Edge[i^1].flow+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
            switch(mp[i][j])
            {
                case 0: row[i][j]=cnt;break;
                case 1: break;
                case 2: ++cnt;break;
            }
        ++cnt;
    }
    for(int i=1;i<=cnt;i++)
        add(s,i,1),
        add(i,s,0);
    int tmp=++cnt;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            switch(mp[j][i])
            {
                case 0: line[j][i]=cnt;break;
                case 1: break;
                case 2: ++cnt;break;
            }
        ++cnt;
    }
    for(int i=tmp;i<=cnt;i++)
        add(i,t,1),
        add(t,i,0);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(mp[i][j]==0)
                add(row[i][j],line[i][j],1),
                x[cnte]=i,y[cnte]=j,
                add(line[i][j],row[i][j],0);
    int ans=0;
    while(bfs())
        ans+=dfs(s,0x3f3f3f3f);
    printf("%d\n",ans);
    for(int i=2;i<=cnte;i++)
        if(!Edge[i].flow&&x[i]!=0)
            printf("%d %d\n",x[i],y[i]);
}
