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
const int MAXN=2E5+5;
const int MAXM=4E5+5;
struct data{
    ll a[4];
    data(){a[0]=a[1]=a[2]=a[3]=0;}
    data(ll _,ll __,ll ___,ll ____) {a[0]=_;a[1]=__;a[2]=___;a[3]=____;}
    inline ll& operator[] (const int &i) {return  a[i];}
    inline data operator * (const data &rhs) const
    {
        data ret;
        ret[0]=a[0]+rhs.a[0];
        ret[1]=max(a[0]+rhs.a[1],a[1]);
        ret[2]=max(a[2]+rhs.a[0],rhs.a[2]);
        ret[3]=max(a[2]+rhs.a[1],max(a[3],rhs.a[3]));
        return ret;
    }
};
namespace Segment_tree{
    data t[MAXN<<2],a[MAXN];
    inline void pushup(const int &x) {t[x]=t[x<<1|1]*t[x<<1];}
    void build(int x,int l,int r,int bl,int br)
    {
        if(l==r) {t[x]=a[l];return;}
        int mid=(l+r)>>1;
        if(bl<=mid) build(x<<1,l,mid,bl,br);
        if(br>mid) build(x<<1|1,mid+1,r,bl,br);
        pushup(x);
    }
    void change(int x,int l,int r,int pos,data val)
    {
        if(l==r) {t[x]=val;return;}
        int mid=(l+r)>>1;
        if(pos<=mid) change(x<<1,l,mid,pos,val);
        else change(x<<1|1,mid+1,r,pos,val);
        pushup(x);
    }
    data query(int x,int l,int r,int ql,int qr)
    {
        if(ql<=l&&r<=qr) return t[x];
        int mid=(l+r)>>1;
        if(qr<=mid) return query(x<<1,l,mid,ql,qr);
        else if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
        else return query(x<<1|1,mid+1,r,ql,qr)*query(x<<1,l,mid,ql,qr);
    }
}
struct __edge{
    int nxt,v;
}Edge[MAXM];
struct heap{
    priority_queue<ll> __heap,__del;
    inline void push(ll x){__heap.push(x);}
    inline void del(ll x) {__del.push(x);}
    inline ll top()
    {
        while(__del.size()&&__del.top()==__heap.top()) __del.pop(),__heap.pop();
        if(__heap.size()) return __heap.top();
        else return -1;
    }
}hp[MAXN];
char opt[10];
ll g[MAXN];
int head[MAXN],cnt_e,cnt,val[MAXN],n,m,x,y,tot;
int siz[MAXN],son[MAXN],top[MAXN],dep[MAXN],fa[MAXN],bot[MAXN],tt[MAXN],pos[MAXN];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void dfs1(int x,int father)
{
    fa[x]=father;dep[x]=dep[fa[x]]+1;
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) continue;
        dfs1(v,x);
        siz[x]+=siz[v];
        if(siz[son[x]]<siz[v]) son[x]=v;
    }
}
void dfs2(int x,int tp)
{
    top[x]=tp;pos[x]=++cnt;
    if(son[x]) dfs2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]||v==son[x]) continue;
        dfs2(v,v);
    }
}
ll query(int x)
{
    data t=Segment_tree::query(1,1,n,pos[x],pos[bot[top[x]]]);
    return max(max(t[1],t[3]),0ll);
}
void change(int x,ll delta)
{
    int _x=x;
    while(x)
    {
        data t=Segment_tree::a[pos[x]],_t=Segment_tree::query(1,1,n,pos[top[x]],pos[bot[top[x]]]);
        if(x==_x) t[0]+=delta,t[1]+=delta;
        else t=data(val[x]+g[x],val[x]+g[x],0,hp[x].top());
        Segment_tree::a[pos[x]]=t;
        Segment_tree::change(1,1,n,pos[x],t);
        t=Segment_tree::query(1,1,n,pos[top[x]],pos[bot[top[x]]]);
        ll f=max(t[0],t[2]),s=max(t[1],t[3]),_f=max(_t[0],_t[2]),_s=max(_t[1],_t[3]);
        // if(_f==f) break;
        if(_s!=s) hp[fa[top[x]]].del(_s),hp[fa[top[x]]].push(s);
        g[fa[top[x]]]+=f-_f;x=fa[top[x]];
    }
}
bool cmp(int x,int y){return dep[x]>dep[y];}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<n;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x);
    dfs1(1,0);dfs2(1,1);
    for(int i=1;i<=n;i++) if(dep[i]>dep[bot[top[i]]]) bot[top[i]]=i;
    for(int i=1;i<=n;i++) if(top[i]==i) tt[++tot]=i;
    sort(tt+1,tt+1+tot,[](int a,int b)->bool{return dep[a]>dep[b];});
    for(int i=1;i<=tot;i++)
    {
        int x=tt[i],bt=bot[x];
        int tx=bt;
        while(tx!=fa[x]) Segment_tree::a[pos[tx]]=data(val[tx]+g[tx],val[tx]+g[tx],0,hp[tx].top()),tx=fa[tx];
        Segment_tree::build(1,1,n,pos[x],pos[bt]);
        data t=Segment_tree::query(1,1,n,pos[x],pos[bt]);
        g[fa[x]]+=max(t[0],t[2]);hp[fa[x]].push(max(t[1],t[3]));
    }
    while(m--)
    {
        scanf("%s",opt+1);
        if(opt[1]=='Q')
        {
            scanf("%d",&x);
            printf("%lld\n",query(x));
        }
        else
        {
            scanf("%d%d",&x,&y);
            y=y-val[x];val[x]+=y;
            change(x,y);
        }
    }
}
