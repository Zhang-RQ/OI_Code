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
#define MAXM 2010
#define MAXN 150
const int INF=0x3f3f3f3f;
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM];
int cnte=0,n,s=0,t=149,t1,lvl[MAXN];
inline void add(const int &u,const int &v,const int &val)
{
    //printf("u:%d v:%d flow:%d\n",u,v,val);
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
char str[20],str2[20];
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof(lvl));
    lvl[s]=1;q.push(s);
    while(q.size())
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
    if(x==t) return cur_flow;
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
    while(~scanf("%s",str+1)&&!(str[4]=='O'&&str[5]=='F'))
    {
        int ans=0;
        cnte=1;
        memset(Edge,0,sizeof(Edge));
        memset(head,0,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            add(s,i,1);
            add(i,s,0);
            int l=0,r=0;
            scanf("%s",str2+1);
            switch (str2[1]) {
                case 'S': l=1;break;
                case 'M': l=2;break;
                case 'L': l=3;break;
                case 'X': l=4;break;
                case 'T': l=5;break;
            }
            switch (str2[2]) {
                case 'S': r=1;break;
                case 'M': r=2;break;
                case 'L': r=3;break;
                case 'X': r=4;break;
                case 'T': r=5;break;
            }
            for(int j=l;j<=r;j++)
                add(i,50+j,1),
                add(50+j,i,0);
        }
        for(int i=1;i<=5;i++)
            scanf("%d",&t1),
            add(50+i,t,t1),
            add(t,50+i,0);
        while(bfs())
            ans+=dfs(s,INF);
        if(ans==n)
            printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
        scanf("%s",str2);
    }
}
