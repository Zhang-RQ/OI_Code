// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN=610;
const int MAXM=400010;
struct node{
    int v,nxt,f;
}Edge[MAXM];
vector<int> v[210][210];
int head[MAXN],cnt_e=1,lvl[MAXN],S=0,T=MAXN-1,n,m,TT,C,b[MAXN],x,s[MAXN];
int ans1[MAXN],ans2[MAXN];
inline void add(int u,int v,int f){Edge[++cnt_e].v=v;Edge[cnt_e].f=f;Edge[cnt_e].nxt=head[u];head[u]=cnt_e;}
inline void add2(int u,int v,int f1,int f2){add(u,v,f1);add(v,u,f2);}
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof lvl);
    lvl[S]=1;q.push(S);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].f) continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[T]!=0;
}
int dfs(int x,int cur_flow)
{
    if(x==T) return cur_flow;
    int add_flow=0;
    for(int i=head[x];i&&add_flow<cur_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].f) continue;
        int min_flow=dfs(v,min(Edge[i].f,cur_flow-add_flow));
        if(!min_flow) {lvl[v]=0;continue;}
        Edge[i].f-=min_flow;
        Edge[i^1].f+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
bool check1(int x,int num) //1---200 people 300---600 daoshi
{
    int ned=0;
    for(int i=1;i<num;i++)
        ned+=ans1[i]?1:0;
    ned++;
    memset(head,0,sizeof head);cnt_e=1;
    for(int i=1;i<=m;i++) add2(i+300,T,b[i],0);
    for(int i=1;i<=num;i++) add2(S,i,1,0);
    for(int i=1;i<=num-1;i++)
        for(int j=0;j<(signed)v[i][ans1[i]].size();j++)
            add2(i,v[i][ans1[i]][j]+300,1,0);
    for(int i=1;i<=x;i++)
        for(int j=0;j<(signed)v[num][i].size();j++)
            add2(num,v[num][i][j]+300,1,0);
    int tas=0;
    while(bfs())
        tas+=dfs(S,0x3f3f3f3f);
    // printf("x=%d num=%d tas=%d\n",x,num,tas);
    return tas>=ned;
}
void solve()
{
    for(int i=1;i<=n;i++) //people
    {
        int L=1,R=m;
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(check1(mid,i)) ans1[i]=mid,R=mid-1;
            else L=mid+1;
        }
    }
}
bool check2(int x,int num)
{
    memset(head,0,sizeof head);cnt_e=1;
    int ned=0;
    for(int i=1;i<=m;i++) add2(i+300,T,b[i],0);
    for(int i=1;i<=num-x-1;i++) if(ans1[i]!=0) add2(S,i,1,0),ned++;
    add2(S,num,1,0);
    for(int i=1;i<=num-x-1;i++)
        for(int j=0;j<(signed)v[i][ans1[i]].size();j++)
            add2(i,v[i][ans1[i]][j]+300,1,0);
    for(int i=1;i<=s[num];i++)
        for(int j=0;j<(signed)v[num][i].size();j++)
            add2(num,v[num][i][j]+300,1,0);
    int tas=0;
    while(bfs())
        tas+=dfs(S,0x3f3f3f3f);
    return tas>=ned+1;
}
void solve2()
{
    for(int i=1;i<=n;i++)
    {
        if(ans1[i]<=s[i]&&ans1[i]!=0) {ans2[i]=0;continue;}
        int L=1,R=n;
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(check2(mid,i)) ans2[i]=mid,R=mid-1;
            else L=mid+1;
        }
    }
}
int main()
{
    scanf("%d%d",&TT,&C);
    while(TT--)
    {
        memset(ans1,0,sizeof ans1);
        memset(ans2,-1,sizeof ans2);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) v[i][j].clear();
        for(int i=1;i<=m;i++) scanf("%d",&b[i]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                scanf("%d",&x);
                if(x!=0) v[i][x].push_back(j);
            }
        for(int i=1;i<=n;i++)  scanf("%d",&s[i]);
        solve();solve2();
        for(int i=1;i<=n;i++) printf("%d ",ans1[i]?ans1[i]:m+1);
        puts("");
        for(int i=1;i<=n;i++) printf("%d ",ans2[i]!=-1?ans2[i]:i);
        puts("");
    }
    return 0;
}
