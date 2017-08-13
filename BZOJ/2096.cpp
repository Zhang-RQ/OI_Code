#include<cstdio>
#include<queue>
using namespace std;
int N[1000005];
int maxn[1000005];
int minn[1000005];
deque<int> q1;
deque<int> q2;
int main()
{
  deque<int>::iterator a;
  int n,k,l,r,i;
  l=1;
  r=1;
  /*int minf=1;
  int mine=2;
  int maxf=1;
  int maxe=2;*/
  int ans=-100;
  scanf("%d%d",&k,&n);
  for(i=1;i<=n;i++) scanf("%d",&N[i]);
  /*q1.push_front(1);
  q2.push_front(1);
  for(r=2;r<=n;r++)
  {
    while(N[r]>N[q1.back()]&&(!q1.empty())) q1.pop_back();
    q1.push_back(r);
    while(N[r]<N[q2.back()]&&(!q2.empty())) q2.pop_back();
    q2.push_back(r);
    while(N[q1.front()]-N[q2.front()]>k)
    {
      if(q1.front()>q2.front()) l=q2.front()+1,q2.pop_front();
      else l=q1.front()+1,q1.pop_front();
    }
    ans=max(ans,r-l+1);
  }
  /*minn[2]=1;
  maxn[2]=1;
  for(r=2;r<=n;r++)
  {
    while(N[i]>N[maxn[maxe]]&&maxe!=maxf)  maxe--;
    maxn[++maxe]=i;
    while(N[i]<N[minn[mine]]&&mine!=minf)  mine--;
    minn[++mine]=i;
    if(N[maxn[maxf+1]]-N[minn[minf+1]]>k)
    {
      if(minn[minf+1]<maxn[maxf+1]) minf++,l=minn[minf+1];
      else maxf++,l=maxn[maxf+1];
    }
    ans=max(ans,r-l);
  }*/
  /*printf("%d %d %d %d\n",maxf,maxe,minf,mine);
  for(i=maxf;i<=maxe;i++) printf("%d ",N[maxn[i]]);
  printf("\n");
  for(i=minf;i<=mine;i++) printf("%d ",N[minn[i]]);
  printf("\n");*/
  /*for(a=q1.begin();a!=q1.end();a++) printf("%d ",N[*a]);
  printf("\n");
  for(a=q2.begin();a!=q2.end();a++) printf("%d ",N[*a]);
  printf("\n");*/
  printf("%d\n",ans);
  return 0;
}
