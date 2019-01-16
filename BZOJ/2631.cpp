#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const uint P=51061;

int n,q;
char str[233];

struct node_t{
    int son[2],fa;
    uint v,s,tga,tgm,rev,siz;
    node_t(){tgm=v=s=siz=1;}
}t[MAXN];

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==x)

bool isrt(int x){return ls(fa(x))!=x&&rs(fa(x))!=x;}

void pushup(int x) {t[x].s=(t[ls(x)].s+t[rs(x)].s+t[x].v)%P;t[x].siz=(t[ls(x)].siz+t[rs(x)].siz+1)%P;}

void apply_rev(int x)
{
    if(!x) return;
    t[x].rev^=1;
    swap(ls(x),rs(x));
}

void apply_add(int x,int v)
{
    if(!x) return;
    (t[x].tga+=v)%=P;
    (t[x].v+=v)%=P;
    (t[x].s+=v*t[x].siz)%=P;
}

void apply_mul(int x,int v)
{
    if(!x) return;
    (t[x].tgm*=v)%=P;
    (t[x].tga*=v)%=P;
    (t[x].v*=v)%=P;
    (t[x].s*=v)%=P;
}

void pushdown(int x)
{
    if(t[x].rev) apply_rev(ls(x)),apply_rev(rs(x)),t[x].rev=0;
    if(t[x].tgm!=1)
    {
        apply_mul(ls(x),t[x].tgm);
        apply_mul(rs(x),t[x].tgm);
        t[x].tgm=1;
    }
    if(t[x].tga)
    {
        apply_add(ls(x),t[x].tga);
        apply_add(rs(x),t[x].tga);
        t[x].tga=0;
    }
}

void pd(int x){if(!isrt(x)) pd(fa(x));pushdown(x);}

void rotate(int x)
{
    int y=fa(x),z=fa(y);
    bool rsx=rson(x),rsy=rson(y);
    if(!isrt(y)) t[z].son[rsy]=x;
    t[y].son[rsx]=t[x].son[!rsx];
    t[x].son[!rsx]=y;
    fa(y)=x;fa(t[y].son[rsx])=y;fa(x)=z;
    pushup(y);pushup(x);
}

void splay(int x)
{
    pd(x);
    while(!isrt(x))
    {
        if(!isrt(fa(x))) rotate(rson(x)^rson(fa(x))?x:fa(x));
        rotate(x);
    }
}

void access(int x)
{
    for(int y=0;x;y=x,x=fa(x))
        splay(x),rs(x)=y,pushup(x);
}

void makert(int x) {access(x);splay(x);apply_rev(x);}

void Link(int x,int y)
{
    makert(y);
    fa(y)=x;
}

void Cut(int x,int y)
{
    makert(x);access(y);splay(y);
    assert(ls(y)==x);
    ls(y)=fa(x)=0;
}

void Add(int x,int y,int v)
{
    v%=P;
    makert(x);access(y);splay(y);
    apply_add(y,v);
}

void Mul(int x,int y,int v)
{
    v%=P;
    makert(x);access(y);splay(y);
    apply_mul(y,v);
}

uint Query(int x,int y)
{
    makert(x);access(y);splay(y);
    return t[y].s;
}

int main()
{
    t[0].s=t[0].v=t[0].siz=0;
    scanf("%d%d",&n,&q);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        Link(u,v);
    }
    while(q--)
    {
        scanf("%s",str+1);
        int u,v,x,y;
        if(str[1]=='+')
        {
            scanf("%d%d%d",&u,&v,&x);
            Add(u,v,x);
        }
        else if(str[1]=='-')
        {
            scanf("%d%d%d%d",&u,&v,&x,&y);
            Cut(u,v),Link(x,y);
        }
        else if(str[1]=='*')
        {
            scanf("%d%d%d",&u,&v,&x);
            Mul(u,v,x);
        }
        else if(str[1]=='/')
        {
            scanf("%d%d",&u,&v);
            printf("%u\n",Query(u,v));
        }
    }
}