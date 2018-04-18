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
const int MAXN=50010;
const int MAXM=100010;
#define fa(x) t[x].fa
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
struct node{
    int son[2],val,fa,mx,mxn;
    bool rev;
}t[MAXN+MAXM];
struct Ed{
    int u,v,a,b;
    bool operator <(const Ed &rhs) const{return a<rhs.a;}
}E[MAXM];
int n,m,ans=1<<30;
bool isroot(int x){return ls(fa(x))!=x&&rs(fa(x))!=x;}
bool rson(int x)  {return rs(fa(x))==x;}
void pushup(int x)
{
    t[x].mx=max(t[x].val,max(t[ls(x)].mx,t[rs(x)].mx));
    if(t[x].val>max(t[ls(x)].mx,t[rs(x)].mx)) t[x].mxn=x;
    else t[x].mxn=(t[x].mx==t[ls(x)].mx)?t[ls(x)].mxn:t[rs(x)].mxn;
}
void pushdown(int x) {if(t[x].rev) {swap(ls(x),rs(x));t[ls(x)].rev^=1;t[rs(x)].rev^=1;t[x].rev=0;}}
void pd(int x) {if(!isroot(x)) {pd(fa(x));}pushdown(x);}
void rotate(int x)
{
    int y=fa(x),z=fa(y);
    bool rsx=rson(x),rsy=rson(y);
    if(!isroot(y)) t[z].son[rsy]=x;
    t[y].son[rsx]=t[x].son[!rsx];
    t[x].son[!rsx]=y;
    fa(t[y].son[rsx])=y;
    fa(y)=x;fa(x)=z;
    pushup(y);pushup(x);
}
void splay(int x)
{
    pd(x);
    while(!isroot(x))
    {
        if(!isroot(fa(x))) rotate(rson(x)==rson(fa(x))?fa(x):x);
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
void split(int x,int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x,int y)
{
    makeroot(x);
    if(findroot(y)==x) return;
    fa(x)=y;
}
void cut(int x,int y)
{
    split(x,y);
    if(ls(y)==x)  ls(y)=fa(x)=0;
}
int query(int x,int y)
{
    makeroot(x);access(y);
    splay(y);
    return t[y].mx;
}
int queryn(int x,int y)
{
    makeroot(x);access(y);
    splay(y);
    return t[y].mxn;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].a,&E[i].b);
    sort(E+1,E+1+m);
    for(int i=1;i<=m;i++) t[i+n].val=E[i].b,t[i+n].mxn=i+n;
    for(int i=1;i<=m;i++)
    {
        if(findroot(E[i].u)==findroot(E[i].v))
        {
            int t=query(E[i].u,E[i].v);
            if(t>E[i].b)
            {
                int x=queryn(E[i].u,E[i].v);
                cut(E[x-n].u,x);cut(x,E[x-n].v);
            }
            else continue;
        }
        link(E[i].u,i+n);link(E[i].v,i+n);
        if(findroot(1)==findroot(n)) ans=min(ans,E[i].a+query(1,n));
    }
    printf("%d\n",ans==1<<30?-1:ans);
}
