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

const int MAXN=2E5+5;
const int MAXM=4E5+5;

struct __edge{
    int nxt,v,w;
}Edge[MAXM<<1];

int head[MAXN],cnt_e,dis[MAXN],cnt,rt[MAXM],n,m,q,lstans,K,S;
bool vis[MAXN];


char B[1<<27],*SS=B;

inline int read()
{
    int ret=0;
    int w=1;
    char ch=*SS++;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') w=-1;
        ch=*SS++;
    }
    while('0'<=ch&&ch<='9')
        ret=(ret<<3)+(ret<<1),ret+=ch-'0',ch=*SS++;
    return ret*w;
}


inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}

struct dat{int fa,mn,siz;};

struct Eg{
    int u,v,a,l;
    bool operator < (const Eg &rhs) const
    {
        if(a!=rhs.a) return a>rhs.a;
        if(l!=rhs.l) return l<rhs.l;
        if(u!=rhs.u) return u<rhs.u;
        return v<rhs.v;
    }
}E[MAXM],tE;

struct node{
    int l,r;
    dat v;
    inline void clear(){v.fa=v.mn=v.siz=0;l=r=0;}
}t[17010000];

priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;

void Dijkstra()
{
    for(int i=1;i<=n;i++) dis[i]=0x7f7f7f7f;
    memset(vis,0,sizeof vis);
    pq.push(make_pair(0,1));dis[1]=0;
    while(!pq.empty())
    {
        int x=pq.top().second,ds=pq.top().first;
        pq.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[v]>ds+Edge[i].w)
                dis[v]=Edge[i].w+ds,pq.push(make_pair(dis[v],v));
        }
    }
}

void build(int &x,int l,int r)
{
    x=++cnt;
    if(l==r) return t[x].v.fa=l,t[x].v.mn=dis[l],t[x].v.siz=1,void();
    int mid=(l+r)>>1;
    build(t[x].l,l,mid);build(t[x].r,mid+1,r);
}

inline dat query(int x,int l,int r,int pos)
{
    int mid;
    while(l!=r)
    {
        mid=(l+r)>>1;
        if(pos<=mid) r=mid,x=t[x].l;
        else l=mid+1,x=t[x].r;
    }
    return t[x].v;
}

inline void change(int x,int l,int r,int pos,int _x,const dat &rhs)
{
    int mid;
    while(l!=r)
    {
        t[x]=t[_x];
        mid=(l+r)>>1;
        if(pos<=mid) r=mid,x=(t[x].l=++cnt),_x=t[_x].l;
        else l=mid+1,x=(t[x].r=++cnt),_x=t[_x].r;
    }
    t[x].v=rhs;
    assert(cnt<=17010000);
}

inline int find(int x,int tp)
{
    int fa=query(rt[tp],1,n,x).fa;
    return x==fa?x:find(fa,tp);
}

inline void merge(int x,int y,int tp)
{
    x=find(x,tp-1),y=find(y,tp-1);
    dat xx=query(rt[tp-1],1,n,x),yy=query(rt[tp-1],1,n,y);
    if(xx.fa==yy.fa) return rt[tp]=rt[tp-1],void();
    int trt=++cnt;rt[tp]=++cnt;
    if(xx.siz<yy.siz) swap(xx,yy),swap(x,y);
    yy.fa=xx.fa;
    xx.siz+=yy.siz;
    xx.mn=min(xx.mn,yy.mn);
    change(trt,1,n,x,rt[tp-1],xx);
    change(rt[tp],1,n,y,trt,yy);
}

void solve()
{
    memset(head,0,sizeof head);lstans=cnt=cnt_e=0;
    n=read();m=read();
    for(int i=1;i<=m;i++) E[i].u=read(),E[i].v=read(),E[i].l=read(),E[i].a=read(),add(E[i].u,E[i].v,E[i].l),add(E[i].v,E[i].u,E[i].l);
    Dijkstra();
    build(rt[0],1,n);
    sort(E+1,E+1+m);
    for(int i=1;i<=m;i++) merge(E[i].u,E[i].v,i);
    q=read();K=read();S=read();
    for(int i=1,v,p,R;i<=q;i++)
    {
        v=read();p=read();
        v=(1ll*v+K*lstans-1)%n+1;
        p=(1ll*p+K*lstans)%(S+1);
        tE.a=p;
        R=upper_bound(E+1,E+1+m,tE)-E-1;
        int fafa=find(v,R);
        lstans=query(rt[R],1,n,fafa).mn;
        printf("%d\n",lstans);
    }
}

int main()
{
    fread(B,1,1<<27,stdin);
    int T;
    for(T=read();T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}