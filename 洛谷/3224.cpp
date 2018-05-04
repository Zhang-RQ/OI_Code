#include<cstdio>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
const int MAXN=1E5+5;
typedef tree<int,int,less<int>,rb_tree_tag,tree_order_statistics_node_update> pbds_set;
int val[MAXN],n,m,q,fa[MAXN],siz[MAXN],u,v;char opt[10];
pbds_set t[MAXN];
int find(int x)  {return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y)
{
    x=find(x);y=find(y);
    if(siz[x]>siz[y]) swap(x,y);
    fa[x]=y;siz[y]+=siz[x];
    for(pbds_set::iterator it=t[x].begin();it!=t[x].end();++it) t[y].insert(*it);
    t[x].clear();
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]),fa[i]=i,siz[i]=1,t[i].insert(make_pair(val[i],i));
    for(int i=1;i<=m;i++) scanf("%d%d",&u,&v),merge(u,v);
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%s%d%d",opt+1,&u,&v);
        if(opt[1]=='B') merge(u,v);
        else
        {
            u=find(u);
            printf("%d\n",siz[u]<v?-1:t[u].find_by_order(v-1)->second);
        }
    }
}
