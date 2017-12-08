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
const int MAXN=100010;
const int MAXM=200010;
int mp[MAXN];
struct graph{
    int head[MAXN];
    struct Node{
        int val,nxt,v;
    }Edge[MAXM];
    int cnte=0;
    int in[MAXN];
    void clear()
    {
        memset(Edge,0,sizeof(Edge));
        memset(in,0,sizeof(in));
        memset(head,0,sizeof(head));
        cnte=0;
    }
    inline void add(const int &u,const int &v,const int &val)
    {
        ++in[v];
        Edge[++cnte].nxt=head[u];
        Edge[cnte].v=v;
        Edge[cnte].val=val;
        head[u]=cnte;
    }
}G,G0,Gr;
struct NODE{
    int dis,lvl,disn;
    int num;
    bool operator <(NODE a)
    {
        if(dis!=a.dis)
            return dis<a.dis;
        else return lvl<a.lvl;
    }
}pnt[MAXN];
int ans[MAXN][60];
int n,m,u,v,val,P,K;
bool inq[MAXN];
void spfa()
{
    memset(inq,0,sizeof(inq));
    queue<int> q;
    q.push(1);inq[1]=1;
    pnt[1].dis=0;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        inq[x]=0;
        for(int i=G.head[x];i;i=G.Edge[i].nxt)
        {
            int v=G.Edge[i].v;
            if(pnt[v].dis>pnt[x].dis+G.Edge[i].val)
            {
                pnt[v].dis=pnt[x].dis+G.Edge[i].val;
                if(!inq[v])
                    q.push(v);
            }
        }
    }
}
void spfa_2()
{
    memset(inq,0,sizeof(inq));
    queue<int> q;
    q.push(n);inq[n]=1;
    pnt[n].disn=0;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        inq[x]=0;
        for(int i=Gr.head[x];i;i=Gr.Edge[i].nxt)
        {
            int v=Gr.Edge[i].v;
            if(pnt[v].disn>pnt[x].disn+Gr.Edge[i].val)
            {
                pnt[v].disn=pnt[x].disn+Gr.Edge[i].val;
                if(!inq[v])
                    q.push(v);
            }
        }
    }
}
bool tsort()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(!G0.in[i])
            q.push(i);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=G0.head[x];i;i=G0.Edge[i].nxt)
        {
            int v=G0.Edge[i].v;
            pnt[v].lvl=pnt[x].lvl+1;
            --G0.in[v];
            if(!G0.in[v])
                q.push(v);
        }
    }
    for(int i=1;i<=n;i++)
        if(G0.in[i]&&pnt[i].dis+pnt[i].disn<=pnt[n].dis+K)
            return false;
    return true;
}
int T;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&n,&m,&K,&P);
        G.clear();G0.clear();Gr.clear();
        memset(pnt,0,sizeof(pnt));
        memset(ans,0,sizeof(ans));
        for(int i=1;i<=n;i++)
            pnt[i].dis=pnt[i].disn=0x3f3f3f3f,pnt[i].num=i;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&val);
            G.add(u,v,val);
            Gr.add(v,u,val);
            if(!val)
                G0.add(u,v,val);
        }
        spfa();
        spfa_2();
        if(!tsort())
            puts("-1");
        else
        {
            ans[1][0]=1;
            sort(pnt+1,pnt+1+n);
            for(int i=1;i<=n;i++)
                mp[pnt[i].num]=i;
            for(int u=1;u<=n;u++)
            {
                for(int i=G.head[pnt[u].num];i;i=G.Edge[i].nxt)
                {
                    int v=G.Edge[i].v;
                    for(int j=0;j<=K;j++)
                        if(pnt[u].dis+j+G.Edge[i].val<=pnt[mp[v]].dis+K)
                            (ans[v][pnt[u].dis+j+G.Edge[i].val-pnt[mp[v]].dis]+=ans[pnt[u].num][j])%=P;
                }
            }
            ll ansi=0;
            for(int i=0;i<=K;i++)
                (ansi+=ans[n][i])%=P;
            printf("%lld\n",ansi);
        }
    }
}
