#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define ls(x) tree[x].son[0]
#define rs(x) tree[x].son[1]
#define fa(x) tree[x].fa
const int MAXN=10010;
struct lct{
    int stk[MAXN],top,cnt[MAXN];
    struct node{
        int fa,son[2],mx,val;
        bool rev;
    }tree[MAXN];
    void pushup(int x)
    {
        tree[x].mx=max(tree[x].val,max(tree[ls(x)].mx,tree[rs(x)].mx));
    }
    void pushdown(int x)
    {
        if(tree[x].rev)
        {
            swap(ls(x),rs(x));
            tree[ls(x)].rev^=1;
            tree[rs(x)].rev^=1;
            tree[x].rev=0;
        }
    }
    bool isroot(int x)
    {
        return ls(fa(x))!=x&&rs(fa(x))!=x;
    }
    void rotate(int x)
    {
        int y=fa(x),z=fa(y);
        bool rsx=rs(y)==x,rsy=rs(z)==y;
        if(!isroot(y))
            tree[z].son[rsy]=x;
        tree[y].son[rsx]=tree[x].son[rsx^1];
        tree[x].son[rsx^1]=y;
        tree[y].fa=x;
        tree[tree[y].son[rsx]].fa=y;
        pushup(y);
        pushup(x);
    }
    void splay(int x)
    {
        bool rsx,rsy;
        top=0;
        stk[++top]=x;
        for(int i=x;!isroot(x);i=fa(i))
            stk[++top]=fa(i);
        while(top)
            pushdown(stk[top--]);
        while(!isroot(x))
        {
            rsx=rs(fa(x))==x;rsy=rs(fa(fa(x)))==fa(x);
            if(!isroot(fa(x)))
                rotate(rsx^rsy?fa(x):x);
            rotate(x);
        }
    }
    void access(int x)
    {
        for(int t=0;x;t=x,x=fa(x))
            splay(x),tree[rs(x)].fa=t;
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        tree[x].rev^=1;
    }
    int findroot(int x)
    {
        access(x);
        splay(x);
        while(ls(x))
            x=ls(x);
        return x;
    }
    void change(int pnt,int val)
    {
        access(pnt);
        splay(pnt);
        tree[pnt].val=val;
        pushup(pnt);
    }
    void link(int x,int y)
    {
        makeroot(x);
        tree[x].fa=y;
    }
    void cut(int x,int y)
    {
        makeroot(x);
        access(y);
        splay(y);
        if(tree[y].son[0]==x)
            tree[x].fa=tree[y].son[0]=0;
    }
}t[11];
struct edge{
    int u,v;
    bool operator <(const edge &a) const
    {
        if(a.u!=u)
            return u<a.u;
        else return v<a.v;
    }
};
map<edge,int> mp;
int n,m,c,k,u,v,w,opt,t1,t2,t3;
int main()
{
    scanf("%d%d%d%d",&n,&m,&c,&k);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        mp[(edge){u,v}]=mp[(edge){v,u}]=w;
    }
    for(int i=1;i<=k;i++)
    {
        scanf("%d",&opt);
        if(opt==1)
        {

        }
    }
}
