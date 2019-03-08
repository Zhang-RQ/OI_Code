#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=5E5+10;
const int MAXL=2E5+10;

struct dat{
    dat(int _=0,int __=0){mx=_;pos=__;}
    int mx,pos;
    bool operator < (const dat &rhs) const {return mx<rhs.mx||(mx==rhs.mx&&pos>rhs.pos);}
};

struct node_t{
    int l,r;
    dat v;
}t[MAXN*60];

char s[MAXN],str[MAXN];
int rt[MAXN],n,cnt,son[MAXL][26],par[MAXL],mx[MAXL],nd[MAXN],len[MAXN];
int Rt=1,Lst=1,Cnt=1,m,q,jmp[MAXL][19];
vector<int> T[MAXL];

void pushup(int x) {t[x].v=max(t[t[x].l].v,t[t[x].r].v);}

void insert(int &x,int l,int r,int p)
{
    if(!x) x=++cnt;
    if(l==r) return t[x].v.mx++,t[x].v.pos=p,void();
    int mid=(l+r)>>1;
    if(p<=mid) insert(t[x].l,l,mid,p);
    else insert(t[x].r,mid+1,r,p);
    pushup(x);
}

int merge(int x,int y,int l,int r)
{
    if(!x||!y) return x|y;
    if(l==r)
    {
        int z=++cnt;
        t[z].v.mx=t[x].v.mx+t[y].v.mx;
        t[z].v.pos=l;
        return z;
    }
    int z=++cnt,mid=(l+r)>>1;
    t[z].l=merge(t[x].l,t[y].l,l,mid);
    t[z].r=merge(t[x].r,t[y].r,mid+1,r);
    pushup(z);
    return z;
}

dat query(int x,int l,int r,int ql,int qr)
{
    if(!x) return dat(0,0);
    if(ql<=l&&r<=qr) return t[x].v;
    int mid=(l+r)>>1;
    if(qr<=mid) return query(t[x].l,l,mid,ql,qr);
    else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr);
    else return max(query(t[x].l,l,mid,ql,qr),query(t[x].r,mid+1,r,ql,qr));
}

void append(int x,int id)
{
    x-='a';
    int p=Lst,np=++Cnt;
    mx[np]=mx[p]+1;
    insert(rt[np],1,m,id);
    while(p&&!son[p][x]) son[p][x]=np,p=par[p];
    if(!p) par[np]=Rt;
    else
    {
        int q=son[p][x];
        if(mx[q]==mx[p]+1) par[np]=q;
        else
        {
            int nq=++Cnt;
            mx[nq]=mx[p]+1;
            par[nq]=par[q];
            par[q]=par[np]=nq;
            memcpy(son[nq],son[q],sizeof son[nq]);
            while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
        }
    }
    Lst=np;
}

void dfs(int x)
{
    for(int v:T[x])
        dfs(v),rt[x]=merge(rt[x],rt[v],1,m);
}

int main()
{
    scanf("%s%d",s+1,&m);
    n=strlen(s+1);
    for(int _=1;_<=m;_++)
    {
        Lst=1;
        scanf("%s",str+1);
        for(int i=1;str[i];i++)
            append(str[i],_);
    }
    for(int i=2;i<=Cnt;i++)
    {
        jmp[i][0]=par[i];
        T[par[i]].push_back(i);
    }
    dfs(Rt);
    for(int j=1;j<=18;j++)
        for(int i=1;i<=Cnt;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
    int x=Rt,l=0;
    for(int i=1;i<=n;i++)
    {
        while(x!=Rt&&!son[x][s[i]-'a']) x=par[x],l=mx[x];
        if(son[x][s[i]-'a']) x=son[x][s[i]-'a'],++l;
        nd[i]=x,len[i]=l;
    }
    scanf("%d",&q);
    for(int i=1,l,r,pl,pr;i<=q;i++)
    {
        scanf("%d%d%d%d",&l,&r,&pl,&pr);
        int x=nd[pr],len_cur=pr-pl+1;
        if(len[pr]<len_cur) printf("%d %d\n",l,0);
        else
        {
            for(int j=18;~j;j--)
                if(mx[jmp[x][j]]>=len_cur)
                    x=jmp[x][j];
            dat p=query(rt[x],1,m,l,r);
            if(p.mx==0) printf("%d %d\n",l,0);
            else printf("%d %d\n",p.pos,p.mx);
        }
    }
}
