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
int head[MAXN],cnt_e,val[MAXN],tot,cnt,rt[MAXN]; //val 1--tot
int _val[MAXN],n,m,lstans;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
struct node{
    int ls,rs,v;
}t[MAXN<<6];
void insert(int &x,int l,int r,int pos,int _x)
{
    x=++cnt;
    t[x]=t[_x];t[x].v++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) insert(t[x].ls,l,mid,pos,t[_x].ls);
    else insert(t[x].rs,mid+1,r,pos,t[_x].rs);
}
int query(int x,int y,int z,int l,int r,int k,int _v)
{
    if(l==r)  return l;
    int mid=(l+r)>>1;
    int lsiz=t[t[x].ls].v+t[t[y].ls].v-2*t[t[z].ls].v+(l<=_v&&_v<=mid);
    if(lsiz<k) return query(t[x].rs,t[y].rs,t[z].rs,mid+1,r,k-lsiz,_v);
    else return query(t[x].ls,t[y].ls,t[z].ls,l,mid,k,_v);
}
namespace LCA{
    int lca[MAXN<<1][21],st[MAXN<<1][21],dft,pos[MAXN<<1],lg2[MAXN<<1];
    void dfs(int x,int fa,int dep)
    {
        st[pos[x]=++dft][0]=dep;
        lca[pos[x]][0]=x;
        insert(rt[x],1,tot,val[x],rt[fa]);
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(v==fa) continue;
            dfs(v,x,dep+1);
            st[++dft][0]=dep;
            lca[dft][0]=x;
        }
    }
    void init()
    {
        dfs(1,0,0);
        for(int i=2;i<=dft;i++) lg2[i]=lg2[i>>1]+1;
        for(int j=1;j<=lg2[dft];j++)
            for(int i=1;i+(1<<j)-1<=dft;i++)
                if(st[i][j-1]<st[i+(1<<(j-1))][j-1])
                    st[i][j]=st[i][j-1],lca[i][j]=lca[i][j-1];
                else 
                    st[i][j]=st[i+(1<<(j-1))][j-1],lca[i][j]=lca[i+(1<<(j-1))][j-1];
    }
    int query(int x,int y)
    {
        x=pos[x];y=pos[y];
        if(x>y) swap(x,y);
        int len=lg2[y-x+1];
        return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]),_val[i]=val[i];
    for(int i=1,u,v;i<n;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    sort(_val+1,_val+1+n);
    tot=unique(_val+1,_val+1+n)-_val-1;
    for(int i=1;i<=n;i++)  val[i]=lower_bound(_val+1,_val+1+tot,val[i])-_val;
    LCA::init();
    for(int i=1,x,y,k;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&k);
        x^=lstans;
        int _lca=LCA::query(x,y);
        printf("%d\n",lstans=_val[query(rt[x],rt[y],rt[_lca],1,tot,k,val[_lca])]);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}