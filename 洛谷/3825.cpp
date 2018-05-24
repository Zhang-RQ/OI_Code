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
#include<cassert>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1E5+5;
const int MAXM=2E5+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];
struct lim{
    int i,j;
    char limi,limj;
}lm[MAXN];
int head[MAXN],cnt_e,n,m;
int dfn[MAXN],low[MAXN],cnt,stk[MAXN],top,SCC,bl[MAXN],pos[10],d,cc;
bool ins[MAXN],flag;
char s[MAXN];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void dfs(int x)
{
    dfn[x]=low[x]=++cnt;
    stk[++top]=x;ins[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!dfn[v]) dfs(v),low[x]=min(low[x],low[v]);
        else if(ins[v]) low[x]=min(low[x],dfn[v]);
    }
    if(dfn[x]==low[x])
    {
        ++SCC;
        while(stk[top]!=x)
        {
            ins[stk[top]]=0;
            bl[stk[top]]=SCC;
            top--;
        }
        ins[x]=0;bl[x]=SCC;
        top--;
    }
}
inline int get(int i,char x) //x is upper
{
    assert(s[i]!=x+'a'-'A');
    if(s[i]=='a') return x=='B'?i:i+n;
    if(s[i]=='b') return x=='A'?i:i+n;
    if(s[i]=='c') return x=='A'?i:i+n;
    return -1;
}
inline int get_c(int i,int x)
{
    if(s[i]=='a') return x==1?'B':'C';
    if(s[i]=='b') return x==1?'A':'C';
    if(s[i]=='c') return x==1?'A':'B';
    return -1;
}
inline int neg(int x){return x<=n?x+n:x-n;}
void build()
{
    for(int i=1,u,v;i<=m;i++)
    {
        if(lm[i].limi+'a'-'A'==s[lm[i].i]) continue;
        if(lm[i].limj+'a'-'A'==s[lm[i].j]) u=get(lm[i].i,lm[i].limi),add(u,neg(u));
        else u=get(lm[i].i,lm[i].limi),v=get(lm[i].j,lm[i].limj),add(u,v),add(neg(v),neg(u));
    }
}
bool judge()
{
    memset(head,0,sizeof head);cnt_e=0;
    memset(dfn,0,sizeof dfn);build();
    for(int i=1;i<=2*n;i++) if(!dfn[i]) dfs(i);
    for(int i=1;i<=n;i++) if(bl[i]==bl[i+n]) return 0;
    return 1;
}
int main()
{
    scanf("%d%d",&n,&d);
    scanf("%s",s+1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d %c %d %c",&lm[i].i,&lm[i].limi,&lm[i].j,&lm[i].limj);
    for(int i=1;i<=n;i++) if(s[i]=='x') pos[++cc]=i;
    for(int s=0;s<1<<d;s++)
    {
        for(int i=0;i<d;i++)
            if((s>>i)&1) ::s[pos[i+1]]='b';
            else ::s[pos[i+1]]='a';
        if(judge()) {flag=1;break;}
    }
    if(flag)
    {
        for(int i=1;i<=n;i++)
            putchar(get_c(i,(bl[i]<bl[i+n])));
        puts("");
    }
    else puts("-1");
    #ifdef LOCAL
        system("pause");
    #endif
}