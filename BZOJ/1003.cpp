#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
inline int min(int a,int b)
{
    if(a<b) return a;
    else return b;
}
struct Node{
    int val,to,next;
}Edge[410];
int Adjlist[25];
int cnt=1;
bool blocked[23][110],flag[23];
bool in[25];
int dis[25];
int f[110];
int n,m,K,e,u,v,w,d,P,a,b;
int cost[110][110];
queue<int> Q;
void add(int u,int v,int val)
{
    Edge[cnt].next=Adjlist[u];
    Edge[cnt].to=v;
    Edge[cnt].val=val;
    Adjlist[u]=cnt;
    cnt++;
    return;
}

int spfa()
{
    memset(dis,0x3f3f3f3f,sizeof(dis));
    memset(in,false,sizeof(in));
    while(!Q.empty()) Q.pop();
    dis[1]=0;
    Q.push(1);
    in[1]=true;
    while(!Q.empty())
    {
        int temp=Q.front();
        Q.pop();
        in[temp]=false;
        for(int i=Adjlist[temp];i;i=Edge[i].next)
        {
            if(dis[Edge[i].to]>dis[temp]+Edge[i].val&&!flag[temp])
            {
                dis[Edge[i].to]=dis[temp]+Edge[i].val;
                if(!in[Edge[i].to])
                {
                    in[Edge[i].to]=true;
                    Q.push(Edge[i].to);
                }
            }
        }
    }
    return dis[m];
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&K,&e);
    for(int i=1;i<=e;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    scanf("%d",&d);
    for(int i=1;i<=d;i++)
    {
        scanf("%d%d%d",&P,&a,&b);
        for(int j=a;j<=b;j++) blocked[P][j]=true;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            memset(flag,0,sizeof(flag));
            for(int i1=1;i1<=m;i1++)
                for(int i2=i;i2<=j;i2++)
                    flag[i1]=flag[i1]|blocked[i1][i2];
            cost[i][j]=spfa();
        }
    }
     for (int i=1;i<=n;++i)
        for (int j=i;j<=n;++j)
            if (cost[i][j]<0x3f3f3f3f) cost[i][j]*=(j-i+1);
    for(int i=1;i<=n;i++) f[i]=cost[1][i];
    for(int i=2;i<=n;i++)
        for(int j=1;j<i;j++)
        {
            f[i]=min(f[i],f[j]+cost[j+1][i]+K);
        }
    printf("%d\n",f[n]);
}
