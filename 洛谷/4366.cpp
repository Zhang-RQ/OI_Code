// luogu-judger-enable-o2
// luogu-judger-enable-o2
%:pragma GCC optimize(2)
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
const int MAXM=2E7+5;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e,n,m,c,dis[MAXN],s,t,u,v,w;
struct cmp{
    bool operator () (int a,int b){return dis[a]>dis[b];}
};
struct data{
    int x,dis;
    data(){}
    data(int _x,int _dis) {x=_x;dis=_dis;}
    inline bool operator < (const data &rhs) const {return dis>rhs.dis;}
};
// priority_queue<int,vector<int>,cmp> q;
priority_queue<data> q;
inline void add(int u,int v,int w)
{
    // printf("%d->%d %d\n",u,v,w);
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
int main()
{
    memset(dis,0x3f,sizeof dis);
    scanf("%d%d%d",&n,&m,&c);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    int tt;
    for(int i=1;i<=n;i++)
    {
        add(i,0,c*i);add(0,i,c*i);
        for(int j=0;j<=21;j++)
        {
            tt=i^(1<<j);
            if(tt<=n) add(i,tt,c*(1<<j));
        }
    }
    scanf("%d%d",&s,&t);
    dis[s]=0;q.push(data(s,0));
    while(q.size())
    {
        data x=q.top();q.pop();
        if(dis[x.x]<x.dis) continue;
        for(int i=head[x.x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[v]>dis[x.x]+Edge[i].w)
                dis[v]=Edge[i].w+dis[x.x],q.push(data(v,dis[v]));
        }
    }
    printf("%d\n",dis[t]);
}
