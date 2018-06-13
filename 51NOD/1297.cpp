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
int head[MAXN],cnt_e,n;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
namespace Tree{
    int son[MAXN][2],st[MAXN<<1][21],lca[MAXN<<1][21],lg2[MAXN<<1],cnt,dep[MAXN],pos[MAXN];
    set<pair<int,int> > s;
    set<pair<int,int> >::iterator it1,it2;
    void build(int n)
    {
        int x;scanf("%d",&x);
        s.insert(make_pair(x,1));
        for(int i=2;i<=n;i++)
        {
            scanf("%d",&x);
            it1=it2=s.insert(make_pair(x,i)).first;
            if(it1!=s.begin())
                if(!son[(--it1)->second][1]) 
                    {son[it1->second][1]=i,add(it1->second,i),add(i,it1->second);continue;}
            if((++it2)!=s.end())
                if(!son[it2->second][0])
                    {son[it2->second][0]=i;add(it2->second,i),add(i,it2->second);continue;}
        }
    }
    void dfs(int x,int fa)
    {
        lca[pos[x]=++cnt][0]=x;
        st[cnt][0]=dep[x];
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(v==fa) continue;
            dep[v]=dep[x]+1;dfs(v,x);
            lca[++cnt][0]=x;
            st[cnt][0]=dep[x];
        }
    }
    void init()
    {
        dfs(1,0);
        for(int i=2;i<=cnt;i++) lg2[i]=lg2[i>>1]+1;
        for(int j=1;j<=lg2[cnt];j++)
            for(int i=1;i+(1<<j)-1<=cnt;i++)
                if(st[i][j-1]<st[i+(1<<(j-1))][j-1])
                    st[i][j]=st[i][j-1],lca[i][j]=lca[i][j-1];
                else st[i][j]=st[i+(1<<(j-1))][j-1],lca[i][j]=lca[i+(1<<(j-1))][j-1];
    }
    int dis(int x,int y)
    {
        int px=pos[x],py=pos[y];
        if(px>py) swap(px,py);
        int len=lg2[py-px+1];
        int _lca=st[px][len]<st[py-(1<<len)+1][len]?lca[px][len]:lca[py-(1<<len)+1][len];
        return dep[x]+dep[y]-2*dep[_lca];
    }
}
namespace Divide_Conquer{
    ll sum[MAXN][2],ans;
    int fa[MAXN],siz[MAXN],mx_G,G;
    int mx_dep[MAXN],_siz[MAXN];
    bool vis[MAXN];
    void get_G(int x,int fa,int sz)
    {
        siz[x]=1;int mx=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(vis[v]||v==fa) continue;
            get_G(v,x,sz);
            siz[x]+=siz[v];
            mx=max(mx,siz[v]);
        }
        mx=max(mx,sz-siz[x]);
        if(mx<mx_G) mx_G=mx,G=x;
    }
    void dfs(int x,int fa,int dep,int t_rt)
    {
        mx_dep[t_rt]=max(mx_dep[t_rt],dep);
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(vis[v]||v==fa) continue;
            dfs(v,x,dep+1,t_rt);
        }
    }
    void solve(int x)
    {
        vis[x]=1;mx_dep[x]=1;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(vis[v]) continue;
            dfs(v,x,1,x);
        }
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(vis[v]) continue;
            mx_G=1<<30;
            get_G(v,x,siz[v]);
            fa[G]=x;solve(G);
        }
    }
    void change(int x)
    {
        int x0=x;
        for(int _dis=0,lstsiz=0;x;x=fa[x])
        {
            _dis=Tree::dis(x0,x);ans+=sum[x][0]-sum[x][1]+1ll*_dis*(_siz[x]-lstsiz);
            lstsiz+=_siz[x]-lstsiz;
            _siz[x]++;
            sum[x][0]+=_dis;
            if(fa[x]) _dis=Tree::dis(x0,fa[x]),sum[x][1]+=_dis;
        }
    }
}
int main()
{
    
    scanf("%d",&n);
    Tree::build(n);Tree::init();
    Divide_Conquer::mx_G=1<<30;
    Divide_Conquer::get_G(1,0,n);
    Divide_Conquer::solve(Divide_Conquer::G);
    for(int i=1;i<=n;i++) Divide_Conquer::change(i),printf("%lld\n",Divide_Conquer::ans);
    #ifdef LOCAL
        system("pause");
    #endif
}