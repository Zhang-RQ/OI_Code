#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct Node{
    int val,next,to;
}Edge[100010];
int DP[15][10100];
int Adjlist[10100];
int in[15][10100];
int k,s,t;
int ans=1000000;
struct p{
    int free,city;
    p(int a,int b):free(a),city(b){}
    Lux(){}
};
queue<p> q;
void spfa()
{
    memset(DP,10000,sizeof(DP));
    memset(in,0,sizeof(in));
    DP[0][s]=0;
    q.push(p(0,s));
    in[0][s]=1;
    while(!q.empty())
    {
        p temp=q.front();
        q.pop();
        in[temp.free][temp.city]=0;
        for(int i=Adjlist[temp.city];i!=-1;i=Edge[i].next)
        {
            if(DP[temp.free][Edge[i].to]>DP[temp.free][temp.city]+Edge[i].val)
            {
                DP[temp.free][Edge[i].to]=DP[temp.free][temp.city]+Edge[i].val;
                if(in[temp.free][Edge[i].to]==0)
                {
                    q.push(p(temp.free,Edge[i].to));
                    in[temp.free][Edge[i].to]=1;
                }
            }
        }
        if(temp.free<k) for(int i=Adjlist[temp.city];i!=-1;i=Edge[i].next)
        {
            if(DP[temp.free+1][Edge[i].to]>DP[temp.free][Edge[i].to])
            {
                    DP[temp.free+1][Edge[i].to]=DP[temp.free][Edge[i].to];
                    if(in[temp.free+1][Edge[i].to]==0)
                    {
                        q.push(p(temp.free+1,Edge[i].to));
                        in[temp.free+1][Edge[i].to]=1;
                    }
            }
        }
    }
    for(int i=0;i<=k;i++)
    {
        if(ans>DP[i][t]) ans=DP[i][t];
    }
}
int cnt=0;
void add(int from,int to,int val)
{
    Edge[cnt].next=Adjlist[from];
    Edge[cnt].to=to;
    Edge[cnt].val=val;
    Adjlist[from]=cnt;
    cnt++;
}
int main()
{
    int n,m;
    int tempval,tempfrom,tempto;
    int temp;
    memset(Adjlist,-1,sizeof(Adjlist));
    scanf("%d%d%d%d%d",&n,&m,&k,&s,&t);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&tempfrom,&tempto,&tempval);
        add(tempfrom,tempto,tempval);
        add(tempto,tempfrom,tempval);
    }
    spfa();
    printf("%d\n",ans);
    return 0;
}
/*
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 11000
#define M 51000
#define inf 0x3f3f3f3f
using namespace std;
struct KSD
{
    int v,len,next;
}e[M<<1];
int head[N],cnt;
struct Lux
{
    int x,y;
    Lux(int a,int b):x(a),y(b){}
    Lux(){}
};
void add(int u,int v,int len)
{
    ++cnt;
    e[cnt].v=v;
    e[cnt].len=len;
    e[cnt].next=head[u];
    head[u]=cnt;
}
int n,m,p,s,t;
int dist[11][N];
bool in[11][N];/*spfa的dist，标记在每一层都要有*/
queue<Lux>q;
int spfa()
{
    int i,v;
    memset(dist,0x3f,sizeof(dist));
    q.push(Lux(0,s));/*从第0层开始spfa*/
    dist[0][s]=0;
    in[0][s]=1;
    while(!q.empty())
    {
        Lux U=q.front();
        q.pop();
        in[U.x][U.y]=0;

        for(i=head[U.y];i;i=e[i].next)
        {
            v=e[i].v;/*先跑完这一层的最短路*/
            if(dist[U.x][v]>dist[U.x][U.y]+e[i].len)
            {
                dist[U.x][v]=dist[U.x][U.y]+e[i].len;
                if(!in[U.x][v])q.push(Lux(U.x,v)),in[U.x][v]=1;
            }
        }
        if(U.x<p)for(i=head[U.y];i;i=e[i].next)
        {/*如果还可以向下一层转移的话，就把这个点出发的每一条边都设为免费下一层转移，因为要记录每个点dist到底用了几个免费的路线，所以用二维数组--分层思想*/
            v=e[i].v;
            if(dist[U.x+1][v]>dist[U.x][U.y])
            {
                dist[U.x+1][v]=dist[U.x][U.y];
                if(!in[U.x+1][v])q.push(Lux(U.x+1,v)),in[U.x+1][v]=1;
            }
        }
    }

    int ret=inf;
    for(i=0;i<=p;i++)ret=min(ret,dist[i][t]);/*在每一层中都找到t的最小值（最多k条免费）,为什么要在每一层都找，而不是只在最后一层寻找呢。假设有这么一种情况，由s--t的最少的路上的途径数目少于k条，那么在k之前的某一层上就有dis=0，但是如果必须使用k条路径的话，那么就会找的一条路途数多于k的路来满足这个条件，那么只用第k层的dis自然不是正确结果了。*/
    return ret;
}

int main()
{
//    freopen("test.in","r",stdin);
    int i,j,k;
    int a,b,c;
    scanf("%d%d%d%d%d",&n,&m,&p,&s,&t);
    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);/*无向图建立双向边*/
        add(b,a,c);
    }
    printf("%d\n",spfa());
    return 0;
}
