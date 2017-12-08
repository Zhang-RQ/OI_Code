#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define ls(x) tree[x].son[0]
#define rs(x) tree[x].son[1]
#define fa(x) tree[x].fa
struct tree{
    int val,sum,siz;
    int lmax,rmax,mmax,MS;
    bool rev,tag_MS;
    int son[2],fa;
}tree[100];
char opt[20];
int cnt,root,n,m,_pos,_len,_val;
int tmp[10010];
queue<int> dele;
inline void delnode(int x)
{
    tree[fa(x)].son[rs(fa(x))==x]=0;
    tree[x].siz=0;
    dele.push(x);
}
inline int newnode()
{
    if(!dele.empty())
    {
        int ret=dele.front();
        if(ls(ret))
            dele.push(ls(ret));
        if(rs(ret))
            dele.push(rs(ret));
        memset(&tree[ret],0,sizeof(tree[ret]));
        return ret;
    }
    else return ++cnt;
}
inline void pushup(int x)
{
    if(x)
    {
        fa(ls(x))=fa(rs(x))=x;
        tree[x].siz=tree[ls(x)].siz+tree[rs(x)].siz+1;
        tree[x].sum=tree[ls(x)].sum+tree[rs(x)].sum+tree[x].val;
        tree[x].lmax=max(tree[ls(x)].lmax,tree[ls(x)].sum+tree[rs(x)].rmax+tree[x].val);
        tree[x].rmax=max(tree[rs(x)].rmax,tree[rs(x)].sum+tree[ls(x)].rmax+tree[x].val);
        tree[x].mmax=max(tree[ls(x)].rmax+tree[x].val+tree[rs(x)].lmax,max(tree[ls(x)].mmax,tree[rs(x)].mmax));
    }
}
inline void pushdown(int x)
{
    if(tree[x].rev)
    {
        swap(tree[ls(ls(x))].lmax,tree[rs(ls(x))].rmax);
        swap(tree[ls(rs(x))].lmax,tree[rs(rs(x))].rmax);
        swap(ls(ls(x)),rs(ls(x)));
        swap(ls(rs(x)),rs(rs(x)));
        tree[ls(x)].rev^=1;
        tree[rs(x)].rev^=1;
        tree[x].rev=0;
        pushup(x);
    }
    if(tree[x].tag_MS)
    {
        tree[ls(x)].val=tree[rs(x)].val=tree[x].MS;
        tree[ls(x)].MS=tree[rs(x)].MS=tree[x].MS;
        tree[ls(x)].tag_MS=tree[rs(x)].tag_MS=1;
        tree[ls(x)].sum=tree[ls(x)].MS*tree[ls(x)].siz;
        tree[rs(x)].sum=tree[rs(x)].MS*tree[rs(x)].siz;
        if(tree[ls(x)].MS>=0)
            tree[ls(x)].lmax=tree[ls(x)].rmax=tree[ls(x)].sum;
        else tree[ls(x)].lmax=tree[ls(x)].rmax=tree[ls(x)].MS;
        if(tree[rs(x)].MS>=0)
            tree[rs(x)].lmax=tree[rs(x)].rmax=tree[rs(x)].sum;
        else tree[rs(x)].lmax=tree[rs(x)].rmax=tree[rs(x)].MS;
        tree[x].tag_MS=0;
        tree[x].MS=0;
        pushup(x);
    }
}
inline void rotate(int x)
{
    int y=fa(x),z=fa(y);
    int rsx=(rs(y)==x),rsy=(rs(z)==y);
    if(z)
        tree[z].son[rsy]=x,fa(x)=z;
    else root=x,fa(x)=0;
    tree[y].son[rsx]=tree[x].son[!rsx];
    tree[x].son[!rsx]=y;
    pushup(y);
    pushup(x);
}
inline void splay(int x,int pos)
{
    stack<int> stk;
    while(!stk.empty())
        stk.pop();
    stk.push(x);
    for(int i=x;i!=pos;i=fa(i))
        stk.push(fa(i));
    while(!stk.empty())
        pushdown(stk.top()),stk.pop();
    while(fa(x)!=pos)
    {
        //printf("%d\n",x);
        if(fa(fa(x))!=pos)
            rotate((ls(fa(x))==x)^(ls(fa(fa(x)))==fa(x))?x:fa(x));
        rotate(x);
    }
    /*printf("root:%d\n",root);
    for(int i=0;i<=cnt;i++)
            printf("%d:val=%d,fa=%d,lson=%d,rson=%d,sum=%d,siz=%d\n",i,tree[i].val,fa(i),ls(i),rs(i),tree[i].sum,tree[i].siz);*/
}
int kth(int x,int pos)
{
    //printf("%d %d\n",x,pos);
    //system("pause");
    pushdown(x);
    if(tree[ls(x)].siz+1==pos)
        {/*puts("END");*/return x;}
    if(tree[ls(x)].siz+1>pos)
        return kth(ls(x),pos);
    else return kth(rs(x),pos-tree[ls(x)].siz-1);
}
inline int get_range(int l,int len)
{
    if(l==1)
    {
        if(len==tree[root].siz)
            return root;
        splay(kth(len+1,root),0);
        return ls(root);
    }
    splay(kth(root,l-1),0);
    if(tree[rs(root)].siz==len)
        return rs(root);
    splay(kth(root,l+len),root);
    return ls(rs(root));
}
inline void insert(int pos,int len)
{
    int pre=newnode(),x;
    tree[pre].siz=1;
    tree[pre].val=tree[pre].lmax=tree[pre].rmax=tree[pre].mmax=tree[pre].sum=tmp[1];
    for(int i=2;i<=len;i++)
    {
        x=newnode();
        tree[x].siz=1;
        tree[x].val=tree[x].lmax=tree[x].rmax=tree[x].mmax=tree[x].sum=tmp[i];
        tree[x].son[0]=pre;
        pushup(x);
        pre=x;
    }
    if(pos==1)
    {
        rs(pre)=root;
        root=pre;
        pushup(root);
        return;
    }
    splay(kth(root,pos),0);
    rs(pre)=rs(root);
    rs(root)=pre;
    pushup(pre);
    pushup(root);
}
inline void del(int pos,int len)
{
    delnode(get_range(pos,len));
}
inline void make_same(int pos,int len,int val)
{
    int x=get_range(pos,len);
    tree[x].val=val;
    tree[x].sum=val*tree[x].siz;
    tree[x].tag_MS=1;
    tree[x].MS=val;
    if(tree[x].MS>=0)
        tree[ls(x)].lmax=tree[ls(x)].rmax=tree[x].MS*tree[ls(x)].siz;
    else tree[ls(x)].lmax=tree[ls(x)].rmax=tree[x].MS;
    if(tree[x].MS>=0)
        tree[rs(x)].lmax=tree[rs(x)].rmax=tree[x].MS*tree[rs(x)].siz;
    else tree[rs(x)].lmax=tree[rs(x)].rmax=tree[x].MS;
    pushup(x);
}
inline void rev(int pos,int len)
{
    int x=get_range(pos,len);
    //printf("x=%d\n",x);
    tree[x].rev^=1;
    swap(tree[x].lmax,tree[x].rmax);
    swap(ls(x),rs(x));
    pushup(x);
    pushup(fa(x));
    pushup(fa(fa(x)));
    /*printf("root:%d\n",root);
    for(int i=0;i<=cnt;i++)
            printf("%d:val=%d,fa=%d,lson=%d,rson=%d,sum=%d,siz=%d.rev=%d\n",i,tree[i].val,fa(i),ls(i),rs(i),tree[i].sum,tree[i].siz,tree[i].rev);*/
}
inline int get_sum(int pos,int len)
{
    int x=get_range(pos,len);
    return tree[x].sum;
}
inline int max_sum()
{
    pushup(root);
    return tree[root].mmax;
}
void print(int x)
{
    pushdown(x);
    if(ls(x)) print(ls(x));
    printf("%d:val=%d,fa=%d,lmax=%d,rmax=%d,mmax=%d,lson=%d,rson=%d\n",x,tree[x].val,fa(x),tree[x].lmax,tree[x].rmax,tree[x].mmax,ls(x),rs(x));
    if(rs(x)) print(rs(x));
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&tmp[i]);
    insert(1,n);
    /*printf("root:%d\n",root);
    for(int i=1;i<=cnt;i++)
        printf("%d:val=%d,fa=%d,lson=%d,rson=%d,sum=%d,siz=%d\n",i,tree[i].val,fa(i),ls(i),rs(i),tree[i].sum,tree[i].siz);*/
    for(int i=1;i<=m;i++)
    {
        scanf("%s",opt);
        if(opt[0]=='I')
        {
            scanf("%d%d",&_pos,&_len);
            for(int i=1;i<=_len;i++)
                scanf("%d",&tmp[i]);
            insert(_pos,_len);
        }
        if(opt[0]=='D')
        {
            scanf("%d%d",&_pos,&_len);
            del(_pos,_len);
        }
        if(opt[0]=='M'&&opt[2]=='K')
        {
            scanf("%d%d%d",&_pos,&_len,&_val);
            make_same(_pos,_len,_val);
        }
        if(opt[0]=='R')
        {
            scanf("%d%d",&_pos,&_len);
            rev(_pos,_len);
        }
        if(opt[0]=='M'&&opt[2]=='X')
            print(root),
            puts(""),
            printf("%d\n",max_sum());
        if(opt[0]=='G')
        {
            scanf("%d%d",&_pos,&_len);
            printf("%d\n",get_sum(_pos,_len));
        }
        /*print(root);
        puts("");*/
        printf("root:%d\n",root);
        for(int x=1;x<=cnt;x++)
                printf("%d:val=%d,fa=%d,lmax=%d,rmax=%d,mmax=%d,lson=%d,rson=%d\n",x,tree[x].val,fa(x),tree[x].lmax,tree[x].rmax,tree[x].mmax,ls(x),rs(x));
    }
}
