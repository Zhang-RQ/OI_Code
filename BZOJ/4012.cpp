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
const int MAXN=1.5E5+10;
const int MAXM=3E5+5;
struct node{
    int nxt,v,w;
}Edge[MAXM];
struct nde{
    int v,id;
    bool operator < (const nde &rhs) const{return v<rhs.v;}
}x[MAXN];
int head[MAXN],cnt_e,pos[MAXN],siz[MAXN],top[MAXN],son[MAXN],fa[MAXN],cnt,n,q,u,v,w,dep[MAXN];
int xx[MAXN],rt[MAXN],a,b,A;
ll lstans,sumE[MAXN],sum[MAXN];
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].w=w;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
namespace President_tree{
    struct node{
        int ls,rs,tims;
        ll sum;
    }t[MAXN<<6];
    int cnt;
    void insert(int &x,int l,int r,int cl,int cr,int _x)
    {
        x=++cnt;t[x]=t[_x];
        if(cl==l&&r==cr) {t[x].tims++;return;}
        t[x].sum+=sumE[cr]-sumE[cl-1];
        int mid=(l+r)>>1;
        if(cl<=mid) insert(t[x].ls,l,mid,cl,min(mid,cr),t[_x].ls);
        if(cr>mid)  insert(t[x].rs,mid+1,r,max(mid+1,cl),cr,t[_x].rs);
    }
    ll query(int x,int l,int r,int ql,int qr)
    {
        ll ret=(sumE[qr]-sumE[ql-1])*t[x].tims;
        if(ql==l&&r==qr) return ret+t[x].sum;
        int mid=(l+r)>>1;
        if(ql<=mid) ret+=query(t[x].ls,l,mid,ql,min(mid,qr));
        if(qr>mid)  ret+=query(t[x].rs,mid+1,r,max(mid+1,ql),qr);
        return ret;
    }
}
void dfs1(int x,int father)
{
    fa[x]=father;siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]) continue;
        dep[v]=dep[x]+Edge[i].w;
        dfs1(v,x);
        siz[x]+=siz[v];
        if(siz[v]>siz[son[x]]) son[x]=v;
    }
}
void dfs2(int x,int tp,int fv)
{
    top[x]=tp;pos[x]=++cnt;
    sumE[pos[x]]=fv;
    for(int i=head[x];i;i=Edge[i].nxt) if(Edge[i].v==son[x]) dfs2(Edge[i].v,tp,Edge[i].w);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]) continue;
        if(v!=son[x]) dfs2(v,v,Edge[i].w);
    }
}
ll query(int u,int l,int r)
{
    ll ret=0;
    while(u)
    {
        ret+=President_tree::query(rt[r],1,n,pos[top[u]],pos[u])-President_tree::query(rt[l-1],1,n,pos[top[u]],pos[u]);
        u=fa[top[u]];
    }
    return ret;
}
int main()
{
    scanf("%d%d%d",&n,&q,&A);
    for(int i=1;i<=n;i++) scanf("%d",&x[i].v),xx[i]=x[i].v,x[i].id=i;
    sort(xx+1,xx+1+n);
    for(int i=1;i<=n;i++) x[i].v=lower_bound(xx+1,xx+1+n,x[i].v)-xx;
    for(int i=1;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
    dfs1(1,0);dfs2(1,1,0);
    for(int i=1;i<=n;i++) sumE[i]+=sumE[i-1];
    sort(x+1,x+1+n);
    for(int i=1;i<=n;i++)
    {
        int x=::x[i].id;
        sum[i]=sum[i-1]+dep[x];
        rt[i]=rt[i-1];
        while(x)  President_tree::insert(rt[i],1,n,pos[top[x]],pos[x],rt[i]),x=fa[top[x]];
    }
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d%d",&u,&a,&b);
        int L=(a+lstans)%A,R=(b+lstans)%A;
        if(L>R) swap(L,R);
        L=lower_bound(xx+1,xx+1+n,L)-xx;
        R=upper_bound(xx+1,xx+1+n,R)-xx-1;
        // printf("Q=%lld\n",query(u,L,R));
        lstans=(sum[R]-sum[L-1])+1ll*(R-L+1)*dep[u]-2ll*query(u,L,R);
        printf("%lld\n",lstans);
    }
}
