#include<cstdio>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;
char s[110];
int len;
int DP[110][110][2];
bool vis[110][110][2];
bool same(int l,int r)
{
  int len=r-l+1;
  if(len%2==1) return false; //len&1
  len/=2;
  bool flag=true;
  for(int i=l;i<l+len;i++) if(s[i]!=s[i+len]) flag=false;
  return flag;
}
int dfs(int l,int r,bool m)
{
  int temp=r-l+1;
  if(l==r) return 1;
  if(vis[l][r][m]) return DP[l][r][m];
  vis[l][r][m]=true;
  if(m) for(int i=l;i<r;i++) temp=min(temp,dfs(l,i,1)+dfs(i+1,r,1)+1);
  for(int i=l;i<r;i++) temp=min(temp,dfs(l,i,m)+r-i);
  if(same(l,r)) temp=min(temp,dfs(l,(l+r)/2,0)+1);
  return DP[l][r][m]=temp;
}
int main()
{
  scanf("%s",s+1);
  len=strlen(s+1);
  printf("%d\n",dfs(1,len,1));
}
