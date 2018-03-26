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
const int MAXN=2000100;
const int MAXM=MAXN<<1;
int n,m;
int c[MAXN],num,ans;
int tot,tmp[MAXN];
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,v;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void dfs(int x,int fa)
{
    for(int i=head[x];i;i=Edge[i].nxt)
        if(Edge[i].v!=fa)
            dfs(Edge[i].v,x);
    tot=0;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(Edge[i].v!=fa) tmp[++tot]=c[Edge[i].v];
    sort(tmp+1,tmp+1+tot);
    for(int i=1;i<=tot;i++)
    {
        if(c[x]+tmp[i]-1>m) break;
        else c[x]+=(tmp[i]-1),++ans;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&c[i]);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&num);c[i]+=num;
        for(int j=1;j<=num;j++)
            scanf("%d",&v),v++,add(v,i),add(i,v);
    }
    dfs(1,0);
    printf("%d\n",ans);
}
