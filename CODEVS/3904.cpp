#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;
int n,m,r,c;
int Matrix[20][20];
int cost[20][20];
int cost_[20];
bool chosen_row[20];
int ans=INT_MAX;
void dfs(int row,int tot);
void DP();
void dfs(int row,int tot)
{
  if(tot>r) return;
  if(tot==r)
  {
    DP();
    return;
  }else{
    for(int i=row+1;i<=n;i++)
    {
      chosen_row[i]=1;
      dfs(i,tot+1);
      chosen_row[i]=0;
    }
  }
}
void DP()
{
  /*for(int o=1;o<=n;o++) if(chosen_row[o]) printf("1 ");else printf("0 ");
  printf(":\n");*/
  int DP[20][20];
  memset(DP,0x3f3f3f3f,sizeof(DP));
  memset(cost,0,sizeof(cost));
  memset(cost_,0,sizeof(cost_));
  //printf("cost:\n");
  for(int i=1;i<m;i++)
    for(int j=i+1;j<=m;j++)
    {
      for(int k=1;k<=n;k++)
        if(chosen_row[k]) cost[i][j]+=abs(Matrix[k][i]-Matrix[k][j]);
      //printf("%d,%d:%d\n",i,j,cost[i][j]);
    }
  //printf("cost_:\n");
  for(int i=1;i<=m;i++)
  {
    int last=-1;
    for(int k=1;k<=n;k++)
      if(chosen_row[k]) {last=k;break;}
    if(last!=-1) for(int j=last+1;j<=n;j++)
    {
      if(chosen_row[j])
      {
        cost_[i]+=abs(Matrix[last][i]-Matrix[j][i]);
        last=j;
      }
    }
    //printf("%d ",cost_[i]);
  }
  //printf("\n");
  for(int i=1;i<=m;i++)
  {
    DP[i][1]=cost_[i];
    if(c==1) ans=min(ans,cost_[i]);//notice!!!!!
  }
  for(int i=1;i<=m;i++)
      for(int j=2;j<=c&&j<=i;j++)
        for(int k=1;k<i;k++)
          {
            DP[i][j]=min(DP[i][j],DP[k][j-1]+cost[k][i]+cost_[i]);
            if(j==c)
            {
              ans=min(DP[i][j],ans);
              /*printf("%d,%d,%d:\n",i,j,ans);
              for(int o=1;o<=n;o++) if(chosen_row[o]) printf("1 ");else printf("0 ");
              printf("\n");*/
            }
          }
}
int main()
{
  scanf("%d%d%d%d",&n,&m,&r,&c);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
      scanf("%d",&Matrix[i][j]);
  dfs(0,0);
  printf("%d\n",ans);
  return 0;
}
