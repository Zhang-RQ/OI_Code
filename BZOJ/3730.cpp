%:pragma GCC optimize(2)
%:pragma GCC optimize(3)

#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=500100;
const int MAXM=500100;
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
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int dep[MAXN],siz[MAXN],st[MAXN<<1][21],cnt,mx_rt,rt,pos[MAXN],srt[MAXN][2],lg2[MAXN<<1],val[MAXN],par[MAXN];
bool vis[MAXN];
int n,m;
namespace SegmentTree{
    int cnt=0,t[MAXN<<4],ls[MAXN<<4],rs[MAXN<<4];
    void insert(int &xx, int l, int r, int pos, int val)
    {
        if(!xx) xx = ++ cnt;
        int x = xx;
        while(1)
        {
            int mid=(l+r)>>1;
            t[x]+=val;
            if(l==r) break;
            if(pos<=mid)
                ls[x]=(ls[x]?ls[x]:++cnt),x=ls[x],r=mid;
            else
                rs[x]=(rs[x]?rs[x]:++cnt),x=rs[x],l=mid+1;
        }
    }
    int query(int x,int l,int r,int ql,int qr)
    {
        if(!x||(ql>r||qr<l)) return 0;
        if(ql<=l&&r<=qr) return t[x];
        int mid=(l+r)>>1,ret=0;
        if(ql<=mid) ret+=query(ls[x],l,mid,ql,qr);
        if(qr>mid) ret+=query(rs[x],mid+1,r,ql,qr);
        return ret;
    }
}
void get_root(int x,int fa,int sz)
{
    int mx=0;siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||v==fa) continue;
        get_root(v,x,sz);
        siz[x]+=siz[v];
        mx=max(siz[v],mx);
    }
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) mx_rt=mx,rt=x;
}
void dfsi(int x,int fa)
{
    st[pos[x]=++cnt][0]=dep[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(fa==v) continue;
        dep[v]=dep[x]+1;
        dfsi(v,x);
        st[++cnt][0]=dep[x];
    }
}
void init()
{
    for(int i=2;i<=cnt;i++) lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[cnt];j++)
        for(int i=1;i+(1<<j)-1<=cnt;i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int dis(int x,int y)
{
    int px=pos[x],py=pos[y];
    if(px>py) swap(px,py);
    int len=lg2[py-px+1];
    return dep[x]+dep[y]-2*min(st[px][len],st[py-(1<<len)+1][len]);
}
void dfs(int x,int fa,int _rt,int _dis,bool tp)  //srt[x][0]记录答案(到重心)  srt[x][1] 消除重复(到重心的父亲)
{
    SegmentTree::insert(srt[_rt][tp],0,n,_dis,val[x]);
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]&&Edge[i].v!=fa)
            dfs(Edge[i].v,x,_rt,_dis+1,tp);
}
void solve(int x)
{
    vis[x]=1;
    dfs(x,0,x,0,0);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        mx_rt=MAXN+10;
        get_root(v,0,siz[v]);
        dfs(v,0,rt,1,1);
        par[rt]=x;
        solve(rt);
    }
}
int query(int x,int _dis)
{
    int ret=SegmentTree::query(srt[x][0],0,n,0,_dis);
    for(int i=x;par[i];i=par[i])
    {
        int k=dis(par[i],x);
        ret+=SegmentTree::query(srt[par[i]][0],0,n,0,_dis-k);
        ret-=SegmentTree::query(srt[i][1],0,n,0,_dis-k);
    }
    return ret;
}
void edit(int x,int _val)
{
    _val=_val-val[x];val[x]+=_val;
    SegmentTree::insert(srt[x][0],0,n,0,_val);
    for(int i=x;par[i];i=par[i])
    {
        int k=dis(par[i],x);
        SegmentTree::insert(srt[par[i]][0],0,n,k,_val);
        SegmentTree::insert(srt[i][1],0,n,k,_val);
    }
}
int u,v,opt,k,x,lstans=0;
int main()
{
    n=readInt();m=readInt();
    for(int i=1;i<=n;i++) val[i]=readInt();
    for(int i=1;i<n;i++)
        u=readInt(),v=readInt(),add(u,v),add(v,u);
    dfsi(1,0);init();
    mx_rt=MAXN+10;
    get_root(1,0,n);
    solve(rt);
    for(int i=1;i<=m;i++)
    {
        opt=readInt();x=readInt();k=readInt();
        x^=lstans;k^=lstans;
        if(opt==0) printf("%d\n",lstans=query(x,k));
        else edit(x,k);
    }
}
