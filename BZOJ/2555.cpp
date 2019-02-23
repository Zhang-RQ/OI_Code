#include<bits/stdc++.h>

using namespace std;

const int MAXN=3E6+10;

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==(x))

struct node_t{
    int son[2],fa,val,tag;
}t[MAXN];

char s[MAXN],op[233];
int rt=1,cnt=1,lst=1,son[MAXN][26],par[MAXN],mx[MAXN],q,mask;

bool isrt(int x){return ls(fa(x))!=x&&rs(fa(x))!=x;}

void pushdown(int x)
{
    if(t[x].tag)
    {
        t[ls(x)].val+=t[x].tag;
        t[ls(x)].tag+=t[x].tag;
        t[rs(x)].val+=t[x].tag;
        t[rs(x)].tag+=t[x].tag;
        t[x].tag=0;
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
    fa(x)=z;fa(y)=x;
    fa(t[y].son[rsx])=y;
}

void splay(int x)
{
    pd(x);
    while(!isrt(x))
    {
        if(!isrt(fa(x))) rotate((rson(x)^rson(fa(x)))?x:fa(x));
        rotate(x);
    }
}

void access(int x)
{
    for(int y=0;x;y=x,x=fa(x))
        splay(x),rs(x)=y;
}

void append(int x)
{
    int p=lst,np=++cnt;
    mx[np]=mx[p]+1;
    while(p&&!son[p][x]) son[p][x]=np,p=par[p];
    if(!p) par[np]=rt,fa(np)=rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q,fa(np)=q;
        else
        {
            int nq=++cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[np]=par[q]=nq;
            memcpy(son[nq],son[q],sizeof son[q]);
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
            access(q);splay(q);
            t[nq].val=t[q].val;
            splay(par[nq]);//par[q]
            fa(q)=nq;rs(nq)=q;
            fa(nq)=par[nq];
            rs(par[nq])=nq;
            fa(np)=nq;
        }
    }
    lst=np;
    access(np);splay(np);
    t[np].val++;t[np].tag++;
}

int main()
{
    scanf("%d",&q);
    scanf("%s",s+1);
    int len=strlen(s+1);
    for(int i=1;i<=len;i++)
        append(s[i]-'A');
    while(q--)
    {
        scanf("%s%s",op+1,s);
        int _mask=mask,len=strlen(s);
        for(int i=0;i<len;i++)
        {
            _mask=(_mask*131+i)%len;
            swap(s[_mask],s[i]);
        }
        if(op[1]=='A')
        {
            for(int i=0;i<len;i++)
                append(s[i]-'A');
        }
        else
        {
            int x=rt;
            for(int i=0;i<len;i++)
                x=son[x][s[i]-'A'];
            if(x==0) puts("0");
            else
            {
                splay(x);
                printf("%d\n",t[x].val);
                mask^=t[x].val;
            }
        }
    }
}
