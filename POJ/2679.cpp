#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

#define MAXN 1105
#define MAXM 5005
#define INF 0x3f3f3f3f

struct Edge{
    int v,len,fee,next;
    Edge(){}
    Edge(int vv,int ll,int ff, int nn):v(vv),len(ll),fee(ff),next(nn){}
}e[2*MAXM];

int n,m;
int dept,dest;
int h[MAXN], le;
int minfee[MAXN], minFee[MAXN];
int vis[MAXN];
int d[MAXN], cnt[MAXN];

void add(int u, int v,int w,int fuv,int fvu)
{
    e[le] = Edge(v, w, fuv, h[u]);  h[u] = le++;
    e[le] = Edge(u, w, fvu, h[v]);  h[v] = le++;
}

bool dfs(int x)  
{
    vis[x] = true;
    if(x == dest) return true;
    if(minfee[x] == INF)   return false;
    for(int i = h[x]; i != -1; i = e[i].next)
    {
        if(!vis[e[i].v] && minfee[x] == e[i].fee)
        {
            if(dfs(e[i].v)) return true;
            vis[e[i].v] = false;
        }
    }
    return false;
}

bool spfa(int x)
{
    memset(d,INF,sizeof(d));
    memset(vis,false,sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    memset(minFee, 0, sizeof(minFee));
    queue<int> q;
    q.push(x);  vis[x] = true;
    cnt[x] = 1; d[x] = 0; minFee[x] = 0;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();    vis[cur] = false;
        for(int i = h[cur]; i != -1; i = e[i].next)
        {
            if(minfee[cur] != e[i].fee) continue;
            int v = e[i].v, w = e[i].len;
            if(minFee[v] > minFee[cur] + minfee[cur] ||
               d[v] > d[cur] + w)   //先判断费用更小，再判断距离更小
            {
                minFee[v] = minFee[cur] + minfee[cur];
                d[v] = d[cur] + w;
                if(!vis[v])
                {
                    vis[v] = true;
                    if(++cnt[v] > n)    //成环
                    {
                        if(dfs(v)) return false;    //可达终点
                        else continue;  //不可达终点
                    }
                    q.push(v);
                }
            }
        }
    }
    return true;
}

int main()
{
    //freopen("in.txt", "r", stdin);

    while(~scanf("%d%d%d%d", &n,&m,&dept,&dest))
    {
        memset(h,-1,sizeof(h));
        memset(minfee,INF,sizeof(minfee));
        le = 0;
        char cmd[100];
        int u,v,w,fuv,fvu;
        for(int i = 0; i < m; i++)
        {
            scanf("%s", cmd);
            sscanf(cmd, "(%d,%d,%d[%d]%d)", &u,&v,&fuv,&w,&fvu);
            add(u,v,w,fuv,fvu);
            minfee[u] = min(minfee[u], fuv);
            minfee[v] = min(minfee[v], fvu);
        }

        memset(vis,false,sizeof(vis));
        bool VOID = !dfs(dept);
        if(VOID)
        {
            printf("VOID\n");
            continue;
        }
        bool UNBOUND = !spfa(dept);
        if(UNBOUND) printf("UNBOUND\n");
        else printf("%d %d\n", minFee[dest], d[dest]);
    }

    return 0;
}
