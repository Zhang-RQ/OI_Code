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
#define fa(x) tree[x].fa
#define ls(x) tree[x].son[0]
#define rs(x) tree[x].son[1]
const int MAXN=10010;
struct node{
    int son[2],fa;
    bool rev;
}tree[MAXN];
int stk[MAXN],top;
bool isroot(int x)
{
    return ls(fa(x))!=x&&rs(fa(x))!=x;
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
void rotate(int x)
{
    int y=fa(x),z=fa(y);
    bool rsx=rs(y)==x,rsy=rs(z)==y;
    if(!isroot(y))
        tree[z].son[rsy]=x;
    tree[y].son[rsx]=tree[x].son[rsx^1];
    tree[x].son[rsx^1]=y;
    fa(x)=z;fa(y)=x;fa(tree[y].son[rsx])=y;
}
void splay(int x)
{
    bool rsx,rsy;
    top=0;
    stk[++top]=x;
    for(int i=x;!isroot(i);i=fa(i))
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
        splay(x),tree[x].son[1]=t;
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
void split(int x,int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x,int y)
{
    makeroot(x);
    tree[x].fa=y;
}
void cut(int x,int y)
{
    split(x,y);
    if(ls(y)==x)
        tree[x].fa=tree[y].son[0]=0;
}
int main()
{
    int n,m,x,y;
    char op[10];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",op);
        scanf("%d%d",&x,&y);
        if(op[0]=='Q')
        {
            if(findroot(x)==findroot(y))
                puts("Yes");
            else
                puts("No");
        }
        if(op[0]=='D')
            cut(x,y);
        if(op[0]=='C')
            link(x,y);
    }
    return 0;
}
