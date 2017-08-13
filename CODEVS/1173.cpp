#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct A{
  int v,next;
}Edge[1000000];
int cnt=1;
int MAX[100010],MIN[100010];
int Data[100010];
int list[100010][2];
bool inq[100010];
int n,m,a,b,c;
int ans=-1;
void addedge(int u,int v)
{
  Edge[cnt].next=list[u][0];Edge[cnt].v=v;list[u][0]=cnt++;
  Edge[cnt].next=list[v][1];Edge[cnt].v=u;list[v][1]=cnt++;
}
queue<int> q;
void spfa_1()
{
  MIN[1]=Data[1];
  q.push(1);
  inq[1]=true;
  while(!q.empty())
  {
    int temp=q.front();
    q.pop();
    inq[temp]=false;
    for(int i=list[temp][0];i;i=Edge[i].next)
    {
      int v=Edge[i].v;
      if(MIN[v]>MIN[temp]||MIN[v]>Data[v])
      {
        MIN[v]=min(MIN[temp],Data[v]);
        if(!inq[v]) q.push(v),inq[v]=1;
      }
    }
  }
}
void spfa_2()
{
  memset(inq,false,sizeof(inq));
  MIN[n]=Data[n];
  q.push(n);
  inq[n]=true;
  while(!q.empty())
  {
    int temp=q.front();
    q.pop();
    inq[temp]=false;
    for(int i=list[temp][1];i;i=Edge[i].next)
    {
      int v=Edge[i].v;
      if(MAX[v]<MAX[temp]||MAX[v]<Data[v])
      {
        MAX[v]=max(MAX[temp],Data[v]);
        if(!inq[v]) q.push(v),inq[v]=1;
        ans=max(ans,MAX[v]-MIN[v]);
      }
    }
  }
}
int main()
{
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++) scanf("%d",&Data[i]),MIN[i]=105;
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d%d",&a,&b,&c);
    addedge(a,b);
    if(c==2) addedge(b,a);
  }
  spfa_1();
  spfa_2();
  printf("%d\n",ans);
}
