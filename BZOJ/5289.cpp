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
const int MAXN=5E5+5;
const int MAXM=5E5+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];
struct dat{
    ll sum;int siz,x;
    dat(){}
    dat(ll _,int __,int ___){sum=_;siz=__;x=___;}
    inline bool operator < (const dat &rhs) const
    {
        if(sum*rhs.siz!=rhs.sum*siz) return sum*rhs.siz<rhs.sum*siz;
        else return x<rhs.x;
    }
};
multiset<dat> s;
multiset<dat>::iterator it;
int head[MAXN],cnt_e;
int a[MAXN],n,fa[MAXN],siz[MAXN],cnt;
bool vis[MAXN];
ll ans=0,w[MAXN];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void dfs(int x)
{
    vis[x]=1;++cnt;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(vis[Edge[i].v]) puts("-1"),exit(0);
        else dfs(Edge[i].v);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),add(a[i],i);
    dfs(0);
    if(cnt<=n) return puts("-1"),0;
    for(int i=1;i<=n;i++) scanf("%lld",&w[i]),siz[i]=1,fa[i]=i,s.insert(dat(w[i],1,i));
    fa[0]=0;siz[0]=1;
    while(!s.empty())
    {
        dat _x=*s.begin();s.erase(s.begin());
        int x=find(_x.x);
        if(siz[x]!=_x.siz) continue;
        int y=fa[x]=find(a[x]);
        if(y)
        {
            it=s.find(dat(w[y],siz[y],y));
            assert(it!=s.end());s.erase(it);
        }
        ans+=w[x]*siz[y];
        siz[y]+=siz[x];
        w[y]+=w[x];
        if(y) s.insert(dat(w[y],siz[y],y));
    }
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}