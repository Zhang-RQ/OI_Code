#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int sticks[70];
bool flag=false;
bool vis[70];
int len;
int N;
bool cmp(int a,int b)
{
  return a>b;
}
void DFS(int used,int len_now,int now_s)
{
  if(flag) return;
  if(len_now==0)
  {
    int k=1;
    while(vis[k]) k++;
    vis[k]=true;
    DFS(used+1,sticks[k],k+1);
    vis[k]=false;
    return;
  }
  if(len_now==len)
  {
    //printf("1\n");
    if(used==N)
    {
      flag=true;
      return;
    }
    DFS(used,0,0);
    return;
  }
  for(int i=now_s;i<=N;i++)
  {
    if(!vis[i]&&sticks[i]+len_now<=len)
    {
      if(!vis[i-1]&&sticks[i-1]==sticks[i]) continue;//notice
      vis[i]=true;
      DFS(used+1,len_now+sticks[i],i+1);
      vis[i]=false;
    }
  }
}
int main()
{
  while(~scanf("%d",&N)&&N)
  {
    memset(sticks,0,sizeof(sticks));
    flag=false;
    int sum=0;
    for(int i=1;i<=N;i++) scanf("%d",&sticks[i]),sum+=sticks[i];
    sort(sticks+1,sticks+1+N,cmp);
    len=sticks[1];
    while(1)
    {
      if(sum%len==0)
      {
        memset(vis,0,sizeof(vis));
        DFS(0,0,1);
        if(flag) break;
      }
      len++;
    }
    printf("%d\n",len);
  }
}
