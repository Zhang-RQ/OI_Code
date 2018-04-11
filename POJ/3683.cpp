// WA
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
const int MAXN=2010;
const int MAXM=2E6+5;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
struct Node{int l,r,len;} a[MAXN];
int n,t,tt,bl[MAXN],SCC,dfn[MAXN],low[MAXN],stk[MAXN],top,cnt;
char t1[110],t2[110];
bool ins[MAXN];
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
    if(low[x]==dfn[x])
    {
        ++SCC;
        while(top&&stk[top]!=x)
        {
            ins[stk[top]]=0;
            bl[stk[top]]=SCC;
            top--;
        }
        bl[x]=SCC;ins[x]=0;top--;
    }
}
inline bool intersect(const int &l,const int &r,const int &L,const int &R){return ((l<=L&&r>L)||(L<=l&&R>l));}
int main()
{
    while(~scanf("%d",&n))
    {
        memset(head,0,sizeof head);
        memset(dfn,0,sizeof dfn);
        memset(low,0,sizeof low);
        memset(bl,0,sizeof bl);
        cnt_e=0;top=0;SCC=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%s%s%d",t1+1,t2+1,&a[i].len);
            sscanf(t1+1,"%d:%d",&t,&tt);
            a[i].l=t*60+tt;
            sscanf(t2+1,"%d:%d",&t,&tt);
            a[i].r=t*60+tt;
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(i==j) continue;
                if(intersect(a[i].l,a[i].l+a[i].len,a[j].l,a[j].l+a[j].len))
                add(i,j+1010);
                if(intersect(a[i].l,a[i].l+a[i].len,a[j].r-a[j].len,a[j].r))
                add(i,j);
                if(intersect(a[i].r-a[i].len,a[i].r,a[j].l,a[j].l+a[j].len))
                add(i+1010,j+1010);
                if(intersect(a[i].r-a[i].len,a[i].r,a[j].r-a[j].len,a[j].r))
                add(i+1010,j);
            }
        }
        for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i);
        for(int i=1;i<=n;i++)
        if(!dfn[i+1010]) tarjan(i+1010);
        bool ok=1;
        for(int i=1;i<=n;i++)
        if(bl[i]==bl[i+1010]) ok=0;
        if(ok)
        {
            puts("YES");
            for(int i=1;i<=n;i++)
            {
                if(bl[i]<bl[i+1010]) printf("%02d:%02d %02d:%02d\n",a[i].l/60,a[i].l%60,(a[i].l+a[i].len)/60,(a[i].l+a[i].len)%60);
                else printf("%02d:%02d %02d:%02d\n",(a[i].r-a[i].len)/60,(a[i].r-a[i].len)%60,a[i].r/60,a[i].r%60);
            }
        }
        else puts("NO");
    }
}
