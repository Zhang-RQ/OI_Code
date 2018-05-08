#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=2E4+5;
const int MAXM=4E4+10;
inline char nc(){
  static char buf[100000],*p1=buf,*p2=buf;
  return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline void read(int &x){
  char c=nc(),b=1;
  for (;!(c>='0' && c<='9');c=nc()) if (c=='-') b=-1;
  for (x=0;c>='0' && c<='9';x=x*10+c-'0',c=nc());
  x*=b;
}
struct __edge{
    int nxt,v,pre;
}Edge[MAXM];
int head[MAXN],cnt_e,n,k,a[MAXN],val[MAXN],siz,fa[MAXN],Cs,K;
int f[25520010],h[25520010],ans;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
inline void solve(int *f,int A,int B)
{
  int i,j=0,h=1,t=0;
  static int q[500010],p[500010];
  for(i=0;i<=k;i++,j+=B)
  {
    f[i]-=j;
    while(h<=t&&f[q[t]]<f[i])t--;
    q[++t]=i;
    while(i-q[h]>A)h++;
    p[i]=f[q[h]]+j;
  }
  memcpy(f,p,siz);
}
void dfs(int x)
{
    if(a[x]) solve(f+x*K,a[x],val[x]);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        memcpy(f+v*K,f+x*K,siz);
        dfs(v);
        int *s=f+x*K+1,*e=f+v*K;
        for(int j=1;j<=k;j++,++s,++e) *s=max(*s,*e+val[v]);
    }
}
void dfsr(int x,int y)
{
    y+=val[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        memcpy(h+v*K,h+x*K,siz);
        dfsr(v,y);
        int *s=h+x*K+1,*e=h+v*K;
        for(int i=1;i<=K;i++,++s,++e) *s=max(*s,*e+val[v]);
    }
    if(!head[x])
    {
        int *e=h+K*x+k,*s=f+K*x;
        for(int j=0;j<=k;j++,++s,--e) ans=max(ans,*s+*e+y);
    }
    if(a[x]) solve(h+x*K,a[x],val[x]);
}
int main()
{
    read(Cs);
    while(Cs--)
    {
        read(n);read(k);
        for(int i=1;i<=n;i++)
            read(fa[i]),read(a[i]),read(val[i]),a[i]--;
        K=k+1;siz=K*sizeof(int);
        memset(head,0,sizeof head);cnt_e=0;
        for(int i=1;i<=n;i++) if(fa[i]) add(fa[i],i);
        memset(f+K,0,siz);memset(h+K,0,siz);
        dfs(1);
        memset(head,0,sizeof head);cnt_e=0;
        for(int i=n;i>=1;i--) if(fa[i]) add(fa[i],i);
        ans=0;dfsr(1,0);
        printf("%d\n",ans);
    }
}
