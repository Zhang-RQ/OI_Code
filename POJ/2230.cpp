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
const int MAXN=1E4+5;
const int MAXM=1E5+5;
struct node{
    int nxt,v;
    bool vis;
}Edge[MAXM];
int head[MAXN],cnt_e,n,m,u,v;
int stk[MAXM],top;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void dfs(int x)
{
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        if(!Edge[i].vis)
        {
            Edge[i].vis=1;
            dfs(Edge[i].v);
            stk[++top]=i;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&u,&v),
        add(u,v),add(v,u);
    dfs(1);
    puts("1");
    for(int i=top;i>=1;i--)
        printf("%d\n",Edge[stk[i]].v);
}
