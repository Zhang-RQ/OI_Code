#include<cstdio>
#include<queue>
using namespace std;
bool blocked[210][210];
int dir[210],len[210];
int dp[203][203][203];
int N,M,x,y,K;
deque<int> q;
int main()
{
  char temp;
  int t1,t2,t3;
  scanf("%d%d%d%d%d",&N,&M,&x,&y,&K);
  for(int i=1;i<=N;i++)
    for(int j=1;j<=M;j++)
    {
      scanf("%c",&temp);
      if(temp=='x') blocked[i][j]=true;
    }
  for(int i=1;i<=K;i++)
  {
    scanf("%d%d%d",&t1,&t2,&t3);
    dir[i]=t3;
    len[i]=t2-t1+1;
  }
  for(int i=1;i<=K;i++)
  {

  }
}
