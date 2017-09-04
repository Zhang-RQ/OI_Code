#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int DP[1000][1000];
int temp[620];
const int inf=0x3f3f3f3f;
struct Node{
  int l,r,dis;
}data[310];
int main()
{
  int T;
  scanf("%d",&T);
  while(T--)
  {
    int n;
    scanf("%d",&n);
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
      scanf("%d%d%d",&data[i].l,&data[i].r,&data[i].dis);
      temp[++cnt]=data[i].l;
      temp[++cnt]=data[i].r;
    }
    sort(temp+1,temp+cnt+1);
    cnt=unique(temp+1,temp+1+cnt)-temp-1;
    for(int i=1;i<=n;i++)
    {
      data[i].l=lower_bound(temp+1,temp+1+cnt,data[i].l)-temp;
      data[i].r=lower_bound(temp+1,temp+1+cnt,data[i].r)-temp;
      //printf("%d %d\n",data[i].l,data[i].r);
    }
    cnt++;
    for(int i=0;i<=cnt;i++)
    {
      for(int j=0;j<=cnt;j++)
      {
        //if(i==j) {DP[i][j]=0;continue;}
        //printf("%d %d\n",i,j);
        int dist=-1;
        for(int k=1;k<=n;k++) if(data[k].l>i&&data[k].r<j&&(dist==-1||data[dist].dis<data[k].dis)) dist=k;
        if(dist==-1) {DP[i][j]=0;continue;}
        DP[i][j]=inf;
        for(int k=data[dist].l;k<=data[dist].r;k++) DP[i][j]=min(DP[i][j],DP[i][k]+DP[k][j]+data[dist].dis)/*,printf("\n%d,%d:%d\n",i,j,DP[i][j])*/;
      }
    }
      printf("%d\n",DP[0][cnt]);
  }
}
