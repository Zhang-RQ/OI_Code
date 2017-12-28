#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <queue>
#define re register
using namespace std;
typedef long long LL;
inline LL read() {
    LL X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=(X<<3)+(X<<1)+c-'0',c=getchar();
    return X*w;
}
LL n;
LL buy,fd,fc,sd,sc;
const LL N=20010,M=2000010;
const LL INF=0x3f3f3f3f;
struct Edge { LL u,v,cap,cost,nxt; } e[M<<1];
LL head[N],cnt=0;
inline void add(LL u,LL v,LL cap,LL cost) {
    e[cnt].u=u; e[cnt].v=v;
    e[cnt].cap=cap; e[cnt].cost=cost;
    e[cnt].nxt=head[u]; head[u]=cnt++;
    e[cnt].u=v; e[cnt].v=u;
    e[cnt].cap=0; e[cnt].cost=-cost;
    e[cnt].nxt=head[v]; head[v]=cnt++;
}
LL dis[N],last[N];
bool inq[N];
inline bool SPFA(LL s,LL t) {
    memset(inq,false,sizeof(inq));
    memset(last,-1,sizeof(last));
    memset(dis,0x3f3f3f3f,sizeof(dis));
    queue<LL> Q; Q.push(s); inq[s]=true; dis[s]=0;
    while (!Q.empty()) {
        LL u=Q.front(); Q.pop(); inq[u]=false;
        for (re LL i=head[u];i!=-1;i=e[i].nxt) {
            LL v=e[i].v;
            if (e[i].cap&&dis[v]>dis[u]+e[i].cost) {
                dis[v]=dis[u]+e[i].cost;
                last[v]=i;
                if (!inq[v])
                {
                    Q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    if (last[t]==-1) return false;
    else return true;
}
inline LL MCMF(LL s,LL t) {
    LL flow=0;
    LL minflow,mincost=0;
    while (SPFA(s,t)) {
        minflow=INF+1;
        for (re LL i=last[t];i!=-1;i=last[e[i].u])
            if (e[i].cap<minflow) minflow=e[i].cap;
        flow+=minflow;
        for (re LL i=last[t];i!=-1;i=last[e[i].u]) {
            e[i].cap-=minflow;
            e[i^1].cap+=minflow;
        }
        mincost+=dis[t]*minflow;
    }
    return mincost;
}
LL r[N];
inline void build(LL s,LL t) {
    for (re LL i=1;i<=n;i++) {
        add(s,i,r[i],0);
        add(i+n,t,r[i],0);
        add(s,i+n,INF,buy);
        if (i+1<=n) add(i,i+1,INF,0);
        if (i+fd<=n) add(i,i+n+fd,INF,fc);
        if (i+sd<=n) add(i,i+n+sd,INF,sc);
    }
}
int main() {
    memset(head,-1,sizeof(head));
    n=read();
    for (re LL i=1;i<=n;i++) r[i]=read();
    buy=read(),fd=read(),fc=read(),sd=read(),sc=read();
    LL s=0,t=n+n+1; build(s,t);
    printf("%lld",MCMF(s,t));
    return 0;
}
