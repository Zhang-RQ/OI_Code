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
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
const int MAXN=300100;
struct node{
    int son[2],fa,val,sum;
    bool rev;
}t[MAXN];
inline void pushup(int x) {t[x].sum=t[ls(x)].sum^t[rs(x)].sum^t[x].val;}
inline bool isroot(int x) {return ls(fa(x))!=x&&rs(fa(x))!=x;}
inline void pushdown(int x) {if(t[x].rev) t[ls(x)].rev^=1,t[rs(x)].rev^=1,swap(ls(x),rs(x)),t[x].rev=0;}
void pd(int x) {if(!isroot(x)){pd(fa(x));}pushdown(x);}
void rotate(int x)
{
    int y=fa(x),z=fa(y);
    int rsx=rs(y)==x,rsy=rs(z)==y;
    if(!isroot(y)) t[z].son[rsy]=x;
    t[y].son[rsx]=t[x].son[rsx^1];
    t[x].son[rsx^1]=y;
    t[x].fa=z;t[y].fa=x;
    t[t[y].son[rsx]].fa=y;
    pushup(y);pushup(x);
}
void splay(int x)
{
    pd(x);
    while(!isroot(x))
    {
        if(!isroot(fa(x))) rotate((rs(fa(fa(x)))==fa(x))==(rs(fa(x))==x)?fa(x):x);
        rotate(x);
    }
}
void access(int x)
{
    for(int y=0;x;y=x,x=fa(x))
        splay(x),rs(x)=y,pushup(x);
}
void makeroot(int x)
{
    access(x);splay(x);
    t[x].rev^=1;
}
int findroot(int x)
{
    access(x);splay(x);
    while(ls(x)) x=ls(x);
    return x;
}
void link(int x,int y)
{
    makeroot(x);
    if(findroot(y)==x) return;
    t[x].fa=y;
}
void split(int x,int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
void cut(int x,int y)
{
    split(x,y);
    if(ls(y)==x) t[y].son[0]=t[x].fa=0;
}
int query(int x,int y)
{
    makeroot(x);access(y);
    splay(y);
    return t[y].sum;
}
void change(int x,int val)
{
    access(x);splay(x);
    t[x].val=val;
    pushup(x);
}
int n,m,x,y,opt;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&t[i].val);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&opt,&x,&y);
        switch(opt)
        {
            case 0:printf("%d\n",query(x,y));break;
            case 1:link(x,y);break;
            case 2:cut(x,y);break;
            case 3:change(x,y);break;
        }
    }
}
