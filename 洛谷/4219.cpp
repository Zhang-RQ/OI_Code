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
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==x)
const int MAXN=1.5E5+10;
struct node{
    int son[2],fa,siz,sizv; // siz real+imag  sizv imag
    bool rev;
}t[MAXN];
int n,q,x,y;
char opt[10];
void debug()
{
    for(int i=1;i<=10;i++) printf("%d ",t[i].siz);
    puts("");
}
inline bool isroot(const int &x) {return ls(fa(x))!=x&&rs(fa(x))!=x;}
inline void pushup(const int &x) {t[x].siz=t[ls(x)].siz+t[rs(x)].siz+t[x].sizv+1;}
inline void pushdown(const int &x){if(t[x].rev) t[ls(x)].rev^=1,t[rs(x)].rev^=1,swap(ls(x),rs(x)),t[x].rev=0;}
inline void pd(const int &x) {if(!isroot(x)) pd(fa(x));pushdown(x);}
inline void rotate(const int &x)
{
    int y=fa(x),z=fa(y);
    bool rsx=rson(x),rsy=rson(y);
    if(!isroot(y)) t[z].son[rsy]=x;
    t[y].son[rsx]=t[x].son[!rsx];
    t[x].son[!rsx]=y;
    t[x].fa=z;t[y].fa=x;
    t[t[y].son[rsx]].fa=y;
    pushup(y);pushup(x);
}
inline void splay(int x)
{
    pd(x);
    while(!isroot(x))
    {
        if(!isroot(fa(x))) rotate(rson(x)^rson(fa(x))?x:fa(x));
        rotate(x);
    }
}
inline void access(int x)
{
    for(int y=0;x;y=x,x=fa(x))
    {
        splay(x);
        t[x].sizv+=t[rs(x)].siz;
        t[x].sizv-=t[y].siz;
        rs(x)=y;pushup(x);
    }
}
inline void makeroot(const int &x)
{
    access(x);splay(x);
    t[x].rev^=1;
}
inline void link(const int &x,const int &y)
{
    makeroot(x);access(y);splay(y);
    fa(x)=y;
    t[y].sizv+=t[x].siz;
    pushup(y);
}
inline void cut(const int &x,const int &y)
{
    makeroot(x);
    access(y);splay(y);
    assert(t[y].son[0]==x);
    t[y].son[0]=0;fa(x)=0;
    pushup(y);
}
inline ll query(const int &x,const int &y)
{
    makeroot(x);access(y);splay(y);
    return 1ll*(t[x].sizv+1)*(t[y].sizv+1);
}
int main()
{
    scanf("%d%d",&n,&q);
    while(q--)
    {
        scanf("%s%d%d",opt+1,&x,&y);
        if(opt[1]=='A') link(x,y);
        else printf("%lld\n",query(x,y));
        // debug();
    }
}
