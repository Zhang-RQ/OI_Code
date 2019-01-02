#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXN=6E5+10;
const int MAXM=2E6+10;

struct _edge{int v,nxt;};

struct Graph{
    int head[MAXN],cnt_e;
    _edge Edge[MAXM];

    int& operator () (int i){return head[i];}
    _edge& operator [] (int i){return Edge[i];}

    void add(int u,int v)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
    }
}G,G1;

queue<int> q;
int ins[MAXN],Mn[MAXN],Mx[MAXN],in[MAXN],a[MAXN];
int st[2][MAXN][20],st2[2][MAXN][20],lg2[MAXN],tn,m;
int t[MAXN],cnt,n,bl[MAXN],SCC,stk[MAXN],top,dfn[MAXN],low[MAXN],dft;

void init2()
{
    for(int i=2;i<=n;i++)
        lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st2[0][i][j]=min(st2[0][i][j-1],st2[0][i+(1<<(j-1))][j-1]),
            st2[1][i][j]=max(st2[1][i][j-1],st2[1][i+(1<<(j-1))][j-1]);
}

void init()
{
    for(int i=1;i<=n;i++) st[0][i][0]=Mn[bl[i]],st[1][i][0]=Mx[bl[i]];
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[0][i][j]=min(st[0][i][j-1],st[0][i+(1<<(j-1))][j-1]),
            st[1][i][j]=max(st[1][i][j-1],st[1][i+(1<<(j-1))][j-1]);
}

int Query(int f,int l,int r)
{
    int len=lg2[r-l+1];
    return f?max(st[f][l][len],st[f][r-(1<<len)+1][len]):min(st[f][l][len],st[f][r-(1<<len)+1][len]);
}

int Query2(int f,int l,int r)
{
    int len=lg2[r-l+1];
    return f?max(st2[f][l][len],st2[f][r-(1<<len)+1][len]):min(st2[f][l][len],st2[f][r-(1<<len)+1][len]);
}

void build(int x,int l,int r)
{
    t[x]=++cnt;
    if(l==r) return G.add(t[x],l),void();
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    G.add(t[x],t[x<<1]);G.add(t[x],t[x<<1|1]);
}

void add(int x,int l,int r,int cl,int cr,int p)
{
    if(cl<=l&&r<=cr) return G.add(p,t[x]),void();
    int mid=(l+r)>>1;
    if(cl<=mid) add(x<<1,l,mid,cl,cr,p);
    if(cr>mid)  add(x<<1|1,mid+1,r,cl,cr,p);
}

void tarjan(int x)
{
    ins[x]=1;
    stk[++top]=x;
    dfn[x]=low[x]=++dft;
    for(int i=G(x);i;i=G[i].nxt)
    {
        int v=G[i].v;
        if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
        else if(ins[v]) low[x]=min(low[x],dfn[v]);
    }
    if(low[x]==dfn[x])
    {
        ++SCC;
        while(stk[top]!=x)
        {
            bl[stk[top]]=SCC;
            ins[stk[top]]=0;
            --top;
        }
        ins[x]=0;
        bl[x]=SCC;--top;
    }
}

int main()
{
    memset(Mn,0x3f,sizeof Mn);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),st2[0][a[i]][0]=st2[1][a[i]][0]=i;
    tn=n-1;cnt=tn;init2();
    build(1,1,tn);
    for(int i=1;i<=tn;i++)
    {
        int l=a[i],r=a[i+1];
        if(l>r) swap(l,r);
        int p1=Query2(0,l,r),p2=max(p1,Query2(1,l,r)-1);
        add(1,1,tn,p1,p2,i);
    }
    for(int i=1;i<=cnt;i++)
        if(!dfn[i]) tarjan(i);
    for(int x=1;x<=cnt;x++)
        for(int i=G(x);i;i=G[i].nxt)
            if(bl[x]!=bl[G[i].v])
                G1.add(bl[G[i].v],bl[x]),in[bl[x]]++;
    for(int i=1;i<n;i++) Mn[bl[i]]=min(Mn[bl[i]],i),Mx[bl[i]]=max(Mx[bl[i]],i);
    for(int i=1;i<=SCC;i++) if(!in[i]) q.push(i);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=G1(x);i;i=G1[i].nxt)
        {
            int v=G1[i].v;
            Mn[v]=min(Mn[v],Mn[x]);
            Mx[v]=max(Mx[v],Mx[x]);
            if(!--in[v]) q.push(v);
        }
    }
    init();
    scanf("%d",&m);
    for(int i=1,l,r;i<=m;i++)
    {
        scanf("%d%d",&l,&r);
        if(l==r) printf("%d %d\n",l,r);
        else printf("%d %d\n",Query(0,l,r-1),Query(1,l,r-1)+1);
    }
}
