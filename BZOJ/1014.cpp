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

const int MAXN=5E5+10;
const ull base=23333333;

ull pw[MAXN];

struct node{
    int son[2],fa,c,siz;
    ull hsh;
}t[MAXN];

int rt,cnt,m,n;
char str[MAXN],s[10];

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==x)

inline void pushup(const int &x)
{
    t[x].siz=t[ls(x)].siz+t[rs(x)].siz+1;
    t[x].hsh=t[ls(x)].hsh*pw[t[rs(x)].siz+1]+t[x].c*pw[t[rs(x)].siz]+t[rs(x)].hsh;
}

inline void rotate(int x)
{
    int y=fa(x),z=fa(y);
    bool rsx=rson(x),rsy=rson(y);
    if(z) t[z].son[rsy]=x;
    else rt=x;
    t[y].son[rsx]=t[x].son[!rsx];
    t[x].son[!rsx]=y;fa(x)=z;
    fa(y)=x;fa(t[y].son[rsx])=y;
    pushup(y);pushup(x);
}

inline void splay(int x,int fa)
{
    while(fa(x)!=fa)
    {
        if(fa(fa(x))!=fa) rotate(rson(x)^rson(fa(x))?x:fa(x));
        rotate(x);
    }
}

void build(int &x,int l,int r)
{
    if(l>r) return;
    x=++cnt;
    int mid=(l+r)>>1;
    t[x].hsh=t[x].c=str[mid],t[x].siz=1;
    if(l==r) return;
    build(ls(x),l,mid-1);build(rs(x),mid+1,r);
    fa(ls(x))=x;fa(rs(x))=x;
    pushup(x);
}

int kth(int x,int k)
{
    if(t[ls(x)].siz+1==k) return x;
    if(t[ls(x)].siz+1<k) return kth(rs(x),k-t[ls(x)].siz-1);
    else return kth(ls(x),k);
}

inline void insert(int c,int pos)
{
    int x=++cnt;
    t[x].hsh=t[x].c=c;t[x].siz=1;
    if(!pos)
    {
        rs(x)=rt;
        fa(rt)=x;
        rt=x;
        pushup(x);
        return;
    }
    int y=kth(rt,pos);
    splay(y,0);
    rs(x)=rs(y);
    fa(rs(x))=x;
    rs(y)=x;fa(x)=y;
    pushup(x);
    pushup(y);
}

inline void change(int c,int pos)
{
    int x=kth(rt,pos);
    splay(x,0);
    t[x].c=c;
    pushup(x);
}

inline ull query(int l,int r)
{
    if(l==1&&r==t[rt].siz) return t[rt].hsh;
    if(l==1)
    {
        splay(kth(rt,r+1),0);
        return t[ls(rt)].hsh;
    }
    if(r==t[rt].siz)
    {
        splay(kth(rt,l-1),0);
        return t[rs(rt)].hsh;
    }
    splay(kth(rt,l-1),0);
    splay(kth(rt,r+1),rt);
    return t[ls(rs(rt))].hsh;
}

inline int LCP(int x,int y)
{
    if(x>y) swap(x,y);
    int L=1,R=t[rt].siz-y+1,ans=0;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(query(x,x+mid-1)==query(y,y+mid-1)) ans=mid,L=mid+1;
        else R=mid-1;
    }
    return ans;
}

int main()
{
    pw[0]=1;
    for(int i=1;i<=100000;i++) pw[i]=pw[i-1]*base;
    scanf("%s",str+1);
    n=strlen(str+1);
    build(rt,1,n);
    scanf("%d",&m);
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%s",s+1);
        if(s[1]=='Q')
        {
            scanf("%d%d",&x,&y);
            printf("%d\n",LCP(x,y));
        }
        else if(s[1]=='R')
        {
            scanf("%d%s",&x,s+1);
            change(s[1],x);
        }
        else if(s[1]=='I')
        {
            scanf("%d%s",&x,s+1);
            insert(s[1],x);
        }
    }
    #ifdef LOCAL
        system("pause");
    #endif
}