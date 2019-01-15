//君の名は
#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E6+10;

struct node_t{
    int l,r,v;
}t[MAXN*20];

char s[MAXN];
int cnt,Rt[MAXN],n,q,len[MAXN];

void insert(int &x,int l,int r,int p)
{
    if(!x) x=++cnt;
    t[x].v++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(p<=mid) insert(t[x].l,l,mid,p);
    else insert(t[x].r,mid+1,r,p);
}

int merge(int x,int y)
{
    if(!x||!y) return x|y;
    int z=++cnt;
    t[z].v=t[x].v+t[y].v;
    t[z].l=merge(t[x].l,t[y].l);
    t[z].r=merge(t[x].r,t[y].r);
    return z;
}

int query(int x,int l,int r,int ql,int qr)
{
    if(!x) return 0;
    if(ql<=l&&r<=qr) return t[x].v;
    int mid=(l+r)>>1;
    if(qr<=mid) return query(t[x].l,l,mid,ql,qr);
    else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr);
    else return query(t[x].l,l,mid,ql,qr)+query(t[x].r,mid+1,r,ql,qr);
}

struct SAM{
    int ord[MAXN],buk[MAXN];
    int son[MAXN][26],par[MAXN],mx[MAXN],pos[MAXN],lst,rt,cnt;

    SAM(){rt=cnt=lst=1;}

    void clear()
    {
        for(int i=1;i<=cnt;i++) memset(son[i],0,sizeof son[i]),pos[i]=par[i]=mx[i]=0;
        lst=rt=cnt=1;
    }

    void append(int x,bool f)
    {
        x-='a';
        int p=lst,np=++cnt;
        mx[np]=mx[p]+1;pos[np]=mx[np];
        if(f) insert(Rt[np],1,n,mx[np]);
        while(p&&!son[p][x]) son[p][x]=np,p=par[p];
        if(!p) par[np]=rt;
        else
        {
            int q=son[p][x];
            if(mx[q]==mx[p]+1) par[np]=q;
            else
            {
                int nq=++cnt;
                mx[nq]=mx[p]+1;
                par[nq]=par[q];
                par[np]=par[q]=nq;
                memcpy(son[nq],son[q],sizeof son[q]);
                while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
            }
        }
        lst=np;
    }

    void topo(bool f)
    {
        int Mx=0;
        for(int i=1;i<=cnt;i++) Mx=max(Mx,mx[i]),buk[mx[i]]++;
        for(int i=1;i<=Mx;i++) buk[i]+=buk[i-1];
        for(int i=cnt;i;i--) ord[buk[mx[i]]--]=i;
        for(int i=cnt;i;i--)
        {
            int p=ord[i];
            if(!pos[par[p]]) pos[par[p]]=pos[p];
            else pos[par[p]]=min(pos[par[p]],pos[p]);
            if(f) Rt[par[p]]=merge(Rt[par[p]],Rt[p]);
        }
        for(int i=1;i<=Mx;i++) buk[i]=0;
    }
}S,T;

int main()
{
    freopen("name.in","r",stdin);
    freopen("name.out","w",stdout);
    scanf("%s%d",s+1,&q);
    n=strlen(s+1);
    for(int i=1;i<=n;i++) S.append(s[i],1);
    S.topo(1);
    while(q--)
    {
        int l,r,m;ll Ans=0;
        scanf("%s%d%d",s+1,&l,&r);
        m=strlen(s+1);
        T.clear();
        for(int i=1;i<=m;i++) T.append(s[i],0);
        T.topo(0);
        int x=S.rt,ln=0;
        for(int i=1;i<=m;i++)
        {
            int c=s[i]-'a';
            while(x!=S.rt)
            {
                if(S.son[x][c]&&query(Rt[S.son[x][c]],1,n,l+ln,r)) break;
                else if(!S.son[x][c])  x=S.par[x],ln=S.mx[x];
                else  if(--ln==S.mx[S.par[x]]) x=S.par[x];
            }
            if(S.son[x][c]&&query(Rt[S.son[x][c]],1,n,l+ln,r))
                x=S.son[x][c],ln++;
            else x=S.rt,ln=0;
            len[i]=ln;
        }
        for(int i=2;i<=T.cnt;i++)
            Ans+=max(0,T.mx[i]-max(T.mx[T.par[i]],len[T.pos[i]]));
        printf("%lld\n",Ans);
    }
}