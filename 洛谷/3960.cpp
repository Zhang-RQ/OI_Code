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
struct node{
    int son[2],fa,val,siz;
    void clear()
    {
        son[0]=son[1]=fa=val=siz=0;
    }
}tree[3000010];
int root[6010],cnt,arr[301000];
void pushup(int x)
{
    fa(ls(x))=fa(rs(x))=x;
    tree[x].siz=tree[ls(x)].siz+tree[rs(x)].siz+1;
}
void rotate(int x,int row)
{
    int y=fa(x),z=fa(y);
    bool rsx=(rs(y)==x),rsy=(rs(z)==y);
    if(z)
        tree[z].son[rsy]=x,tree[x].fa=z;
    else tree[x].fa=0,root[row]=x;
    tree[y].son[rsx]=tree[x].son[!rsx];
    tree[x].son[!rsx]=y;
    pushup(y);
    pushup(x);
}
void splay(int x,int row)
{
    while(fa(x))
    {
        if(fa(fa(x)))
            rotate((ls(fa(x))==x)^(ls(fa(fa(x))))?fa(x):x,row);
        rotate(x,row);
    }
}
int kth(int x,int pos)
{
    //printf("x=%d,pos=%d,siz(ls)=%d,ls=%d,rs=%d\n",x,pos,tree[ls(x)].siz,ls(x),rs(x));
    if(tree[ls(x)].siz+1==pos)
        return x;
    if(tree[ls(x)].siz+1>pos)
        return kth(ls(x),pos);
    else return kth(rs(x),pos-1-tree[ls(x)].siz);
}
void append(int row,int pos,int val)
{
    int x=kth(root[row],pos);
    //printf("x=%d pos=%d\n",x,pos);
    splay(x,row);
    tree[++cnt].val=val;
    tree[cnt].son[1]=tree[x].son[1];
    tree[x].son[1]=cnt;
    pushup(cnt);
    pushup(x);
}
int query(int row,int pos)
{
    int x=kth(root[row],pos),y=kth(root[row],pos-1);
    int ret=tree[x].val;
    splay(x,row);
    root[row]=y;
    tree[y].fa=0;
    tree[y].son[1]=tree[x].son[1];
    tree[x].clear();
    pushup(y);
    return ret;
}
void build(int row,int n)
{
    int pre=0;
    for(int i=1;i<=n;i++)
    {
        tree[++cnt].val=arr[i];
        tree[cnt].son[0]=pre;
        pre=cnt;
        pushup(cnt);
    }
    root[row]=pre;
    splay(kth(root[row],n/2),row);
}
int n,m,q,x,y,ans,tmp;
void output(int x)
{
    if(ls(x)) output(ls(x));
    printf("id=%d,val=%d,ls=%d,rs=%d,fa=%d,siz=%d\n",x,tree[x].val,ls(x),rs(x),fa(x),tree[x].siz);
    if(rs(x)) output(rs(x));
}
int main()
{
    //freopen("phalanx.out","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n+2;i++)
        arr[i]=(i-1)*m;
    build(0,n+2);
    for(int i=1;i<=q;i++)
    {
        //printf("%d:\n",i);
        scanf("%d%d",&x,&y);
        if(!root[x])
        {
            for(int j=1;j<=m+1;j++)
                arr[j]=(x-1)*m+j-1;
            build(x,m+1);
        }
        if(y!=m)
        {
            /*puts("1:");
            output(root[x]);
            puts("");*/
            ans=query(x,y+1);
            /*puts("2:");
            output(root[0]);
            puts("");*/
            tmp=query(0,x+1);
            //printf("%d %d\n",ans,tmp);
            //puts("3:");
            /*output(root[0]);
            puts("");*/
            append(0,n,ans);
            /*puts("4:");
            output(root[x]);
            puts("");*/
            append(x,m-1,tmp);
            /*puts("root[x]:");
            output(root[x]);
            puts("root[0]:");
            output(root[0]);*/
        }
        else
        {
            //output(root[0]);
            ans=query(0,x+1);
            printf("%d\n",ans);
            append(0,m,ans);
            /*puts("root[0]:");
            output(root[0]);*/
        }
        //puts("\n");
    }
}
