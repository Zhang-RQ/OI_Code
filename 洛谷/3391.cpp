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
const int MAXN=100010;
#define Ls(x) tree[x].son[0]
#define Rs(x) tree[x].son[1]
#define rson(x) (tree[tree[x].fa].son[1]==x)
struct node{
    int son[2],val,siz,fa;
    bool rev;
}tree[MAXN];
int root,cnt;
int n,q,L,R;
inline void pushup(const int &x)
{
    tree[x].siz=tree[Ls(x)].siz+tree[Rs(x)].siz+1;
    tree[Ls(x)].fa=x;tree[Rs(x)].fa=x;
}
inline void pushdown(const int &x)
{
    if(tree[x].rev)
    {
        swap(Ls(x),Rs(x));
        tree[Ls(x)].rev^=1;
        tree[Rs(x)].rev^=1;
        tree[x].rev=0;
    }
}
void rotate(int x)
{
    int fx=tree[x].fa,ffx=tree[fx].fa;
    bool rsx=rson(x),rsfx=rson(fx);
    if(ffx)
        tree[ffx].son[rsfx]=x;
    else root=x;
    tree[x].fa=ffx;
    tree[fx].son[rsx]=tree[x].son[rsx^1];
    tree[x].son[rsx^1]=fx;
    pushup(fx);
    pushup(x);
}
stack<int> stk;
void splay(int x,int pos)
{
    stk.push(x);
    for(int i=x;tree[i].fa!=pos;i=tree[i].fa)
        stk.push(tree[i].fa);
    while(!stk.empty())
        pushdown(stk.top()),stk.pop();
    while(tree[x].fa!=pos)
    {
        int fx=tree[x].fa,ffx=tree[fx].fa;
        if(ffx!=pos)
            rotate(rson(x)^rson(fx)?x:fx);
        rotate(x);
    }
}
int find(int x,int pos)
{
    pushdown(x);
    if(pos==tree[Ls(x)].siz+1) return x;
    if(tree[Ls(x)].siz+1<pos) return find(Rs(x),pos-tree[Ls(x)].siz-1);
    else return find(Ls(x),pos);
}
void rev(int l,int r)
{
    int _l=find(root,l),_r=find(root,r+2);
    splay(_l,0),splay(_r,_l);
    tree[tree[_r].son[0]].rev^=1;
}
void print(int x)
{
    pushdown(x);
    if(Ls(x)) print(Ls(x));
    if(x>=2&&x<n+2) printf("%d ",x-1);
    if(Rs(x)) print(Rs(x));
}
int main()
{
    scanf("%d%d",&n,&q);
    root=1;
    for(int i=1;i<=n+2;i++)
    {
        tree[i].fa=i-1,tree[i].siz=n+3-i;
        if(i!=n+2)
            tree[i].son[1]=i+1;
    }
    tree[root].fa=0;
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&L,&R);
        rev(L,R);
    }
    print(root);
    puts("");
}
