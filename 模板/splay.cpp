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

const int MAXN=1E5+10;

struct node{
    int son[2],fa,v,siz,tms;
}t[MAXN];

int Rt,cnt,n;

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==x)

int nd(int val)
{
    ++cnt;
    t[cnt].v=val;t[cnt].siz=t[cnt].tms=1;
    return cnt;
}

void pushup(int x) {t[x].siz=t[ls(x)].siz+t[rs(x)].siz+t[x].tms;}

void rotate(int x)
{
    int y=fa(x),z=fa(y);
    bool rsx=rson(x),rsy=rson(y);
    if(z) t[z].son[rsy]=x;
    else Rt=x;
    t[y].son[rsx]=t[x].son[!rsx];
    t[x].son[!rsx]=y;
    fa(t[y].son[rsx])=y;fa(y)=x;fa(x)=z;
    pushup(y);
}

void splay(int x)
{
    while(fa(x))
    {
        if(fa(fa(x))) rotate(rson(x)^rson(fa(x))?x:fa(x));
        rotate(x);
    }
    pushup(x);
}

int find(int x,int val) //return node
{
    if(t[x].v==val) return x;
    if(t[x].v<val) return rs(x)?find(rs(x),val):x;
    else return ls(x)?find(ls(x),val):x;
}

int Pred(int x) //return node
{
    splay(x);
    x=ls(x);
    while(rs(x)) x=rs(x);
    return x;
}

int Succ(int x) //return node
{
    splay(x);
    x=rs(x);
    while(ls(x)) x=ls(x);
    return x;
}

void insert(int val)
{
    if(!Rt) return Rt=nd(val),void();
    int x=find(Rt,val);
    if(t[x].v==val) return splay(x),++t[x].tms,++t[x].siz,void();
    int z=nd(val);
    t[x].son[val>t[x].v]=z;
    fa(z)=x;
    while(x) pushup(x),x=fa(x);
    splay(z);
}

void erase(int val)
{
    int x=find(Rt,val);
    if(t[x].tms>1) return splay(x),--t[x].tms,--t[x].siz,void();
    splay(x);
    if(rs(x))
    {
        int y=Succ(x);
        fa(rs(x))=0;
        splay(y);Rt=y;
        ls(Rt)=ls(x);
        fa(ls(Rt))=Rt;
        pushup(Rt);
    }
    else
    {
        fa(ls(x))=0;
        Rt=ls(x);
    }
}

int Rank(int val)
{
    int x=find(Rt,val);
    if(t[x].v<val)  x=Succ(x);
    splay(x);
    return t[ls(x)].siz+1;
}

int kth(int x,int k)//return val
{
    if(t[ls(x)].siz+1<=k&&k<=t[ls(x)].siz+t[x].tms) return t[x].v;
    if(t[ls(x)].siz+t[x].tms>k) return kth(ls(x),k);
    else return kth(rs(x),k-t[x].tms-t[ls(x)].siz);
}

int Pred_val(int val) //return val
{
    int x=find(Rt,val);
    if(t[x].v<val) return t[x].v;
    return t[Pred(x)].v;
}

int Succ_val(int val) //return val
{
    int x=find(Rt,val);
    if(t[x].v>val) return t[x].v;
    return t[Succ(x)].v;
}

int main()
{
    scanf("%d",&n);
    for(int i=1,opt,x;i<=n;i++)
    {
        scanf("%d%d",&opt,&x);
        if(opt==1) insert(x);
        else if(opt==2) erase(x);
        else if(opt==3) printf("%d\n",Rank(x));
        else if(opt==4) printf("%d\n",kth(Rt,x));
        else if(opt==5) printf("%d\n",Pred_val(x));
        else if(opt==6) printf("%d\n",Succ_val(x));
    }
}