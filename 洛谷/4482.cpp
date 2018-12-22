#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN=200100<<1;

int n,q;
char str[MAXN];

namespace solve{int ans[MAXN];}

namespace SAM{
    int son[MAXN][26],mx[MAXN],par[MAXN],nd[MAXN],rht[MAXN];
    int rt=1,lst=1,cnt=1;
    void insert(int x,int pos)
    {
        int p=lst,np=++cnt;
        mx[np]=mx[p]+1;
        rht[np]=pos;
        nd[pos]=np;
        while(p&&!son[p][x]) son[p][x]=np,p=par[p];
        if(!p) par[np]=rt;
        else
        {
            int q=son[p][x];
            if(mx[q]==mx[p]+1) par[np]=q;
            else
            {
                int nq=++cnt;
                mx[nq]=mx[p]+1;
                par[nq]=par[q];
                par[q]=par[np]=nq;
                memcpy(son[nq],son[q],sizeof son[q]);
                while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
            }
        }
        lst=np;
    }
}

namespace President_Tree{
    struct node{
        int l,r,v;
    }t[MAXN<<8];
    int cnt;
    void insert(int &x,int l,int r,int pos,int _x)
    {
        x=++cnt;
        t[x]=t[_x];
        t[x].v++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) insert(t[x].l,l,mid,pos,t[_x].l);
        else insert(t[x].r,mid+1,r,pos,t[_x].r);
    }
    int query(int x,int l,int r,int ql,int qr,int _x) // query max in [ql,qr]
    {
        if(t[x].v==t[_x].v) return 0;
        if(ql<=l&&r<=qr)
        {
            if(l==r) return l;
            int mid=(l+r)>>1;
            int ret=0;
            ret=query(t[x].r,mid+1,r,ql,qr,t[_x].r);
            if(!ret) ret=query(t[x].l,l,mid,ql,qr,t[_x].l);
            return ret;
        }
        int mid=(l+r)>>1,ret=0;
        if(qr>mid) ret=query(t[x].r,mid+1,r,ql,qr,t[_x].r);
        if(!ret&&ql<=mid) ret=query(t[x].l,l,mid,ql,qr,t[_x].l);
        return ret;
    }
}

namespace Segment_Tree{
    struct node{
        int mx,id,pos,head;
    }t[MAXN<<3];
    int nxt[MAXN],mx[MAXN];
    inline void pushup(const int &x)
    {
        if(t[x<<1].mx>t[x<<1|1].mx) t[x].mx=t[x<<1].mx,t[x].id=t[x<<1].id,t[x].pos=t[x<<1].pos;
        else t[x].mx=t[x<<1|1].mx,t[x].id=t[x<<1|1].id,t[x].pos=t[x<<1|1].pos;
    }
    void insert(int x,int l,int r,int pos,int val,int _id)
    {
        if(l==r)
        {
            nxt[_id]=t[x].head;
            t[x].head=_id;
            mx[_id]=val;t[x].mx=val;
            t[x].id=_id;
            t[x].pos=l;
            return;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) insert(x<<1,l,mid,pos,val,_id);
        else insert(x<<1|1,mid+1,r,pos,val,_id);
        pushup(x);
    }
    void clear(int x,int l,int r,int pos)
    {
        if(l==r)
        {
            t[x].head=nxt[t[x].head];
            t[x].mx=mx[t[x].head];
            t[x].id=t[x].head;
            return;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) clear(x<<1,l,mid,pos);
        else clear(x<<1|1,mid+1,r,pos);
        pushup(x);
    }
    node query(int x,int l,int r,int ql,int qr)
    {
        if(ql<=l&&r<=qr) return t[x];
        int mid=(l+r)>>1;
        if(qr<=mid) return query(x<<1,l,mid,ql,qr);
        if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
        node L=query(x<<1,l,mid,ql,qr),R=query(x<<1|1,mid+1,r,ql,qr);
        return L.mx>R.mx?L:R;
    }
}

namespace Tree{
    struct node{
        int v,nxt;
    }Edge[MAXN<<1];
    int head[MAXN],cnt_e,siz[MAXN],son[MAXN],fa[MAXN],top[MAXN],cnt,rt[MAXN];
    int pos[MAXN],rev[MAXN];
    inline void add(int u,int v)
    {
        Edge[++cnt_e].v=v;Edge[cnt_e].nxt=head[u];head[u]=cnt_e;
    }
    void dfs1(int x,int father)
    {
        siz[x]=1;fa[x]=father;
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
        pos[x]=++cnt;
        rev[cnt]=x;top[x]=tp;
        if(son[x]) dfs2(son[x],tp);
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(v==fa[x]||v==son[x]) continue;
            dfs2(v,v);
        }
    }
    void build()
    {
        for(int i=2;i<=SAM::cnt;i++) 
            add(SAM::par[i],i),add(i,SAM::par[i]);
        dfs1(1,0);dfs2(1,1);
        for(int i=1;i<=SAM::cnt;i++)
            if(SAM::rht[rev[i]]) President_Tree::insert(rt[i],1,n,SAM::rht[rev[i]],rt[i-1]);
            else rt[i]=rt[i-1];
    }
    int query1(int x,int l,int r)
    {
        if(l==r) return 0;
        int ret=0;
        while(x)
        {
            if(x==1) break;
            ret=max(ret,President_Tree::query(rt[pos[x]+siz[x]-1],1,n,l,min(r-1,l+SAM::mx[x]-1),rt[pos[x]-1]));
            x=fa[top[x]];
        }
        ret=ret-l+1;
        ret=max(ret,0);
        return ret;
    }
    void query2(int x,int w)
    {
        while(x)
        {
            Segment_Tree::node t=Segment_Tree::query(1,1,SAM::cnt,pos[x],pos[x]+siz[x]-1);
            while(t.mx>=w-SAM::mx[x]+1)
            {
                solve::ans[t.id]=max(w-t.mx+1,solve::ans[t.id]);
                Segment_Tree::clear(1,1,SAM::cnt,t.pos);
                t=Segment_Tree::query(1,1,SAM::cnt,pos[x],pos[x]+siz[x]-1);
            }
            x=fa[top[x]];
        }
    }
}

namespace solve{
    struct Query{
        int l,r,id;
        inline bool operator < (const Query &rhs) const{return r<rhs.r||(r==rhs.r&&l>rhs.l);}
    }Q[MAXN>>1];
    void solve()
    {
        for(int i=1;i<=n;i++) SAM::insert(str[i]-'a',i);
        Tree::build();
        for(int i=1;i<=q;i++) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
        sort(Q+1,Q+1+q);
        int w=1;
        for(int i=1;i<=n;i++)
        {
            while(w<=q&&Q[w].r==i)
            {
                ans[Q[w].id]=Tree::query1(SAM::nd[i],Q[w].l,Q[w].r);
                w++;
            }
        }
        w=q;
        for(int i=n;i>=1;i--)
        {
            Tree::query2(SAM::nd[i],i);
            while(w&&Q[w].r==i)
            {
                Segment_Tree::insert(1,1,SAM::cnt,Tree::pos[SAM::nd[i]],Q[w].l,Q[w].id);
                w--;
            }
        }
        for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    }
}

int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);scanf("%d",&q);
    solve::solve();
}
