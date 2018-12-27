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
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2010;
const int MAXM=10010;

struct __edge{
    int nxt,v,w;
}Edge[MAXM];

bool inq[MAXN];
int head[MAXN],cnt_e,T,n,m,cnt[MAXN],dis[MAXN];

inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}

bool SPFA()
{
    queue<int> q;
    q.push(1);inq[1]=1;dis[1]=0;
    while(!q.empty())
    {
        int x=q.front();q.pop();inq[x]=0;
        if(++cnt[x]>n) return false;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[x]+Edge[i].w<dis[v])
            {
                dis[v]=dis[x]+Edge[i].w;
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
    return true;
}

void solve()
{
    cnt_e=0;
    memset(inq,0,sizeof inq);
    memset(head,0,sizeof head);
    memset(dis,0x3f,sizeof dis);
    memset(cnt,0,sizeof cnt);
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        if(w>=0) add(v,u,w);
    }
    puts(SPFA()?"N0":"YE5");
}

int main()
{
    for(scanf("%d",&T);T--;solve());
}