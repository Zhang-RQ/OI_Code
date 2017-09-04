#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
int dis[10010];
bool inq[10010];
int out[10010];
int adjlist[2][10010];
struct node{
    int v,nxt;
}Edge[400100];
int cnt=0;
int s,t;
void add(int u,int v)
{
    ++out[u];
    Edge[cnt].nxt=adjlist[0][u];
    Edge[cnt].v=v;
    adjlist[0][u]=cnt++;
    Edge[cnt].nxt=adjlist[1][v];
    Edge[cnt].v=u;
    adjlist[1][v]=cnt++;
}
void bfs()
{
    queue<int> q;
    q.push(t);
    inq[t]=true;
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        for(int i=adjlist[1][tmp];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            --out[v];
            if(!inq[v]) q.push(v),inq[v]=true;
        }
  }
}
void spfa()
{
  memset(inq,0,sizeof(inq));
  memset(dis,0x3f,sizeof(dis));
  queue<int> q;
  q.push(s);
  dis[s]=0;
  inq[s]=true;
  while(!q.empty())
  {
    int tmp=q.front();
    q.pop();
    inq[tmp]=false;
    for(int i=adjlist[0][tmp];i;i=Edge[i].nxt)
    {
      int v=Edge[i].v;
      if(out[v]==0&&dis[v]>dis[tmp]+1)
      {
        dis[v]=dis[tmp]+1;
        if(!inq[v])
        {
          inq[v]=true;
          q.push(v);
        }
      }
    }
  }
}
int main()
{
    memset(out,0,sizeof(out));
  int n,m;
  int x,y;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&x,&y);
    add(x,y);
  }
  scanf("%d%d",&s,&t);
  bfs();
  spfa();
  if(dis[t]==0x3f3f3f3f) printf("-1\n");
  else printf("%d\n",dis[t]);
  return 0;
}
