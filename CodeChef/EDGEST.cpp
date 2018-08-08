#include<bits/stdc++.h>

using namespace std;

const int MAXN=5E5+10;

struct __edge{
    int u,v,nxt;
};

char B[1<<27],*S=B;
int F()
{
    for(;*S<'-';S++);
    int x=*S++-'0';
    for(;*S>='0';x=(x<<3)+(x<<1)+*S++-'0');
    return x;
}

struct __node{
    int l,r,v;
}t[MAXN<<7];

int n,cnt,pos1[MAXN],pos2[MAXN],rt[MAXN],dft,n2,ans[MAXN];

struct Tree{
    __edge Edge[MAXN<<1];
    int head[MAXN],cnt_e,dep[MAXN],jmp[MAXN][19];
    inline void clear(){memset(head,0,sizeof head);cnt_e=0;}
    inline void add(int u,int v)
    {
        Edge[++cnt_e].u=u;
        Edge[cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
        
        Edge[++cnt_e].v=u;
        Edge[cnt_e].u=v;
        Edge[cnt_e].nxt=head[v];
        head[v]=cnt_e;
    }
    void dfs(int x,int fa)
    {
        jmp[x][0]=fa;dep[x]=dep[fa]+1;
        for(int i=head[x];i;i=Edge[i].nxt)
            if(Edge[i].v!=fa)
                dfs(Edge[i].v,x);
    }
    void init()
    {
        for(int j=1;j<=18;j++)
            for(int i=1;i<=n;i++)
                jmp[i][j]=jmp[jmp[i][j-1]][j-1];
    }
    int lca(int x,int y)
    {
        if(dep[x]>dep[y]) swap(x,y);
        for(int i=18;~i;i--)
            if(dep[jmp[y][i]]>=dep[x])
                y=jmp[y][i];
        if(x==y) return x;
        for(int i=18;~i;i--)
            if(jmp[x][i]!=jmp[y][i])
                x=jmp[x][i],y=jmp[y][i];
        return jmp[x][0];
    }
}T1,T2;

void change(int &x,int l,int r,int pos,int val)
{
    if(!x) x=++cnt,t[x].l=t[x].r=t[x].v=0;
    if(l==r) return t[x].v+=val,void();
    int mid=(l+r)>>1;
    if(pos<=mid) change(t[x].l,l,mid,pos,val);
    if(pos>mid)  change(t[x].r,mid+1,r,pos,val);
    t[x].v=t[t[x].l].v+t[t[x].r].v;
}

int query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return t[x].v;
    int mid=(l+r)>>1,ret=0;
    if(ql<=mid) ret+=query(t[x].l,l,mid,ql,qr);
    if(qr>mid)  ret+=query(t[x].r,mid+1,r,ql,qr);
    return ret;
}

int merge(const int x,const int y)
{
    if(!x||!y) return x|y;
    t[x].l=merge(t[x].l,t[y].l);
    t[x].r=merge(t[x].r,t[y].r);
    t[x].v+=t[y].v;
    return x;
}

void dfs1(int x,int fa)
{
    for(int i=T1.head[x];i;i=T1.Edge[i].nxt)
        if(T1.Edge[i].v!=fa)
            dfs1(T1.Edge[i].v,x),rt[x]=merge(rt[x],rt[T1.Edge[i].v]);
    if(fa!=0)
    {
        int LCA=T2.lca(x,fa);
        ans[x]=query(rt[x],1,n2,1,pos1[x])+query(rt[x],1,n2,1,pos1[fa])-2*query(rt[x],1,n2,1,pos1[LCA]);
    }
}

void dfs2(int x,int fa)
{
    pos1[x]=++dft;
    for(int i=T2.head[x];i;i=T2.Edge[i].nxt)
        if(T2.Edge[i].v!=fa)
            dfs2(T2.Edge[i].v,x);
    pos2[x]=++dft;
    if(fa!=0)
    {
        int LCA=T1.lca(x,fa);
        
        change(rt[x],1,n2,pos1[x],1);
        change(rt[x],1,n2,pos2[x],-1);
        
        change(rt[fa],1,n2,pos1[x],1);
        change(rt[fa],1,n2,pos2[x],-1);
        
        change(rt[LCA],1,n2,pos1[x],-2);
        change(rt[LCA],1,n2,pos2[x],2);
    }
}

void solve()
{
    T1.clear();T2.clear();
    memset(rt,0,sizeof rt);
    dft=cnt=0;
    n=F();n2=n<<1;
    for(int i=1,u,v;i<n;i++) u=F(),v=F(),T1.add(u,v);
    for(int i=1,u,v;i<n;i++) u=F(),v=F(),T2.add(u,v);
    T1.dfs(1,0);T1.init();T2.dfs(1,0);T2.init();
    dfs2(1,0);dfs1(1,0);
    for(int i=1;i<=T1.cnt_e;i+=2)
        printf("%d ",T1.dep[T1.Edge[i].u]>T1.dep[T1.Edge[i].v]?ans[T1.Edge[i].u]:ans[T1.Edge[i].v]);
    puts("");
}

int main()
{
    fread(B,1,1<<26,stdin);
    for(int T=F();T--;solve());
}
