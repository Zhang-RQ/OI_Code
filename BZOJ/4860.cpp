// TLE
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

#define DEBUG fprintf(stderr,"Passing Line %d in function \"%s\" .\n",__LINE__,__FUNCTION__);

const int MAXN=2E5+10;

int n,m,L,R;
int val[MAXN],siz[MAXN],rt,mx_rt,ans=0xcfcfcfcf;
bool vis[MAXN];
vector<pair<int,int> > g[MAXN]; // first color,second vertex

struct Segment_tree{
    int t[MAXN<<3];bool cls[MAXN<<3];

    inline void clear(){cls[1]=1;t[1]=0xcfcfcfcf;}

    inline void pushdown(int x) {if(cls[x]){cls[x<<1]=cls[x<<1|1]=1;t[x<<1]=t[x<<1|1]=0xcfcfcfcf;cls[x]=0;}}

    void change(int x,int l,int r,int pos,int val)
    {
        if(l==r) return t[x]=max(t[x],val),void();
        int mid=(l+r)>>1;pushdown(x);
        if(pos<=mid) change(x<<1,l,mid,pos,val);
        else change(x<<1|1,mid+1,r,pos,val);
        t[x]=max(t[x<<1],t[x<<1|1]);
    }

    int query(int x,int l,int r,int ql,int qr)
    {
        if(t[x]==0xcfcfcfcf) return 0xcfcfcfcf;
        if(ql<=l&&r<=qr) return t[x];
        int mid=(l+r)>>1,ret=0xcfcfcfcf;pushdown(x);
        if(ql<=mid) ret=max(ret,query(x<<1,l,mid,ql,qr));
        if(qr>mid) ret=max(ret,query(x<<1|1,mid+1,r,ql,qr));
        return ret;
    }

}sgt[2];


void get_rt(int x,int fa,int sz)
{
    siz[x]=1;int mx=0;
    for(auto i:g[x])
    {
        int v=i.second;
        if(v==fa||vis[v]) continue;
        get_rt(v,x,sz);
        siz[x]+=siz[v];
        mx=max(mx,siz[v]);
    }
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) rt=x,mx_rt=mx;
}

void dfs_c(int x,int fa,int lstcol,int valp,int dep,int tp)
{
    if(dep>R) return;
    sgt[tp].change(1,0,R,dep,valp);
    for(auto i:g[x])
    {
        int v=i.second;
        if(v==fa||vis[v]) continue;
        dfs_c(v,x,i.first,valp+(i.first==lstcol?0:val[i.first]),dep+1,tp);
    }
}

void dfs_q(int x,int fa,int lstcol,int valp,int dep)
{
    if(dep>R) return;
    ans=max(ans,sgt[0].query(1,0,R,max(L-dep,0),R-dep)+valp);
    ans=max(ans,sgt[1].query(1,0,R,max(L-dep,0),R-dep)+valp);
    for(auto i:g[x])
    {
        int v=i.second;
        if(v==fa||vis[v]) continue;
        dfs_q(v,x,i.first,valp+(i.first==lstcol?0:val[i.first]),dep+1);
    }
}

void solve(int x)
{
    vis[x]=1;
    sort(g[x].begin(),g[x].end());
    int lst=0;sgt[0].clear();sgt[1].clear();
    sgt[0].change(1,0,n,0,0);
    for(unsigned int i=0;i<g[x].size();i++)
    {
        int v=g[x][i].second;
        if(vis[v]) continue;
        dfs_q(v,x,g[x][i].first,val[g[x][i].first],1);
        if(i+1<g[x].size()&&g[x][i+1].first==g[x][i].first) dfs_c(v,x,g[x][i].first,0,1,1);
        else
        {
            for(unsigned int j=lst;j<=i;j++)
                dfs_c(g[x][j].second,x,g[x][j].first,val[g[x][j].first],1,0);
            lst=i+1;sgt[1].clear();
        }
    }
    reverse(g[x].begin(),g[x].end());
    sgt[0].clear();sgt[1].clear();lst=0;
    sgt[0].change(1,0,n,0,0);
    for(unsigned int i=0;i<g[x].size();i++)
    {
        int v=g[x][i].second;
        if(vis[v]) continue;
        dfs_q(v,x,g[x][i].first,val[g[x][i].first],1);
        if(i+1<g[x].size()&&g[x][i+1].first==g[x][i].first) dfs_c(v,x,g[x][i].first,0,1,1);
        else
        {
            for(unsigned int j=lst;j<=i;j++)
                dfs_c(g[x][j].second,x,g[x][j].first,val[g[x][j].first],1,0);
            lst=i+1;sgt[1].clear();
        }
    }
    for(auto i:g[x])
    {
        int v=i.second;
        if(vis[v]) continue;
        mx_rt=MAXN;rt=0;
        get_rt(v,x,siz[v]);
        solve(rt);
    }
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&L,&R);
    for(int i=1;i<=m;i++) scanf("%d",&val[i]);
    for(int i=1,u,v,c;i<n;i++) scanf("%d%d%d",&u,&v,&c),g[u].push_back(make_pair(c,v)),g[v].push_back(make_pair(c,u));
    mx_rt=MAXN;
    get_rt(1,0,n);
    solve(rt);
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}