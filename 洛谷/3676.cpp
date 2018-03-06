%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=2E5+5;
const int MAXM=4E5+5;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline char readChar()
{
  static char buf[10000000],*p=buf,*end=buf;
  if(p==end) end=buf+fread(p=buf,sizeof(char),10000000,stdin);
  return *(p++);
}

inline int readInt()
{
  int ans=0,c,f=1;
  while (!isdigit(c=readChar())) if(c=='-') f*=-1;
  do ans=ans*10+c-'0';
  while (isdigit(c=readChar()));
  return ans*f;
}
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int arr[MAXN];
namespace SegmentTree{  //区间和(t) 区间平方和(ta) 区间加  维护子树和
    ll t[MAXN<<2],ta[MAXN<<2];
    int tag[MAXN<<2];  //tag表示这个点已被操作
    void pushup(int x)
    {
        t[x]=t[x<<1]+t[x<<1|1];
        ta[x]=ta[x<<1]+ta[x<<1|1];
    }
    void pushdown(int x,int l,int r)
    {
        if(tag[x])
        {
            int mid=(l+r)>>1;
            ta[x<<1]+=2ll*t[x<<1]*tag[x]+1ll*(mid-l+1)*tag[x]*tag[x];
            t[x<<1]+=1ll*tag[x]*(mid-l+1);
            ta[x<<1|1]+=2ll*t[x<<1|1]*tag[x]+1ll*(r-mid)*tag[x]*tag[x];
            t[x<<1|1]+=1ll*tag[x]*(r-mid);
            tag[x<<1]+=tag[x];tag[x<<1|1]+=tag[x];
            tag[x]=0;
        }
    }
    void build(int x,int l,int r)
    {
        if(l==r) {t[x]=arr[l];ta[x]=arr[l]*arr[l];return;}
        int mid=(l+r)>>1;
        build(x<<1,l,mid);build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void change(int x,int l,int r,int cl,int cr,int val)
    {
        if(cr<l||cl>r) return;
        if(cl<=l&&r<=cr) {tag[x]+=val;ta[x]+=2ll*t[x]*val+(r-l+1)*val*val;t[x]+=val*(r-l+1);return;}
        int mid=(l+r)>>1;pushdown(x,l,r);
        if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
        if(cr>mid) change(x<<1|1,mid+1,r,cl,cr,val);
        pushup(x);
    }
    ll asksum(int x,int l,int r,int ql,int qr)
    {
        if(qr<l||ql>r) return 0;
        if(ql<=l&&r<=qr) return t[x];
        int mid=(l+r)>>1;ll ret=0;pushdown(x,l,r);
        if(ql<=mid) ret+=asksum(x<<1,l,mid,ql,qr);
        if(qr>mid) ret+=asksum(x<<1|1,mid+1,r,ql,qr);
        return ret;
    }
    ll askssum(int x,int l,int r,int ql,int qr)
    {
        if(qr<l||ql>r) return 0;
        if(ql<=l&&r<=qr) return ta[x];
        int mid=(l+r)>>1;ll ret=0;pushdown(x,l,r);
        if(ql<=mid) ret+=askssum(x<<1,l,mid,ql,qr);
        if(qr>mid) ret+=askssum(x<<1|1,mid+1,r,ql,qr);
        return ret;
    }
}
int top[MAXN],siz[MAXN],son[MAXN],fa[MAXN],cnt,val[MAXN],dep[MAXN],sum[MAXN],pos[MAXN];
int n,q,tot,u,v,opt,x,va;
void dp(int x,int fa)
{
    sum[x]=val[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dp(v,x);
        sum[x]+=sum[v];
    }
}
void dfs1(int x)
{
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]) continue;
        fa[v]=x;dep[v]=dep[x]+1;
        dfs1(v);
        siz[x]+=siz[v];
        if(!son[x]||siz[v]>siz[son[x]]) son[x]=v;
    }
}
void dfs2(int x,int tp)
{
    arr[pos[x]=++cnt]=sum[x];top[x]=tp;
    if(son[x]) dfs2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]||v==son[x]) continue;
        dfs2(v,v);
    }
}
void edit(int x,int _val)
{
    _val=_val-val[x];
    tot+=_val;val[x]+=_val;
    while(x)
    {
        SegmentTree::change(1,1,n,pos[top[x]],pos[x],_val);
        x=fa[top[x]];
    }
}
ll ask(int x)
{
    ll ret1=SegmentTree::askssum(1,1,n,1,n)+1ll*(dep[x]+1)*tot*tot;
    while(x)
    {
        ret1-=2ll*tot*SegmentTree::asksum(1,1,n,pos[top[x]],pos[x]);
        x=fa[top[x]];
    }
    return ret1;
}
int main()
{
    n=readInt();q=readInt();
    for(int i=1;i<n;i++)
        u=readInt(),v=readInt(),add(u,v),add(v,u);
    for(int i=1;i<=n;i++)
        val[i]=readInt(),tot+=val[i];
    dep[1]=1;fa[1]=0;
    dfs1(1);dp(1,0);dfs2(1,1);
    SegmentTree::build(1,1,n);
    for(int i=1;i<=q;i++)
    {
         opt=readInt();
         if(opt==1) x=readInt(),va=readInt(),edit(x,va);
         else x=readInt(),printf("%lld\n",ask(x));
    }
}
