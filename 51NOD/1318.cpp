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
struct equation{
    int x1,x2,tp,res;
    vector<pair<int,int>> p;
    void clear(){x1=x2=tp=0;p.clear();}
}eq[210];
const int __MAXN=2E5+5;
const int __MAXM=4E6+5;
struct __edge{
    int nxt,v;
}Edge[__MAXM];
int head[__MAXN],cnt_e;
inline void add(int u,int v)
{
    // printf("%d->%d\n",u,v);
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
set<int> pri;
int T,n,m,cnt,id[205][35][2],pw[210],dfn[__MAXN],low[__MAXN],dft,stk[__MAXN],top,SCC,bl[__MAXN];
bool ins[__MAXN];
char ty[10];
void decomposition()
{
    for(int i=1;i<=m;i++)
    {
        int o=eq[i].res,lim=sqrt(o),cnt=0;
        for(int j=2;j<=lim;j++)
            if(o%j==0)
            {
                cnt=0;while(o%j==0) ++cnt,o/=j;
                eq[i].p.push_back(make_pair(j,cnt));
                pri.insert(j);
            }
        if(o!=1) eq[i].p.push_back(make_pair(o,1)),pri.insert(o);
    }
}
int fj(int x,int p)
{
    int ret=0;
    while(x%p==0) x/=p,ret++;
    return ret;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++dft;
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
        while(stk[top]!=x)
        {
            ins[stk[top]]=0;
            bl[stk[top]]=SCC;
            top--;
        }
        top--;
        bl[x]=SCC;
        ins[x]=0;
    }
}
bool judge(int mx)
{
    SCC=0;top=0;
    dft=0;
    memset(dfn,0,sizeof dfn);
    memset(low,0,sizeof low);
    memset(bl,0,sizeof bl);
    for(int i=1;i<=cnt;i++)
        if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
        for(int j=0;j<=mx;j++)
            if(bl[id[i][j][0]]==bl[id[i][j][1]]) return false;
    return true;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        pri.clear();
        memset(head,0,sizeof head);cnt_e=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            eq[i].clear(),scanf("%s%d%d%d",ty+1,&eq[i].x1,&eq[i].x2,&eq[i].res),eq[i].x1++,eq[i].x2++,eq[i].tp=(ty[1]=='G')?1:2;
        decomposition();
        int ans=1;
        while(pri.size())
        {
            int x=*pri.begin(),mx=0;pri.erase(x);cnt=0;
            memset(head,0,sizeof head);cnt_e=0;
            for(int i=1;i<=m;i++) pw[i]=fj(eq[i].res,x),mx=max(mx,pw[i]);
            for(int i=1;i<=n;i++) for(int j=0;j<=mx;j++)
                id[i][j][0]=++cnt,id[i][j][1]=++cnt;
            for(int i=1;i<=n;i++) for(int j=0;j<=mx-1;j++) add(id[i][j][0],id[i][j+1][0]);
            for(int i=1;i<=n;i++) for(int j=1;j<=mx;j++) add(id[i][j][1],id[i][j-1][1]);
            for(int i=1;i<=m;i++)
            {
                if(eq[i].tp==1)
                {
                    for(int j=0;j<=pw[i]-1;j++)
                        add(id[eq[i].x1][j][0],id[eq[i].x1][j][1]),
                        add(id[eq[i].x2][j][0],id[eq[i].x2][j][1]);
                    for(int j=pw[i];j<=mx;j++)
                        add(id[eq[i].x1][j][1],id[eq[i].x2][pw[i]][0]),
                        add(id[eq[i].x2][j][1],id[eq[i].x1][pw[i]][0]);
                }
                else
                {
                    for(int j=pw[i];j<=mx;j++)
                        add(id[eq[i].x1][j][1],id[eq[i].x1][j][0]),
                        add(id[eq[i].x2][j][1],id[eq[i].x2][j][0]);
                    for(int j=0;j<=pw[i]-1;j++)
                        add(id[eq[i].x1][j][0],id[eq[i].x2][pw[i]-1][1]),
                        add(id[eq[i].x2][j][0],id[eq[i].x1][pw[i]-1][1]);
                }
            }
            ans&=judge(mx);
            if(!ans) break;
        }
        puts(ans?"Solution exists":"Solution does not exist");
    }
}
