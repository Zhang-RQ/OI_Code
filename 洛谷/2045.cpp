#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=55;
const int MAXT=5*MAXN*MAXN;
const int INF=1<<30;

struct edge_t{
    int v,nxt,f,c;
}Edge[MAXT<<2];

int n,k;
int head[MAXT],cnt_e=1,S,T=MAXT-1,flw[MAXT];
int dis[MAXT],pre[MAXT],pree[MAXT],inq[MAXT];
queue<int> q;

int id(int x,int y,int f){return (x-1)*n+y+f*n*n;}

void _add(int u,int v,int f,int c)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].f=f;
    Edge[cnt_e].c=c;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

void add(int u,int v,int f,int c,int f2=0){_add(u,v,f,c);_add(v,u,f2,-c);}

bool SPFA()
{
    memset(dis,0x3f,sizeof dis);
    q.push(S);dis[S]=0;inq[S]=1;
    flw[S]=INF;
    while(!q.empty())
    {
        int x=q.front();q.pop();inq[x]=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            if(!Edge[i].f) continue;
            int v=Edge[i].v;
            if(dis[v]>dis[x]+Edge[i].c)
            {
                flw[v]=min(flw[x],Edge[i].f);
                dis[v]=dis[x]+Edge[i].c;
                pre[v]=x;pree[v]=i;
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
    return dis[T]!=0x3f3f3f3f;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1,x;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&x);
            add(id(i,j,0),id(i,j,1),1,-x);
            add(id(i,j,0),id(i,j,1),INF,0);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i!=n) add(id(i,j,1),id(i+1,j,0),INF,0);
            if(j!=n) add(id(i,j,1),id(i,j+1,0),INF,0);
        }
    add(S,id(1,1,0),k,0);add(id(n,n,1),T,k,0);
    int Ans=0;
    while(SPFA())
    {
        Ans-=dis[T]*flw[T];
        int x=T;
        while(x!=S)
        {
            Edge[pree[x]].f-=flw[T];
            Edge[pree[x]^1].f+=flw[T];
            x=pre[x];
        }
    }
    printf("%d\n",Ans);
}