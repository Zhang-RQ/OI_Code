#include<cstdio>
#include<algorithm>
using namespace std;
struct Node{
  int a,b,val;
}Data[100010];
int F[40010];
bool cmp(Node a,Node b)
{
  return a.val>b.val;
}
int find(int x)
{
  if(x==F[x]) return x;
  else return F[x]=find(F[x]);
}
int main()
{
  int n,m;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++) scanf("%d%d%d",&Data[i].a,&Data[i].b,&Data[i].val);
  sort(Data+1,Data+1+m,cmp);
  for(int i=1;i<=n*2;i++) F[i]=i;
  for(int i=1;i<=m;i++)
  {
    int x=find(Data[i].a);
    int y=find(Data[i].b);
    if(x==y)
    {
      printf("%d\n",Data[i].val);
      return 0;
    }
    F[x]=find(Data[i].b+n);
    F[y]=find(Data[i].a+n);
  }
  printf("0\n");
  return 0;
}
