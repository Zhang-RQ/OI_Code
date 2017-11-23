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
const int J=1;
const int W=2;
const int HK=3;
const int YYY=4;
const int E=5;
const int MAXN=110;
const int INF=1<<30;
bool mp[6][6];
struct peo{
    int type,life;
}BYX[MAXN],SQJ[MAXN];
void init()
{
    mp[J][HK]=mp[J][W]=1;
    mp[W][YYY]=mp[W][E]=1;
    mp[HK][W]=mp[HK][E]=1;
    mp[YYY][HK]=mp[YYY][J]=1;
    mp[E][YYY]=mp[E][J]=1;
}
const int MAXNN=310;
const int MAXM=200010;
int head[MAXNN];
int n,m;
struct Node{
    int flow,nxt,v;
}Edge[MAXM];
int cnte=1;  //notice
inline void add(const int &u,const int &v,const int &val1,const int &val2)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val1;
    head[u]=cnte;
    Edge[++cnte].nxt=head[v];
    Edge[cnte].v=u;
    Edge[cnte].flow=val2;
    head[v]=cnte;
}
int lvl[MAXNN];
int s=0,t=300;
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof(lvl));
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
        if(!Edge[i].flow||lvl[v]!=lvl[x]+1)
            continue;
        int min_flow=dfs(v,min(Edge[i].flow,cur_flow-add_flow));
        add_flow+=min_flow;
        Edge[i].flow-=min_flow;
        Edge[i^1].flow+=min_flow;
    }
    return add_flow;
}
char str[10];
int cntyyy1,cntyyy2;
int main()
{
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        switch(str[1])
        {
            case 'J':BYX[i].type=J;break;
            case 'H':BYX[i].type=HK;break;
            case 'Y':BYX[i].type=YYY;++cntyyy1;break;
            case 'W':BYX[i].type=W;break;
            case 'E':BYX[i].type=E;break;
        }
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        switch(str[1])
        {
            case 'J':SQJ[i].type=J;break;
            case 'H':SQJ[i].type=HK;break;
            case 'Y':SQJ[i].type=YYY;++cntyyy2;break;
            case 'W':SQJ[i].type=W;break;
            case 'E':SQJ[i].type=E;break;
        }
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&BYX[i].life);
        if(BYX[i].type==J) BYX[i].life+=cntyyy1;
        add(s,i,BYX[i].life,0);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&SQJ[i].life);
        if(SQJ[i].type==J) SQJ[i].life+=cntyyy2;
        add(i+150,t,SQJ[i].life,0);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(mp[BYX[i].type][SQJ[j].type])
                add(i,j+150,1,0);
    int ans=0;
    while(bfs())
        ans+=dfs(s,INF);
    ans=min(ans,m);
    printf("%d\n",ans);
}
