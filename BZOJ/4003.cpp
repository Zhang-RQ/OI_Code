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

const int MAXN=6E5+10;

int n,m;
int Ans1[MAXN],Ans2[MAXN],dep[MAXN],c[MAXN];
int a[MAXN],rt[MAXN],cnt;
ll h[MAXN],v[MAXN];
vector<int> g[MAXN];

struct node{
    int l,r,d;
    ll tag_p,tag_m;
    pair<ll,int> v;
    node(){tag_m=1;}
}t[MAXN];

inline void pushdown(const int &x)
{
    if(!x) return;
    if(t[x].tag_m!=1)
    {
        t[t[x].l].v.first*=t[x].tag_m;
        t[t[x].l].tag_m*=t[x].tag_m;
        t[t[x].l].tag_p*=t[x].tag_m;
        t[t[x].r].v.first*=t[x].tag_m;
        t[t[x].r].tag_m*=t[x].tag_m;
        t[t[x].r].tag_p*=t[x].tag_m;
        t[x].tag_m=1;
    }
    if(t[x].tag_p!=0)
    {
        t[t[x].l].v.first+=t[x].tag_p;
        t[t[x].l].tag_p+=t[x].tag_p;
        t[t[x].r].v.first+=t[x].tag_p;
        t[t[x].r].tag_p+=t[x].tag_p;
        t[x].tag_p=0;
    }
}

inline int merge(int x,int y)
{
    if(!x||!y) return x|y;
    pushdown(x);pushdown(y);
    if(t[x].v>t[y].v) swap(x,y);
    t[x].r=merge(t[x].r,y);
    if(t[t[x].l].d<t[t[x].r].d) swap(t[x].l,t[x].r);
    t[x].d=t[t[x].r].d+1;
    return x;
}

void dfs(int x)
{
    for(int i=0;i<g[x].size();i++)
    {
        int v=g[x][i];
        dep[v]=dep[x]+1,dfs(v),rt[x]=merge(rt[x],rt[v]);
    }
    while(rt[x]&&t[rt[x]].v.first<h[x])
    {
        ++Ans1[x];
        Ans2[t[rt[x]].v.second]=x;
        pushdown(rt[x]);
        rt[x]=merge(t[rt[x]].l,t[rt[x]].r);
    }
    if(a[x]) pushdown(rt[x]),t[rt[x]].tag_m*=v[x],t[rt[x]].v.first*=v[x];
    else pushdown(rt[x]),t[rt[x]].tag_p+=v[x],t[rt[x]].v.first+=v[x];
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&h[i]);
    for(int i=2,fa;i<=n;i++)
    {
        scanf("%d%d%lld",&fa,&a[i],&v[i]);
        g[fa].push_back(i);
    }
    ll s;
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%d",&s,&c[i]);
        t[++cnt].v.first=s;
        t[cnt].v.second=i;
        rt[c[i]]=merge(rt[c[i]],cnt);
    }
    dep[1]=1;dfs(1);
    for(int i=1;i<=n;i++) printf("%d\n",Ans1[i]);
    for(int i=1;i<=m;i++) printf("%d\n",dep[c[i]]-dep[Ans2[i]]);
}