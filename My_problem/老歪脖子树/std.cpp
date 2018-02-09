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
const int P=1E9+7;
const int MAXN=5E5+5;
#define ls(x) tree[x].son[0]
#define rs(x) tree[x].son[1]
#define fa(x) tree[x].fa
struct node{
    int son[2],fa,siz;            //tree struct
    ll mul,sum;                  //val
    int val,minn,maxn;          //val
    int edt,rev,mult;          //tags
}tree[MAXN];
int root,cnt;
int stk[MAXN],top;
int arr[MAXN];
ll ksm(ll base,int b)
{
    ll ret=1;
    while(b)
    {
        if(b&1)  (ret*=base)%=P;
        (base*=base)%=P;
        b>>=1;
    }
    return ret%P;
}
inline void pushup(int x)
{
    fa(ls(x))=fa(rs(x))=x;
    tree[x].siz=tree[ls(x)].siz+tree[rs(x)].siz+1;
    (tree[x].sum=(tree[ls(x)].sum+tree[rs(x)].sum)%P+tree[x].val)%=P;
    (tree[x].mul=((tree[ls(x)].mul*tree[rs(x)].mul)%P)*tree[x].val)%=P;
    tree[x].minn=min(tree[x].val,min(tree[ls(x)].minn,tree[rs(x)].minn));
    tree[x].maxn=max(tree[x].val,max(tree[ls(x)].maxn,tree[rs(x)].maxn));
}
inline void pushdown(int x)
{
    if(tree[x].edt!=0)
    {
        int k=tree[x].edt%P;
        tree[x].edt=0;
        tree[ls(x)].edt=tree[rs(x)].edt=k;  //tags
        tree[ls(x)].val=tree[rs(x)].val=k;  //val
        tree[ls(x)].sum=tree[ls(x)].val*tree[ls(x)].siz%P;
        tree[rs(x)].sum=tree[rs(x)].val*tree[rs(x)].siz%P;
        tree[ls(x)].mul=ksm(tree[ls(x)].val,tree[ls(x)].siz);
        tree[rs(x)].mul=ksm(tree[rs(x)].val,tree[rs(x)].siz);
        tree[ls(x)].minn=tree[ls(x)].maxn=tree[ls(x)].val;
        tree[rs(x)].minn=tree[rs(x)].maxn=tree[rs(x)].val;
    }
    if(tree[x].mult!=1)
    {
        int k=tree[x].mult;
        tree[x].mult=1;
        (tree[ls(x)].mult*=k)%=P;(tree[rs(x)].mult*=k)%=P;  //tags
        (tree[ls(x)].edt*=k)%=P;(tree[rs(x)].edt*=k)%=P;    //tags
        (tree[ls(x)].sum+=tree[ls(x)].siz*k)%=P;            //val
        (tree[rs(x)].sum+=tree[rs(x)].siz*k)%=P;
        (tree[ls(x)].val*=tree[ls(x)].mult)%=P;
        (tree[rs(x)].val*=tree[rs(x)].mult)%=P;
        (tree[ls(x)].maxn*=tree[ls(x)].mult)%=P;
        (tree[rs(x)].maxn*=tree[ls(x)].mult)%=P;
        (tree[ls(x)].minn*=tree[ls(x)].mult)%=P;
        (tree[rs(x)].minn*=tree[ls(x)].mult)%=P;
        (tree[ls(x)].mul*=ksm(tree[ls(x)].mult,tree[ls(x)].siz))%=P;
        (tree[rs(x)].mul*=ksm(tree[rs(x)].mult,tree[rs(x)].siz))%=P;
    }
    if(tree[x].rev)
    {
        tree[x].rev=0;
        tree[ls(x)].rev^=1;tree[rs(x)].rev^=1;
        swap(ls(ls(x)),rs(ls(x)));
        swap(ls(rs(x)),rs(rs(x)));
    }
}
inline void rotate(int x)
{
    int y=fa(x),z=fa(y);
    bool rsx=(rs(y)==x),rsy=(rs(fa(y))==y);
    if(z) tree[z].son[rsy]=x,fa(x)=z;
    else root=x;
    tree[y].son[rsx]=tree[x].son[!rsx];
    tree[x].son[!rsx]=y;
    pushup(y);
    pushup(x);
}
inline void splay(int x,int pos)
{
    int tmp=x;top=0;
    stk[++top]=x;
    while(fa(tmp)!=pos)
        stk[++top]=fa(tmp),
        tmp=fa(tmp);
    while(top) pushdown(stk[top--]);
    while(fa(x)!=pos)
    {
        int y=fa(x);
        bool rsx=(rs(y)==x),rsy=(rs(fa(y))==y);
        rotate(rsx^rsy?x:y);
        rotate(x);
    }
}
void build(int &x,int l,int r)
{
    x=++cnt;
    tree[x].val=tree[x].minn=tree[x].maxn=tree[x].mul=tree[x].sum=arr[l];
    tree[x].mult=1;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(tree[x].son[0],l,mid);
    build(tree[x].son[1],mid+1,r);
    pushup(x);
}
int kth(int x,int rk)
{
    if(tree[ls(x)].siz+1==rk) return x;
    if(tree[ls(x)].siz+1>rk) return kth(rs(x),rk-1-tree[ls(x)].siz);
    return kth(ls(x),rk);
}
int get_range(int l,int r)
{
    int tmp=kth(root,l-1);
    splay(tmp,0);
    splay(kth(root,r+1),tmp);
    return rs(root);
}
int main()
{

}
