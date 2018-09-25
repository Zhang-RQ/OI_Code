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

const int MAXN=3E5+10;

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==x)

struct dat{
    ll v,siz;
    dat(){}
    dat(ll _,ll __){siz=__;v=_;}
    pair<dat,dat> split(ll k) const {return make_pair(dat(v,k),dat(v+k,siz-k));}
};

struct node{
    int son[2],fa;
    ll siz;
    dat v;
}t[MAXN<<5];

int rt[MAXN],cnt,n,m,q;

void pushup(int x) {if(x) t[x].siz=t[ls(x)].siz+t[rs(x)].siz+t[x].v.siz;}

void rotate(int x,int row)
{
    int y=fa(x),z=fa(y);
    bool rsx=rson(x),rsy=rson(y);
    if(z) t[z].son[rsy]=x;
    else rt[row]=x;
    t[y].son[rsx]=t[x].son[!rsx];
    t[x].son[!rsx]=y;
    fa(t[y].son[rsx])=y;
    fa(y)=x;fa(x)=z;
    pushup(y);pushup(x);
}

void splay(int x,int row)
{
    while(fa(x))
    {
        if(fa(fa(x))) rotate(rson(x)^rson(fa(x))?x:fa(x),row);
        rotate(x,row);
    }
    pushup(x);
}

int kth(int x,ll k)
{
    if(t[ls(x)].siz<k&&k<=t[ls(x)].siz+t[x].v.siz) return x;
    if(t[ls(x)].siz+t[x].v.siz>=k) return kth(ls(x),k);
    else return kth(rs(x),k-t[ls(x)].siz-t[x].v.siz);
}

void insert(int p,int row,dat v) //after p(rank)
{
    if(!rt[row])
    {
        rt[row]=++cnt;
        t[cnt].v=v;pushup(cnt);
        return;
    }
    if(p==0)
    {
        int x=rt[row];
        while(ls(x)) x=ls(x);
        splay(x,row);
        int y=++cnt;
        ls(x)=y;fa(y)=x;
        t[y].v=v;pushup(y);
        return;
    }
    int x=kth(rt[row],p);
    splay(x,row);
    if(rs(x))
    {
        x=rs(x);
        while(ls(x)) x=ls(x);
        int y=++cnt;
        fa(y)=x;t[y].v=v;ls(x)=y;
        while(fa(y)) pushup(y),y=fa(y);
        pushup(y);
    }
    else
    {
        int y=++cnt;
        rs(x)=y;
        fa(y)=x;t[y].v=v;
        pushup(y);pushup(x);
    }
}

dat split(int p,int row) //[l,p-1] ,[p,p] ,[p+1,r] return [p,p] p is rank
{
    int x=kth(rt[row],p);
    splay(x,row);
    pair<dat,dat> S=t[x].v.split(p-t[ls(x)].siz-1);
    if(S.first.siz==0)
    {
        if(!ls(x))
        {
            rt[row]=rs(x);
            fa(rs(x))=0;
        }
        else
        {
            int y=ls(x);fa(y)=0;
            while(rs(y)) y=rs(y);
            splay(y,row);
            rs(y)=rs(x);fa(rs(x))=y;
            pushup(y);
        }
    }
    else t[x].v=S.first,pushup(x);
    if(S.second.siz!=1)
    {
        pair<dat,dat> T=S.second.split(1);
        insert(p-1,row,T.second);
        return T.first;
    }
    return S.second;
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
    {
        rt[i]=++cnt;
        t[cnt].v.v=1ll*(i-1)*m+1;
        t[cnt].v.siz=m-1;pushup(cnt);
    }
    for(int i=1;i<=n;i++)
    {
        ++cnt;
        fa(rt[0])=cnt;
        ls(cnt)=rt[0];
        t[cnt].v.v=1ll*i*m;
        t[cnt].v.siz=1;
        pushup(cnt);rt[0]=cnt;
    }
    for(int i=1,x,y;i<=q;i++)
    {
        scanf("%d%d",&x,&y);
        if(y!=m)
        {
            dat p=split(y,x);
            printf("%lld\n",p.v);
            dat q=split(x,0);
            insert(m-2,x,q);
            insert(n-1,0,p);
        }
        else
        {
            dat p=split(x,0);
            printf("%lld\n",p.v);
            insert(n-1,0,p);
        }
    }
}