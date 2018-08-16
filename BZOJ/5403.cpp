#include<bits/stdc++.h>

using namespace std;

const int MAXN=1E5+10;
const int MAXM=2E6+10;
typedef long long ll;

//#define id(x,y) (((x)-1)*n+(y))

int head[MAXN],val[55][55],cnt_e=1,S=0,T=100000,dis[MAXN],n,m,Ans;
int pre[MAXN],preedge[MAXN],flw[MAXN],k;
bool inq[MAXN];
queue<int> q;

inline int id(int x,int y){return (x-1)*n+y;}

struct __edge{
    int nxt,v,f,c;
}Edge[MAXM];

void add(int u,int v,int f,int c)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].f=f;
    Edge[cnt_e].c=c;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

void add2(int u,int v,int f,int c){add(u,v,f,c);add(v,u,0,-c);}

bool SPFA()
{
    memset(dis,0x3f,sizeof dis);
    q.push(S);dis[S]=0;flw[S]=1<<30;
    inq[S]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();inq[x]=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[v]<=dis[x]+Edge[i].c||!Edge[i].f) continue;
            dis[v]=dis[x]+Edge[i].c;
            pre[v]=x;preedge[v]=i;
            flw[v]=min(flw[x],Edge[i].f);
            if(!inq[v]) q.push(v),inq[v]=1;
        }
    }
    return dis[T]<=0;
}

int MCMF()
{
    int ret=0;
    while(SPFA()&&m)
    {
        int F=flw[T],x=T;
        m-=F;ret+=dis[T]*F;
        while(x!=S)
        {
            Edge[preedge[x]].f-=F;
            Edge[preedge[x]^1].f+=F;
            x=pre[x];
        }
    }
    return ret;
}

int main()
{
    freopen("marshland.in","r",stdin);
    freopen("marshland.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&val[i][j]),Ans+=val[i][j];
    for(int i=1,x,y;i<=k;i++)
        scanf("%d%d",&x,&y),val[x][y]=-1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(val[i][j]==-1) continue;
            if((i+j)%2) add2(id(i,j),id(i,j)+25000,1,-val[i][j]);
            else 
            {
                if(j&1)
                {
                    add2(S,id(i,j),1,0);
                    if(j>1&&val[i][j-1]!=-1) add2(id(i,j),id(i,j-1),1,0);
                    if(j<n&&val[i][j+1]!=-1) add2(id(i,j),id(i,j+1),1,0);
                    if(i>1&&val[i-1][j]!=-1) add2(id(i,j),id(i-1,j),1,0);
                    if(i<n&&val[i+1][j]!=-1) add2(id(i,j),id(i+1,j),1,0);
                }
                else 
                {
                    add2(id(i,j),T,1,0);
                    if(i>1&&val[i-1][j]!=-1) add2(id(i-1,j)+25000,id(i,j),1,0);
                    if(i<n&&val[i+1][j]!=-1) add2(id(i+1,j)+25000,id(i,j),1,0);
                    if(j>1&&val[i][j-1]!=-1) add2(id(i,j-1)+25000,id(i,j),1,0);
                    if(j<n&&val[i][j+1]!=-1) add2(id(i,j+1)+25000,id(i,j),1,0);
                }
            }
        }
    printf("%d\n",Ans+MCMF());
}
