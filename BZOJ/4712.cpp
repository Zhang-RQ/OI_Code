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
const int MAXN=200010;
const int MAXM=4E5+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,siz[MAXN],son[MAXN],top[MAXN],dfn[MAXN],dep[MAXN],fa[MAXN],cnt,n;
int tt[MAXN],u,v,x,y,tot,val[MAXN],m,du[MAXN],bot[MAXN];
char opt[10];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
struct data{
    ll a[2];
    data(){a[0]=a[1]=233333;}
    data(ll _,ll __) {a[0]=_;a[1]=__;}
    inline ll& operator [] (int i) {return a[i];}
    inline data operator * (const data &rhs) const
    {
        data ret;
        ret[0]=a[0]+rhs.a[0];
        ret[1]=min(a[1]+rhs.a[0],rhs.a[1]);
        return ret;
    }
}t[MAXN<<2],arr[MAXN];
inline void pushup(const int &x){t[x]=t[x<<1|1]*t[x<<1];}
void build(int x,int l,int r,int bl,int br)
{
    if(l==r) {t[x]=arr[l];return;}
    int mid=(l+r)>>1;
    if(bl<=mid) build(x<<1,l,mid,bl,br);
    if(br>mid)  build(x<<1|1,mid+1,r,bl,br);
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
void dfs_1(int x,int father)
{
    fa[x]=father;dep[x]=dep[fa[x]]+1;
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) continue;
        dfs_1(v,x);
        siz[x]+=siz[v];
        if(siz[v]>siz[son[x]]) son[x]=v;
    }
}
void dfs_2(int x,int tp)
{
    top[x]=tp;dfn[x]=++cnt;
    arr[cnt][1]=val[x];arr[cnt][0]=0;
    if(son[x]) dfs_2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]||v==son[x]) continue;
        dfs_2(v,v);
    }
}
ll ask(int x)
{
    data t=query(1,1,n,dfn[x],dfn[bot[top[x]]]);
    // cout<<"Q:"<<t[0]<<" "<<t[1]<<endl;
    return min(t[0]+val[bot[top[x]]],t[1]);
}
void edit(int x,ll val)
{
    int _x=x;
    ll _val=val;
    while(_x)
    {
        data t=arr[dfn[_x]],tmp=query(1,1,n,dfn[top[_x]],dfn[bot[top[_x]]]);
        int __f=min(tmp[0]+::val[bot[top[_x]]],tmp[1]);
        if(_x==x) t[1]+=val;
        else t[0]+=val;
        arr[dfn[_x]]=t;
        change(1,1,n,dfn[_x],t);
        data Q=query(1,1,n,dfn[top[_x]],dfn[bot[top[_x]]]);
        int _f=min(Q[0]+::val[bot[top[_x]]]+(bot[top[_x]]==x?_val:0),Q[1]);
        if(__f==_f) break;
        else val=_f-__f,_x=fa[top[_x]];
    }
    ::val[x]+=_val;
}
bool cmp(int a,int b)
{
    return dep[top[a]]>dep[top[b]];
}
signed main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
        du[u]++;du[v]++;
    }
    dfs_1(1,0);dfs_2(1,1);
    for(int i=1;i<=n;i++) tot+=(top[i]==i);
    for(int i=1;i<=n;i++) if(dep[i]>dep[bot[top[i]]]) bot[top[i]]=i,tt[top[i]]=i;
    sort(tt+1,tt+1+n,[](int a,int b)->bool{return dep[top[a]]>dep[top[b]];});
    for(int i=1;i<=tot;i++)
    {
        int x=tt[i],tp=top[x];
        build(1,1,n,dfn[tp],dfn[x]);
        data Q=query(1,1,n,dfn[tp],dfn[x]);
        arr[dfn[fa[tp]]][0]+=min(Q[0]+val[x],Q[1]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",opt+1);
        if(opt[1]=='Q') scanf("%d",&x),printf("%lld\n",ask(x));
        else scanf("%d%d",&x,&y),edit(x,y);
    }
}
