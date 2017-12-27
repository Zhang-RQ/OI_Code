#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

const int N = 30, M = 1000000 + 10, D = 50, inf = 0x3f3f3f3f;
struct Edge{
    int fr, to, cap, flow;
}edg[M];
int hd[N * D], nxt[M];
int d[N * D], vis[N * D], q[N * D], dfn;
int s, t;
int n, m, k, ans, tot;
int a[N][D], h[N];
void insert(int u, int v, int w){
    edg[tot].fr = u, edg[tot].to = v, edg[tot].cap = w;
    nxt[tot] = hd[u], hd[u] = tot;
    tot++;
    edg[tot].fr = v, edg[tot].to = u;
    nxt[tot] = hd[v], hd[v] = tot;
    tot++;
}
bool bfs(){
    int head = 1, tail = 1;
    q[1] = s; vis[s] = ++dfn; d[s] = 0;
    while(head <= tail){
        int u = q[head++];
        for(int i = hd[u]; i >= 0; i = nxt[i]){
            Edge &e = edg[i];
            if(vis[e.to] == dfn || e.cap <= e.flow) continue;
            vis[e.to] = dfn;
            d[e.to] = d[u] + 1;
            q[++tail] = e.to;
        }
    }
    return vis[t] == dfn;
}
int dfs(int x, int a){
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int i = hd[x]; i >= 0; i = nxt[i]){
        Edge &e = edg[i];
        if(d[e.to] == d[x] + 1 && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0){
            flow += f;
            e.flow += f;
            edg[i^1].flow -= f;
            a -= f;
            if(a == 0) break;
        }
    }
    return flow;
}
void init(){
    memset(hd, -1, sizeof(hd));
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; i++){
        scanf("%d%d", &h[i], &a[i][0]);
        for(int j = 1; j <= a[i][0]; j++)
            scanf("%d", &a[i][j]);
    }
}
void work(){
    s = 0, t = 1;
    insert(s, 3, inf);
    insert(2, t, inf);
    for(int TIME = 1; TIME <= 50; TIME++){
        insert(s, TIME*(n+2)+3, inf);
        insert(TIME*(n+2)+2, t, inf);
        for(int i = 1; i <= m; i++){
            int yd = (TIME - 1) % a[i][0] + 1;
            int td = (yd != a[i][0]) ? (yd + 1) : (1);
            insert((TIME-1)*(n+2)+a[i][yd]+3, TIME*(n+2)+a[i][td]+3, h[i]);
        }
        for(int i = 2; i <= n + 3; i++)
            insert((TIME-1)*(n+2)+i, TIME*(n+2)+i, inf);
        while(bfs()) ans += dfs(s, inf);
        if(ans >= k){
            printf("%d\n", TIME);
            return;
        }
    }
    puts("0");
}
int main(){
    init();
    work();
    return 0;
}
