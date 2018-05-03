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
const int MAXN=500010;
const int MAXM=1E6+5;
double f[MAXN];
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,n,u,v,a[MAXN],du[MAXN];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void dfs(int x,int fa,double cur)
{
    f[x]=cur+log(a[x]);
    for(int i=head[x];i;i=Edge[i].nxt)
        if(Edge[i].v!=fa) dfs(Edge[i].v,x,cur+log(du[x]-1));
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);du[u]++;du[v]++;
    }
    du[1]++;
    dfs(1,0,0);
    sort(f+1,f+1+n);
    int ans=1,cnt=1;
    for(int i=2;i<=n;i++)
        if(fabs(f[i-1]-f[i])<=1E-7)
            ans=max(ans,++cnt);
        else cnt=1;
    printf("%d\n",n-ans);
}
