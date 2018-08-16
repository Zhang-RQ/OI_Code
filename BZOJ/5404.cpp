#include<bits/stdc++.h>

using namespace std;

const int MAXN=3E5+10;
const int MAXM=1010;

struct __edge{
    int v,nxt;
}Edge[MAXN<<1];

int n,q,top[MAXN],siz[MAXN],son[MAXN],dep[MAXN],pos[MAXN],head[MAXN],cnt_e;
int dft,rpos[MAXN],fa[MAXN],ar[10];
bitset<MAXM> t[MAXN<<2],bs[MAXN],res,tb[10],TMP,Res;

bool cmp(int a,int b){return pos[a]<pos[b];}

void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

void dfs1(int x)
{
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        dep[v]=dep[x]+1;fa[v]=x;
        dfs1(v);siz[x]+=siz[v];
        if(siz[v]>siz[son[x]]) son[x]=v;
    }
}

void dfs2(int x,int tp)
{
    top[x]=tp;
    pos[x]=++dft;rpos[pos[x]]=x;
    if(son[x]) dfs2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==son[x]) continue;
        dfs2(v,v);
    }
}

void build(int x,int l,int r)
{
    if(l==r) return t[x]=bs[rpos[l]],void();
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    t[x]=t[x<<1]|t[x<<1|1];
}

void query(int x,int l,int r,int ql,int qr)
{
    if(x==1) res.reset();
    if(ql<=l&&r<=qr) return res|=t[x],void();
    int mid=(l+r)>>1;
    if(ql<=mid) query(x<<1,l,mid,ql,qr);
    if(qr>mid) query(x<<1|1,mid+1,r,ql,qr);
}

void tquery(int x,int y) //x->y
{
    Res.reset();
    while(top[x]!=top[y])
    {
        query(1,1,n,pos[top[x]],pos[x]);
        Res|=res;
        x=fa[top[x]];
    }
    query(1,1,n,pos[y],pos[x]);
    Res|=res;
}

int LCA(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]>dep[y]?y:x;
}

int main()
{
    freopen("party.in","r",stdin);
    freopen("party.out","w",stdout);
    scanf("%d%*d%d",&n,&q);
    for(int i=2,x;i<=n;i++) scanf("%d",&x),add(x,i);
    for(int i=1,x;i<=n;i++) scanf("%d",&x),bs[i][x]=1;
    dfs1(1);dfs2(1,1);build(1,1,n);
    for(int i=1,c,Ans,cnt;i<=q;i++)
    {
        scanf("%d",&c);Ans=1<<30;
        for(int j=1;j<=c;j++) scanf("%d",&ar[j]);
        sort(ar+1,ar+1+c,cmp);
        int l=LCA(ar[1],ar[c]);
        for(int j=1;j<=c;j++) tquery(ar[j],l),tb[j]=Res;
        for(int s=1;s<(1<<c);s++)
        {
            TMP.reset();cnt=0;
            for(int j=0;j<c;j++)
                if((s>>j)&1) TMP|=tb[j+1],++cnt;
            Ans=min(Ans,(int)TMP.count()/cnt);
        }
        printf("%d\n",Ans*c);
    }
}
