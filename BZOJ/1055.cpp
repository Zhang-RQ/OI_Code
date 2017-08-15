#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char string[210];
int sn[210];
int data[6][17][4];
bool DP[210][210][5],vis[210][210][5];
int len[5];
int lenn;
void inti()
{
  char temp[10];
  for(int i=1;i<=len[1];i++)
  {
    scanf("%s",temp);
    switch(temp[0])
    {
      case 'W':data[1][i][1]=1;break;
      case 'I':data[1][i][1]=2;break;
      case 'N':data[1][i][1]=3;break;
      case 'G':data[1][i][1]=4;break;
    }
    switch(temp[1])
    {
      case 'W':data[1][i][2]=1;break;
      case 'I':data[1][i][2]=2;break;
      case 'N':data[1][i][2]=3;break;
      case 'G':data[1][i][2]=4;break;
    }
    //printf("%d %d",data[1][i][1],data[1][i][2]);
  }
  for(int i=1;i<=len[2];i++)
  {
    scanf("%s",temp);
    switch(temp[0])
    {
      case 'W':data[2][i][1]=1;break;
      case 'I':data[2][i][1]=2;break;
      case 'N':data[2][i][1]=3;break;
      case 'G':data[2][i][1]=4;break;
    }
    switch(temp[1])
    {
      case 'W':data[2][i][2]=1;break;
      case 'I':data[2][i][2]=2;break;
      case 'N':data[2][i][2]=3;break;
      case 'G':data[2][i][2]=4;break;
    }
    //printf("%d %d",data[2][i][1],data[2][i][2]);
  }
  for(int i=1;i<=len[3];i++)
  {
    scanf("%s",temp);
    switch(temp[0])
    {
      case 'W':data[3][i][1]=1;break;
      case 'I':data[3][i][1]=2;break;
      case 'N':data[3][i][1]=3;break;
      case 'G':data[3][i][1]=4;break;
    }
    switch(temp[1])
    {
      case 'W':data[3][i][2]=1;break;
      case 'I':data[3][i][2]=2;break;
      case 'N':data[3][i][2]=3;break;
      case 'G':data[3][i][2]=4;break;
    }
    //printf("%d %d",data[3][i][1],data[3][i][2]);
  }
  for(int i=1;i<=len[4];i++)
  {
    scanf("%s",temp);
    switch(temp[0])
    {
      case 'W':data[4][i][1]=1;break;
      case 'I':data[4][i][1]=2;break;
      case 'N':data[4][i][1]=3;break;
      case 'G':data[4][i][1]=4;break;
    }
    switch(temp[1])
    {
      case 'W':data[4][i][2]=1;break;
      case 'I':data[4][i][2]=2;break;
      case 'N':data[4][i][2]=3;break;
      case 'G':data[4][i][2]=4;break;
    }
    //printf("%d %d",data[4][i][1],data[4][i][2]);
  }
  scanf("%s",string);
  lenn=strlen(string);
  for(int i=0;i<lenn;i++)
  {
    switch(string[i])
    {
      case 'W':sn[i+1]=1;break;
      case 'I':sn[i+1]=2;break;
      case 'N':sn[i+1]=3;break;
      case 'G':sn[i+1]=4;break;
    }
    //printf("%d",sn[i+1]);
  }
  //printf("\n");
}
bool dfs(int l,int r,int k)
{
  if(vis[l][r][k]) return DP[l][r][k];
  vis[l][r][k]=true;
  if(l==r)
  {
    if(sn[l]==k) return DP[l][r][k]=true;
    else return DP[l][r][k]=false;
  }
  for(int i=1;i<=len[k];i++)
    for(int j=l;j<r;j++) if(dfs(l,j,data[k][i][1])&&dfs(j+1,r,data[k][i][2])) return DP[l][r][k]=true;
  return DP[l][r][k]=false;
}
int main()
{
  scanf("%d%d%d%d",&len[1],&len[2],&len[3],&len[4]);
  inti();
  bool flag=false;
  if(dfs(1,lenn,1)) printf("W"),flag=true;
  if(dfs(1,lenn,2)) printf("I"),flag=true;
  if(dfs(1,lenn,3)) printf("N"),flag=true;
  if(dfs(1,lenn,4)) printf("G"),flag=true;
  if(!flag) printf("The name is wrong!");
  printf("\n");
  return 0;
}
