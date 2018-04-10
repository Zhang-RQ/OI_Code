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
const int MAXM=1E5+5;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,T,n,m,x1,x2;
char s1[110],s2[110],t1,t2;
int tp1,tp2,dfn[MAXN],bl[MAXN],SCC,low[MAXN],cnt,stk[MAXN],top;
bool ins[MAXN],ok;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void tarjan(int x)
{
    stk[++top]=x;ins[x]=1;
    dfn[x]=low[x]=++cnt;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
        else if(ins[v]) low[x]=min(low[x],dfn[v]);
    }
    if(dfn[x]==low[x])
    {
        SCC++;
        while(top&&stk[top]!=x)
        {
            bl[stk[top]]=SCC;
            ins[stk[top]]=0;
            top--;
        }
        ins[x]=0;
        bl[x]=SCC;top--;
    }
}
int main() //1..100 xuan man,110...210 bu xuan man 220...320 xuan han,330...430 bu xuan han
{
    scanf("%d",&T);
    while(T--)
    {
        memset(head,0,sizeof head);cnt_e=0;
        memset(dfn,0,sizeof dfn);memset(low,0,sizeof low);
        memset(bl,0,sizeof bl);
        SCC=cnt=0;top=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) add(i,330+i),add(i+220,i+110);
        for(int i=1;i<=m;i++)
        {
            scanf("%s%s",s1+1,s2+1);
            sscanf(s1+1,"%c%d",&t1,&x1);
            sscanf(s2+1,"%c%d",&t2,&x2);
            tp1=t1=='m'?0:220;tp2=t2=='m'?0:220;
            add(x1+tp1+110,x2+tp2);
            add(x2+tp2+110,x1+tp1);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i]) tarjan(i);
        ok=1;
        for(int i=1;i<=n;i++)
            if(bl[i]==bl[i+110]||bl[i+220]==bl[i+330]) ok=0;
        puts(ok?"GOOD":"BAD");
    }
}
