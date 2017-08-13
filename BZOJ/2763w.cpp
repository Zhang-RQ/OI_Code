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
bool in[11][N];/*spfa��dist�������ÿһ�㶼Ҫ��*/
queue<Lux>q;
int spfa()
{
    int i,v;
    memset(dist,0x3f,sizeof(dist));
    q.push(Lux(0,s));/*�ӵ�0�㿪ʼspfa*/
    dist[0][s]=0;
    in[0][s]=1;
    while(!q.empty())
    {
        Lux U=q.front();
        q.pop();
        in[U.x][U.y]=0;

        for(i=head[U.y];i;i=e[i].next)
        {
            v=e[i].v;/*��������һ������·*/
            if(dist[U.x][v]>dist[U.x][U.y]+e[i].len)
            {
                dist[U.x][v]=dist[U.x][U.y]+e[i].len;
                if(!in[U.x][v])q.push(Lux(U.x,v)),in[U.x][v]=1;
            }
        }
        if(U.x<p)for(i=head[U.y];i;i=e[i].next)
        {/*�������������һ��ת�ƵĻ����Ͱ�����������ÿһ���߶���Ϊ�����һ��ת�ƣ���ΪҪ��¼ÿ����dist�������˼�����ѵ�·�ߣ������ö�ά����--�ֲ�˼��*/
            v=e[i].v;
            if(dist[U.x+1][v]>dist[U.x][U.y])
            {
                dist[U.x+1][v]=dist[U.x][U.y];
                if(!in[U.x+1][v])q.push(Lux(U.x+1,v)),in[U.x+1][v]=1;
            }
        }
    }

    int ret=inf;
    for(i=0;i<=p;i++)ret=min(ret,dist[i][t]);/*��ÿһ���ж��ҵ�t����Сֵ�����k����ѣ�,ΪʲôҪ��ÿһ�㶼�ң�������ֻ�����һ��Ѱ���ء���������ôһ���������s--t�����ٵ�·�ϵ�;����Ŀ����k������ô��k֮ǰ��ĳһ���Ͼ���dis=0�������������ʹ��k��·���Ļ�����ô�ͻ��ҵ�һ��·;������k��·�����������������ôֻ�õ�k���dis��Ȼ������ȷ����ˡ�*/
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
        add(a,b,c);/*����ͼ����˫���*/
        add(b,a,c);
    }
    printf("%d\n",spfa());
    return 0;
}
