#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN=3E5+10;

struct __edge{
    int v,nxt;
}Edge[MAXN<<1];

ll t[MAXN<<3],tag[MAXN<<3],val[MAXN];
int head[MAXN],cnt_e,siz[MAXN],pos[MAXN],dft,rt,rev[MAXN],n,q,jmp[MAXN][21],dep[MAXN];

inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
    Edge[++cnt_e].v=u;
    Edge[cnt_e].nxt=head[v];
    head[v]=cnt_e;
}

void pushdown(int x,int l,int r)
{
    if(tag[x])
    {
        int mid=(l+r)>>1;
        t[x<<1]+=1ll*tag[x]*(mid-l+1);
        t[x<<1|1]+=1ll*tag[x]*(r-mid);
        tag[x<<1]+=tag[x];
        tag[x<<1|1]+=tag[x];
        tag[x]=0;
    }
}

void build(int x,int l,int r)
{
    if(l==r) return t[x]=val[rev[l]],void();
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    t[x]=t[x<<1]+t[x<<1|1];    
}

void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&r<=cr) return t[x]+=1ll*val*(r-l+1),tag[x]+=val,void();
    int mid=(l+r)>>1;pushdown(x,l,r);
    if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
    if(cr>mid) change(x<<1|1,mid+1,r,cl,cr,val);
    t[x]=t[x<<1]+t[x<<1|1];
}

ll query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return t[x];
    int mid=(l+r)>>1;ll ret=0;pushdown(x,l,r);
    if(ql<=mid) ret+=query(x<<1,l,mid,ql,qr);
    if(qr>mid)  ret+=query(x<<1|1,mid+1,r,ql,qr);
    return ret;
}

void dfs(int x,int fa)
{
    pos[x]=++dft;siz[x]=1;
    jmp[x][0]=fa;dep[x]=dep[fa]+1;
    rev[dft]=x;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(Edge[i].v!=fa)
            dfs(Edge[i].v,x),siz[x]+=siz[Edge[i].v];
}

void init()
{
    for(int j=1;j<=20;j++)
        for(int i=1;i<=n;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
}

inline int __lca(int x,int y)
{
    if(dep[x]>dep[y]) swap(x,y);
    for(int i=20;~i;i--)
        if(dep[jmp[y][i]]>=dep[x])
            y=jmp[y][i];
    if(x==y) return x;
    for(int i=20;~i;i--)
        if(jmp[x][i]!=jmp[y][i])
            x=jmp[x][i],y=jmp[y][i];
    return jmp[x][0];
}

inline pair<int,int> __lca_p(int x,int y)
{
    bool flag=0;
    if(dep[x]>dep[y]) swap(x,y),flag=1;
    for(int i=20;~i;i--)
        if(dep[jmp[y][i]]>=dep[x])
            y=jmp[y][i];
    if(x==y) return make_pair(x,x);
    for(int i=20;~i;i--)
        if(jmp[x][i]!=jmp[y][i])
            x=jmp[x][i],y=jmp[y][i];
    if(flag) swap(x,y);
    return make_pair(x,y);
}

inline int fa_son(int x,int fa)
{
    for(int i=20;~i;i--)
        if(dep[jmp[x][i]]>dep[fa])
            x=jmp[x][i];
    return x;
}

inline bool inside(int x,int y){return pos[x]<=pos[y]&&pos[y]<=pos[x]+siz[x]-1;}// y in x 

inline void makeroot(int x){rt=x;}

inline int lca(int x,int y,bool flag)
{
    int a=__lca(rt,x),b=__lca(rt,y);
    if(a==b) return __lca(x,y);
    else return dep[a]>dep[b]?a:b;
}

inline void st_plus(int x,int val)
{
    if(x==rt) change(1,1,n,1,n,val);
    else if(inside(x,rt))
    {
        int t=fa_son(rt,x);
        change(1,1,n,1,n,val);change(1,1,n,pos[t],pos[t]+siz[t]-1,-val);
    }
    else change(1,1,n,pos[x],pos[x]+siz[x]-1,val);
}

inline ll st_query(int x)
{
    if(x==rt) return query(1,1,n,1,n);
    else if(inside(x,rt)) 
    {
        int t=fa_son(rt,x);
        return query(1,1,n,1,n)-query(1,1,n,pos[t],pos[t]+siz[t]-1);
    }
    else return query(1,1,n,pos[x],pos[x]+siz[x]-1);
}

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) cin>>val[i];
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v);
    dfs(1,0);rt=1;init();
    build(1,1,n);
    for(int i=1,op,x,y,z;i<=q;i++)
    {
        scanf("%d",&op);
        if(op==1) scanf("%d",&x),makeroot(x);
        else if(op==2) scanf("%d%d%d",&x,&y,&z),st_plus(lca(x,y,0),z);
        else if(op==3) scanf("%d",&x),cout<<st_query(x)<<endl;
    }
}
