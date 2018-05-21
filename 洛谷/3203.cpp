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
const int MAXN=2E5+10;
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==x)
struct ndoe{
    int son[2],siz,fa;
    bool rev;
}t[MAXN];
bool isroot(int x) {return (x!=ls(fa(x)))&&(x!=rs(fa(x)));}
void pushup(int x) {t[x].siz=t[ls(x)].siz+t[rs(x)].siz+1;};
void pushdown(int x) {if(t[x].rev) swap(ls(x),rs(x)),t[ls(x)].rev^=1,t[rs(x)].rev^=1,t[x].rev=0;}
void pd(int x){if(!isroot(x)) pd(fa(x));pushdown(x);}
int k[MAXN],n,m,opt,x,y;
void rotate(int x)
{
    int y=fa(x),z=fa(y);
    bool rsx=rson(x),rsy=rson(y);
    if(!isroot(y)) t[z].son[rsy]=x;
    t[y].son[rsx]=t[x].son[!rsx];
    t[x].son[!rsx]=y;
    fa(y)=x;fa(x)=z;
    fa(t[y].son[rsx])=y;
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
void link(int x,int y)
{
    makeroot(x);
    if(findroot(y)==x) return;
    fa(x)=y;
}
void split(int x,int y)
{
    makeroot(x);
    access(y);splay(y);
}
void cut(int x,int y)
{
    split(x,y);
    if(ls(y)==x) ls(y)=fa(x)=0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&k[i]),link(i,(i+k[i]>n)?n+1:i+k[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&opt,&x);
        x++;
        if(opt==1)
        {
            makeroot(x);
            access(n+1);splay(n+1);
            printf("%d\n",t[n+1].siz-1);
        }
        else
        {
            scanf("%d",&y);
            cut(x,(x+k[x]>n)?n+1:x+k[x]);
            k[x]=y;
            link(x,(x+k[x]>n)?n+1:x+k[x]);
        }
    }
    #ifdef LOCAL
        system("pause");
    #endif
}