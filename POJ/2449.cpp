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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1E3+5;
const int MAXM=1E5+5;
struct Graph{
    struct node{
        int nxt,v,w;
    }Edge[MAXM];
    int head[MAXN],cnt_e;
    inline void add(int u,int v,int w)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        Edge[cnt_e].w=w;
        head[u]=cnt_e;
    }
}G,Gr;
struct S{
    int u,ds,rds;
    S(int ux,int x,int y):u(ux),ds(x),rds(y){}
    friend bool operator < (S a,S b)
    {
        return a.rds+a.ds>b.rds+b.ds;
    }
};
int n,m,s,t,k,u,v,w;
int rdis[MAXN];
bool inq[MAXN];
void spfa()
{
    queue<int> q;
    memset(rdis,0x3f,sizeof(rdis));
    memset(inq,0,sizeof(inq));
    rdis[t]=0;
    q.push(t);inq[t]=0;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();inq[x]=0;
        for(int i=Gr.head[x];i;i=Gr.Edge[i].nxt)
        {
            int v=Gr.Edge[i].v;
            if(rdis[v]>rdis[x]+Gr.Edge[i].w)
            {
                rdis[v]=rdis[x]+Gr.Edge[i].w;
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
}
int Astar()
{
    if(rdis[s]==0x3f3f3f3f) return -1;
    int cnt=0;
    if(s==t) ++k;
    priority_queue<S> pq;
    pq.push(S(s,0,rdis[s]));
    while(!pq.empty())
    {
        S tmp=pq.top();
        pq.pop();
        if(tmp.u==t&&++cnt==k) return tmp.ds;
        for(int i=G.head[tmp.u];i;i=G.Edge[i].nxt)
        {
            int v=G.Edge[i].v;
            pq.push(S(v,tmp.ds+G.Edge[i].w,rdis[v]));
        }
    }
    return -1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        G.add(u,v,w);
        Gr.add(v,u,w);
    }
    scanf("%d%d%d",&s,&t,&k);
    spfa();
    printf("%d\n",Astar());
}
