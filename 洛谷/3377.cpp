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

const int MAXN=100010;

struct node{
    int l,r,d;
    pair<int,int> v;
}t[MAXN];

bool del[MAXN];
int fa[MAXN],rt[MAXN],n,m,cnt;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

int merge(int x,int y)
{
    if(!x||!y) return x|y;
    if(t[x].v>t[y].v) swap(x,y);
    t[x].r=merge(t[x].r,y);
    if(t[t[x].l].d<t[t[x].r].d) swap(t[x].l,t[x].r);
    t[x].d=t[t[x].r].d+1;
    return x;
}

inline void pop(int x) {printf("%d\n",t[rt[x]].v.first);del[t[rt[x]].v.second]=1;rt[x]=merge(t[rt[x]].l,t[rt[x]].r);}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        rt[i]=++cnt;
        t[cnt].v=make_pair(x,i);
        fa[i]=i;
    }
    for(int i=1,op,x,y;i<=m;i++)
    {
        scanf("%d%d",&op,&x);
        if(op==1)
        {
            scanf("%d",&y);
            if(del[x]||del[y]) continue;
            x=find(x);y=find(y);
            if(x==y) continue;
            fa[x]=y;
            rt[y]=merge(rt[x],rt[y]);
        }
        else
        {
            if(del[x]) {puts("-1");continue;}
            pop(find(x));
        }
    }
    #ifdef LOCAL
        system("pause");
    #endif
}