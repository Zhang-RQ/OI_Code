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
const int MAXN=2E5+10;
const int MAXM=2E6+10;
const int INF=1<<30;
const int mv[2][3][2]={
    {{-1,0},{0,-1},{0,1}},
    {{ 1,0},{0,-1},{0,1}}
};
struct node{
    int nxt,v,f;
}Edge[MAXM];
int head[MAXN],cnt_e=1,cnt,val[MAXN],C,R,x,y,tt,col[MAXN];
inline void add(int u,int v,int f1,int f2)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].f=f1;
    head[u]=cnt_e;
    Edge[++cnt_e].v=u;
    Edge[cnt_e].nxt=head[v];
    Edge[cnt_e].f=f2;
    head[v]=cnt_e;
}
int lvl[MAXN],n,m,S=0,T=MAXN-1;
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof lvl);
    lvl[S]=1;q.push(S);
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].f)
                continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[T]!=0;
}
int dfs(int x,int flow)
{
    if(x==T) return flow;
    int add_flow=0;
    for(int i=head[x];i&&add_flow<flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].f)
            continue;
        int min_flow=dfs(v,min(flow-add_flow,Edge[i].f));
        if(!min_flow) lvl[v]=0;
        Edge[i].f-=min_flow;
        Edge[i^1].f+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
map<pair<int,int>,int> mp;
vector<pair<int,int> > vv;
void build()
{
    int le,re,te,tre;
    for(auto xx : vv)
    {
        tre=mp[make_pair(xx.first+1,xx.second)];
        if(tre)
        {
            te=mp[xx];
            if(!col[te]) add(te,tre,min(val[te],val[tre]),0);
            else add(tre,te,min(val[te],val[tre]),0);
            for(int i=0;i<3;i++)
            {
                le=mp[make_pair(xx.first+mv[0][i][0],xx.second+mv[0][i][1])];
                if(le)
                {
                    if(col[le]) add(le,te,INF,0);
                    else add(te,le,INF,0);
                }
            }
            for(int i=0;i<3;i++)
            {
                re=mp[make_pair(xx.first+1+mv[1][i][0],xx.second+mv[1][i][1])];
                if(re)
                {
                    if(col[re]) add(re,tre,INF,0);
                    else add(tre,re,INF,0);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d%d",&C,&R,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&x,&y,&tt);
        mp[make_pair(x,y)]=++cnt;
        val[cnt]=tt;col[cnt]=(x+y)&1;
        if(x%4==1&&y%2==1) vv.push_back(make_pair(x,y));
        else if(x%4==3&&y%2==0) vv.push_back(make_pair(x,y));
        else if(!((x%4==2&&y%2==1)||(x%4==0&&y%2==0)))
        {
            if((x+y)&1) add(S,cnt,tt,0);
            else add(cnt,T,tt,0);
        }
    }
    build();
    int ans=0;
    while(bfs()) ans+=dfs(S,INF);
    printf("%d\n",ans<0?0:ans);
}
