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
#define rson(x) (tree[fa(x)].son[1]==x)
const int MAXN=80010;
const int fir=160001;
const int lst=160002;
struct node{
    int son[2];
    int val,fa,siz;
}tree[MAXN<<1];
int root,cnt,pos[MAXN<<1],arr[MAXN<<1],n,m;
int t1,t2;
char opt[20];
void print(int x)
{
    if(ls(x)) print(ls(x));
    printf("%d,val=%d,siz=%d,ls=%d,rs=%d,fa=%d\n",x,tree[x].val,tree[x].siz,tree[x].son[0],rs(x),fa(x));
    if(rs(x)) print(rs(x));
}
void pushup(int x)
{
    tree[x].siz=tree[ls(x)].siz+tree[rs(x)].siz+1;
    pos[tree[x].val]=x;
    pos[tree[ls(x)].val]=ls(x);
    pos[tree[rs(x)].val]=rs(x);
}
void rotate(int x)
{
    int y=tree[x].fa,z=tree[y].fa;
    bool rsx=rson(x),rsy=rson(y);
    if(z)
        tree[z].son[rsy]=x;
    else root=x;
    tree[y].son[rsx]=tree[x].son[rsx^1];
    tree[x].son[rsx^1]=y;
    tree[x].fa=z;tree[y].fa=x;
    fa(tree[y].son[rsx])=y;
    pushup(y);
    pushup(x);
}
void splay(int x,int pos)
{
    while(tree[x].fa!=pos)
    {
        int y=tree[x].fa,z=tree[y].fa;
        if(z!=pos)
            rotate(rson(x)^rson(y)?x:y);
        rotate(x);
    }
}
void build(int &x,int l,int r,int fa)
{
    if(l>r)
        return;
    if(!x)
        x=++cnt;
    if(l==r)
    {
        tree[x].val=arr[l];
        tree[x].fa=fa;
        tree[x].siz=1;
        return;
    }
    int mid=(l+r)>>1;
    build(ls(x),l,mid-1,x);
    build(rs(x),mid+1,r,x);
    tree[x].val=arr[mid];
    tree[x].fa=fa;
    tree[x].siz=1;
    pushup(x);
}
int kth(int x,int th)
{
    if(tree[ls(x)].siz+1==th)
        return x;
    if(tree[ls(x)].siz+1<th)
        return kth(rs(x),th-1-tree[ls(x)].siz);
    else return kth(ls(x),th);
}
void insert(int x,int val)
{
    splay(x,0);
    root=++cnt;
    tree[cnt].val=val;
    tree[cnt].son[0]=x;
    fa(x)=cnt;
    tree[cnt].son[1]=tree[x].son[1];
    tree[x].son[1]=0;
    fa(rs(cnt))=cnt;
    pushup(x);
    pushup(cnt);
}
void del(int x)
{
    splay(x,0);
    int tmp=tree[x].son[0];
    while(rs(tmp))
        tmp=rs(tmp);
    splay(tmp,root);
    tree[tmp].son[1]=tree[x].son[1];
    fa(rs(tmp))=tmp;
    fa(tmp)=0;
    root=tmp;
    tree[x].val=6666;
}
void top(int num)
{
    int x=pos[num];
    del(x);
    insert(kth(root,1),num);
}
void bottom(int num)
{
    int x=pos[num];
    del(x);
    insert(kth(root,n),num);
}
int ask(int num)
{
    int x=pos[num];
    splay(x,0);
    return tree[ls(x)].siz-1;
}
int query(int pos)
{
    return tree[kth(root,pos+1)].val;
}
void ins(int num,int x)
{
    if(x==0)
        return;
    int _pos=ask(num)+1;
    del(pos[num]);
    insert(kth(root,_pos+x),num);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]);
    arr[0]=fir,arr[n+1]=lst;
    build(root,0,n+1,0);
    for(int i=1;i<=m;i++)
    {
        scanf("%s%d",opt+1,&t1);
        switch(opt[1])
        {
            case 'T' : top(t1);break;
            case 'B' : bottom(t1);break;
            case 'Q' : printf("%d\n",query(t1));break;
            case 'A' : printf("%d\n",ask(t1));break;
            case 'I' : scanf("%d",&t2);ins(t1,t2);break;
        }
        //print(root);
    }
}
