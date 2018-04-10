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
const int MAXN=1010;
const int MAXM=300100;
struct node{
    int nxt,v;
}Edge[MAXM];
struct NODE{int l,r;}Line[MAXN];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int dfn[MAXN],low[MAXN],stk[MAXN],top,cnt,SCC,bl[MAXN],n,m;
bool ins[MAXN];
void tarjan(int x)
{
    stk[++top]=x;ins[x]=1;
    dfn[x]=low[x]=++cnt;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
        else if(ins[v]) low[x]=min(dfn[v],low[x]);
   }
   if(dfn[x]==low[x])
   {
       ++SCC;
       while(top&&stk[top]!=x)
       {
           ins[stk[top]]=0;
           bl[stk[top]]=SCC;
           top--;
       }
       top--;bl[x]=SCC;
       ins[x]=0;
   }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&Line[i].l,&Line[i].r);
        if(Line[i].l>Line[i].r) swap(Line[i].l,Line[i].r);
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=i+1;j<=m;j++)
        {
            if((Line[j].l>=Line[i].l&&Line[j].l<=Line[i].r&&Line[j].r>=Line[i].r)||(Line[j].r>=Line[i].l&&Line[j].r<=Line[i].r&&Line[j].l<=Line[i].l))
                add(i,j+501),add(i+501,j),add(j+501,i),add(j,i+501);
        }
    }
    for(int i=1;i<=m;i++)
        if(!dfn[i]) tarjan(i);
    bool ok=1;
    for(int i=1;i<=m;i++)
        if(bl[i]==bl[i+501]) ok=0;
    puts(ok?"panda is telling the truth...":"the evil panda is lying again");
}
