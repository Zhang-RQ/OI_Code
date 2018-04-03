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
const int MAXN=4000010;
const int MAXM=4E5+5;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[100010],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int son[MAXN][10],mx[MAXN],par[MAXN];
int rt=1,cnt=1,du[100010],cc[100010],n,u,v;
ll ans=0;
int insert(int p,int x)
{
    int np=++cnt;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x]) son[p][x]=np,p=par[p];
    if(!p) par[np]=rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
        }
    }
    return np;
}
void dfs(int x,int fa,int now)
{
    int xx=insert(now,cc[x]);
    for(int i=head[x];i;i=Edge[i].nxt)
        if(Edge[i].v!=fa)
            dfs(Edge[i].v,x,xx);
}
void calc()
{
    for(int i=1;i<=cnt;i++) ans+=mx[i]-mx[par[i]];
}
int main()
{
    scanf("%d%*d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&cc[i]);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
        du[u]++;du[v]++;
    }
    for(int i=1;i<=n;i++)
        if(du[i]==1)  dfs(i,0,1);
    calc();
    printf("%lld\n",ans);
}
