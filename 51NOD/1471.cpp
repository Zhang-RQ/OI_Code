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
const int MAXN=1E5+10;
int n,q,l,r,k,lstans=0,a[MAXN],opt;
namespace Splay{
    struct node{
        int son[2],siz,fa;
        void clear(){son[0]=son[1]=siz=fa=0;}
    }t[MAXN];
    #define ls(x) t[x].son[0]
    #define rs(x) t[x].son[1]
    #define fa(x) t[x].fa
    #define rson(x) (rs(fa(x))==x)
    int rt;
    inline void pushup(const int &x){t[x].siz=1+t[ls(x)].siz+t[rs(x)].siz;}
    inline void rotate(int x)
    {
        int y=fa(x),z=fa(y);
        bool rsx=rson(x),rsy=rson(y);
        if(z) t[z].son[rsy]=x;
        else rt=x;
        t[y].son[rsx]=t[x].son[!rsx];
        t[x].son[!rsx]=y;
        fa(y)=x;fa(x)=z;
        fa(t[y].son[rsx])=y;
        pushup(y);pushup(x);
    }
    inline void splay(int x)
    {
        while(fa(x))
        {
            if(fa(fa(x))) rotate(rson(x)==rson(fa(x))?fa(x):x);
            rotate(x);
        }
    }
    int kth(int x,int k)
    {
        if(t[ls(x)].siz+1==k) return x;
        if(t[ls(x)].siz+1<k)  return kth(rs(x),k-t[ls(x)].siz-1);
        return kth(ls(x),k);
    }
    inline void insert(int x,int pos)
    {
        t[x].clear();
        if(pos==0)
        {
            t[x].son[1]=rt;
            fa(rt)=x;
            pushup(x);
            rt=x;
            return;
        }
        int tx=kth(rt,pos);
        splay(tx);
        rs(x)=rs(tx);
        ls(x)=tx;
        rs(tx)=0;
        fa(rs(x))=fa(ls(x))=x;
        pushup(tx);
        pushup(x);
        rt=x;
    }
    inline void del(int pos)
    {
        int x=kth(rt,pos);
        splay(x);
        if(!ls(x))
        {
            rt=rs(x);
            fa(rt)=0;
            t[x].clear();
            return;
        }
        int tx=ls(x);
        fa(tx)=ls(x)=0;
        while(rs(tx)) tx=rs(tx);
        splay(tx);
        rs(tx)=rs(x);
        fa(rs(tx))=tx;
        pushup(tx);
        rt=tx;
        t[x].clear();
    }
    inline int get_rank(int x)
    {
        splay(x);
        return t[ls(x)].siz+1;
    }
    void build(int n)
    {
        for(int i=1;i<=n;i++)
        {
            if(i!=n) t[i].fa=i+1;
            if(i!=1) t[i].son[0]=i-1;
            pushup(i);
        }
        rt=n;
    }
    #undef ls
    #undef rs
    #undef fa
    #undef rson
}
namespace splay{
    struct node{
        int son[2],siz,fa;
        void clear(){son[0]=son[1]=siz=fa=0;}
    }t[MAXN];
    #define ls(x) t[x].son[0]
    #define rs(x) t[x].son[1]
    #define fa(x) t[x].fa
    #define rson(x) (rs(fa(x))==x)
    int rt[MAXN],lstpos[MAXN];
    inline void pushup(const int &x){t[x].siz=1+t[ls(x)].siz+t[rs(x)].siz;}
    inline void rotate(int x,int id)
    {
        int y=fa(x),z=fa(y);
        bool rsx=rson(x),rsy=rson(y);
        if(z) t[z].son[rsy]=x;
        else rt[id]=x;
        t[y].son[rsx]=t[x].son[!rsx];
        t[x].son[!rsx]=y;
        fa(y)=x;fa(x)=z;
        fa(t[y].son[rsx])=y;
        pushup(y);pushup(x);
    }
    inline void splay(int x,int id)
    {
        while(fa(x))
        {
            if(fa(fa(x))) rotate((rson(x)==rson(fa(x))?fa(x):x),id);
            rotate(x,id);
        }
    }
    inline int get_rank(int x,int id)
    {
        splay(x,id);
        return t[ls(x)].siz+1;
    }
    inline int find(int x,int val)
    {
        int rk=Splay::get_rank(x);
        if(rk==val) return x;
        if(rk>val)
        {
            if(ls(x)) return find(ls(x),val);
            else return x;
        }
        else
        {
            if(rs(x)) return find(rs(x),val);
            else return x;
        }
    }
    inline void del(int x,int id)
    {
        splay(x,id);
        if(!ls(x))
        {
            rt[id]=rs(x);
            fa(rt[id])=0;
            t[x].clear();
            return;
        }
        int tx=ls(x);
        fa(tx)=ls(x)=0;
        while(rs(tx)) tx=rs(tx);
        splay(tx,id);
        rs(tx)=rs(x);
        fa(rs(tx))=tx;
        pushup(tx);
        rt[id]=tx;
        t[x].clear();
    }
    inline void insert(int x,int pos,int id)
    {
        t[x].clear();
        if(!rt[id])
        {
            rt[id]=x;
            t[x].siz=1;
            return;
        }
        int tx=find(rt[id],pos);
        int rk=Splay::get_rank(tx);
        splay(tx,id);
        if(rk<=pos)
        {
            ls(x)=tx;
            rs(x)=rs(tx);
            rs(tx)=0;
            fa(ls(x))=fa(rs(x))=x;
            pushup(tx);pushup(x);
            rt[id]=x;
        }
        else
        {
            ls(x)=ls(tx);
            rs(x)=tx;
            ls(tx)=0;
            fa(ls(x))=fa(rs(x))=x;
            pushup(tx);pushup(x);
            rt[id]=x;
        }
    }
    inline void build(int n)
    {
        for(int i=1;i<=n;i++)
        {
            if(lstpos[a[i]]) ls(i)=lstpos[a[i]],fa(lstpos[a[i]])=i;
            pushup(i);lstpos[a[i]]=i;rt[a[i]]=i;
        }
    }
    inline int query(int x,int val,int id)
    {
        int k=Splay::get_rank(x),ret=0;
        if(k>val)
        {
            if(ls(x)) ret+=query(ls(x),val,id);
            else splay(x,id);
        }
        else
        {
            ret=t[ls(x)].siz+1;
            if(rs(x)) ret+=query(rs(x),val,id);
            else splay(x,id);
        }
        return ret;
    }
    #undef ls
    #undef rs
    #undef fa
    #undef rson
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    Splay::build(n);splay::build(n);
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d%d",&opt,&l,&r);
        l=(l+lstans-1)%n+1;
        r=(r+lstans-1)%n+1;
        if(l>r) swap(l,r);
        if(opt==1)
        {
            if(l==r) continue;
            int t=Splay::kth(Splay::rt,r);
            Splay::del(r);
            splay::del(t,a[t]);
            splay::insert(t,l-1,a[t]);
            Splay::insert(t,l-1);
        }
        else
        {
            scanf("%d",&k);
            k=(k+lstans-1)%n+1;
            if(!splay::rt[k])
            {
                lstans=0;
                printf("0\n");
                continue;
            }
            lstans=splay::query(splay::rt[k],r,k)-splay::query(splay::rt[k],l-1,k);
            printf("%d\n",lstans);
        }
    }
}
