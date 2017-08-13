#include<cstdio>
using namespace std;
int L,N,M;
int pos[50010];
int ans;
bool check(int x)
{
  int lastpos=0;
  int cnt=0;
  for(int i=1;i<=N;i++)
  {
    if(pos[i]-lastpos<x)
    {
      cnt++;
      continue;
    }
    lastpos=pos[i];
  }
  if(cnt>M) return false;
  else return true;
}
int main()
{
  scanf("%d%d%d",&L,&N,&M);
  for(int i=1;i<=N;i++)  scanf("%d",&pos[i]);
  pos[++N]=L;
  int l=1,r=L;
  int ans=0;
  while(l<=r)
  {
    int mid=(l+r)/2;
    if(check(mid))
    {
      ans=mid;
      l=mid+1;
    }
    else r=mid-1;
  }
  printf("%d\n",ans);
}
