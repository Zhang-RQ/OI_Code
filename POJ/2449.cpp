#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int s,t,m,n,k;
int f[1100];
struct Node{
    int w,v,nxt;
}Edge[100000*2+100];
struct Node2{
    int f,id,now;
    Node2(){}
    Node2(int f1,int id1,int now1){
        f=f1;id=id1;now=now1;
    }
    friend bool operator <(Node2 a,Node2 b)
    {
        if(!(a.f+a.now==b.f+b.now))   return a.f+a.now>b.f+b.now;
        else    return a.f>b.f;
    }
};
int head[1100][2];
int cnt=0;
void add(int u,int v,int w)
{
    Edge[++cnt].nxt=head[u][0];Edge[cnt].w=w;Edge[cnt].v=v;head[u][0]=cnt;
    Edge[++cnt].nxt=head[v][1];Edge[cnt].w=w;Edge[cnt].v=u;head[v][1]=cnt;
}
void spfa()
{
    queue<int> q;
    bool inq[1100];
    memset(inq,0,sizeof(inq));
    memset(f,0x3f,sizeof(f));
    q.push(t);f[t]=0;inq[t]=true;
    while(q.size())
    {
        int tmp=q.front();q.pop();inq[tmp]=false;
        for(int i=head[tmp][1];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(f[v]>f[tmp]+Edge[i].w)
            {
                f[v]=f[tmp]+Edge[i].w;
                if(!inq[v])
                {
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
}
int ans=-1;
void Astar()
{
    priority_queue<Node2> q;
    int cnt=0;
    q.push(Node2(f[s],s,0));
    while(q.size())
    {
        Node2 tmp=q.top();q.pop();
        if(tmp.id==t)
        {
            cnt++;
            if(cnt==k) {ans=tmp.now;return;}
        }
        //printf("%d  %d  %d\n",tmp.id,tmp.f,tmp.now);
        for(int i=head[tmp.id][0];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            q.push(Node2(f[v],v,tmp.now+Edge[i].w));
        }
    }
}
int main()
{
    int u,v,w;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    scanf("%d%d%d",&s,&t,&k);
    spfa();
    //for(int i=1;i<=n;i++) printf("%d\n",f[i]);
    Astar();
    printf("%d\n",ans);
}
