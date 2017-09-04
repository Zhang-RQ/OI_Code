#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<climits>
using namespace std;
int ans,n;
int now[1050];
bool IDAx(int dep)
{
  if(dep>ans) return false;
  if((now[dep]<<(ans-dep))<n) return false;
  if(now[dep]==n) return true;
  for(int i=0;i<=dep;i++)
  {
    now[dep+1]=now[dep]+now[i];if(IDAx(dep+1)) return true;
    now[dep+1]=now[dep]-now[i];if(IDAx(dep+1)) return true;
  }
  return false;
}
int main()
{
  now[0]=1;
  while(~scanf("%d",&n)&&n)
  {
    for(ans=0;!IDAx(0);ans++);
    printf("%d\n",ans);
  }
}
