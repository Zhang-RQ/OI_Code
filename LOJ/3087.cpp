#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

int n,m,k,b[MAXN],S[MAXN],cnts;
vector<pair<int,int> > G[MAXN];
priority_queue<pair<ll,int>,vector<pair<ll,int> > ,greater<pair<ll,int> > > pq;
ll dis[MAXN];

void Dijkstra()
{
    memset(dis,0x3f,sizeof dis);
    for(int i=1;i<=cnts;i++)
        dis[S[i]]=0,pq.emplace(0,S[i]);
    while(!pq.empty())
    {
        pair<ll,int> x=pq.top();pq.pop();
        if(x.first!=dis[x.second])
            continue;
        for(auto e:G[x.second])
        {
            int v=e.first;
            if(dis[v]<=x.first+e.second)
                continue;
            dis[v]=x.first+e.second;
            pq.emplace(dis[v],v);
        }
    }
}

void solve()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        G[i].clear();
    for(int i=1,u,v,w;i<=m;i++)
        scanf("%d%d%d",&u,&v,&w),
        G[u].emplace_back(v,w);
    for(int i=0;i<k;i++)
        scanf("%d",&b[i]);
    ll Ans=1ll<<60;
    for(int bit=0;(1<<bit)<k;bit++)
    {
        cnts=0;
        for(int i=0;i<k;i++)
            if((i>>bit)&1)
                S[++cnts]=b[i];
        Dijkstra();
        for(int i=0;i<k;i++)
            if(!((i>>bit)&1))
                Ans=min(Ans,dis[b[i]]);
        cnts=0;
        for(int i=0;i<k;i++)
            if(!((i>>bit)&1))
                S[++cnts]=b[i];
        Dijkstra();
        for(int i=0;i<k;i++)
            if((i>>bit)&1)
                Ans=min(Ans,dis[b[i]]);
    }
    printf("%lld\n",Ans);
}

int main()
{
    int T;
    for(scanf("%d",&T);T--;solve());
}
