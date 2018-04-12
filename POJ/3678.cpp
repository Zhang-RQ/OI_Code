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
const int MAXN=2020;
const int MAXM=2E6+10;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,n,m,x,y,t;
int dfn[MAXN],bl[MAXN],low[MAXN],stk[MAXN],top,SCC,cnt;
bool ins[MAXN];
char str[10];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}          //a->1 a+1010->0
inline void insert(int a,int b,int op,int val) //1 AND 2 OR 3 XOR
{
    switch(op)
    {
        case 1:
            if(val) add(a+1010,a);
            else add(a,b+1010);
        break;
        case 2:
            if(val) add(a+1010,b);
            else add(a,a+1010);
        break;
        case 3:
            if(val) add(a,b+1010),add(a+1010,b);
            else add(a,b),add(a+1010,b+1010);
        break;
    }
}
void tarjan(int x)
{
    dfn[x]=low[x]=++cnt;
    stk[++top]=x;ins[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
        else if(ins[v]) low[x]=min(low[x],dfn[v]);
    }
    if(dfn[x]==low[x])
    {
        ++SCC;
        while(top&&stk[top]!=x)
        {
            bl[stk[top]]=SCC;
            ins[stk[top]]=0;
            top--;
        }
        top--;
        bl[x]=SCC;
        ins[x]=0;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%s",&x,&y,&t,str+1);
        x++;y++;
        if(str[1]=='A') insert(x,y,1,t),insert(y,x,1,t);
        else if(str[1]=='O') insert(x,y,2,t),insert(y,x,2,t);
        else if(str[1]=='X') insert(x,y,3,t),insert(y,x,3,t);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
        if(!dfn[i+1010]) tarjan(i+1010);
    bool ok=1;
    for(int i=1;i<=n;i++)
        if(bl[i]==bl[i+1010]) ok=0;
    puts(ok?"YES":"NO");
}
