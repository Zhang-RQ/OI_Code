#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MN 200000
#define INF 1000000000LL
#define eps 1e-4
using namespace std;
inline int read()
{
    int x = 0 , f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1;  ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
double d[MN+5],w[MN+5];
double mid;
vector<int> v[MN+5];
int maxdep,dep[MN+5],size[MN+5],q[MN+5],top=0,mark[MN+5];
int n,low,up,minn,rt,tot,bigrt,cnt=0,head[MN+5],mx[MN+5],rtnum=0;
int root[MN+5];
struct edge{int to,next;double w;}e[MN*2+5];
bool yes,b[MN+5];
struct Queue{
    int hd,tl,n,qx[MN+5];
    void init(int size){hd=-1;tl=0;n=size;}
    void ins(int x)
    {
        if(hd>=tl&&qx[hd]<=x)return;
        if(hd<tl&&x>n)return;
        while(d[x]>=d[qx[hd]]&&hd>=tl) hd--;
        qx[++hd]=x;
    }
    double query(int x)
    {
        while(qx[tl]>x&&hd>=tl)++tl;
        if(hd<tl)return -INF;
        return d[qx[tl]];
    }
}Q;

void ins(int f,int t,int w)
{
    e[++cnt]=(edge){t,head[f],w};head[f]=cnt;
    e[++cnt]=(edge){f,head[t],w};head[t]=cnt;
}

void getrt(int x,int fa)
{
    for(int i=head[x];i;i=e[i].next)
        if(e[i].to!=fa&&!b[e[i].to])
            getrt(e[i].to,x);
    if(max(tot-size[x],size[mx[x]])<minn) {minn=max(tot-size[x],size[mx[x]]);rt=x;}
}

void bfs(int x,int from)
{
    int i,j;mark[x]=from;
    for(q[i=top=1]=x;i<=top;i++)
        for(int j=head[q[i]];j;j=e[j].next)
            if(!b[e[j].to]&&mark[e[j].to]!=from)
                mark[q[++top]=e[j].to]=from;
}

void dfs(int x,int fa)
{
    maxdep=max(maxdep,dep[x]);
    for(int i=head[x];i;i=e[i].next)
        if(e[i].to!=fa&&!b[e[i].to])
        {
            dep[e[i].to]=dep[x]+1;w[e[i].to]=w[x]+(double)e[i].w-mid;
            dfs(e[i].to,x);
        }
}

void pre_dfs(int x,int fa)
{
    size[x]=1;mx[x]=0;
    for(int i=head[x];i;i=e[i].next)
        if(e[i].to!=fa&&!b[e[i].to])
        {
            pre_dfs(e[i].to,x);
            size[x]+=size[e[i].to];
            if(size[e[i].to]>size[mx[x]]) mx[x]=e[i].to;
        }
}

void pre_work(int x)
{
    b[x]=1;
    if(yes)return;int mxdp=0;
    for(int i=head[x];i;i=e[i].next) if(!b[e[i].to])
        pre_dfs(e[i].to,x);
    for(int i=head[x];i;i=e[i].next)
        if(!b[e[i].to])
        {
            tot=size[e[i].to];minn=INF;
            getrt(e[i].to,x);
            root[++rtnum]=rt;pre_work(rt);
        }
}

void solve(int x)
{
    b[x]=1;maxdep=0;
    if(yes)return;int mxdp=0;
    for(int i=head[x];i;i=e[i].next) if(!b[e[i].to])
    {
        maxdep=0;dep[e[i].to]=1;w[e[i].to]=(double)e[i].w-mid;
        dfs(e[i].to,x);
        mxdp=max(mxdp,maxdep);
        v[maxdep].push_back(e[i].to);
    }
    for(int i=1;i<=mxdp;i++)
        for(int j=0;j<v[i].size();j++)
        {
            top=0;bfs(v[i][j],x);Q.init(mxdp);
            int k;for(k=i;k>low-1;k--) Q.ins(k);
            for(k=1;k<=top;k++)
            {
                if(w[q[k]]>=0&&dep[q[k]]>=low&&dep[q[k]]<=up) {yes=true;for(int i=1;i<=mxdp;i++) d[i]=-INF,v[i].clear();return;}
                if(dep[q[k]]>up) break;
                if(dep[q[k]]<low) Q.ins(low-dep[q[k]]);
                if(Q.query(up-dep[q[k]])+w[q[k]]>=0) {yes=true;for(int i=1;i<=mxdp;i++) d[i]=-INF,v[i].clear();return;}
            }
            for(k=1;k<=top;k++)d[dep[q[k]]]=max(d[dep[q[k]]],w[q[k]]);
        }
    for(int i=1;i<=mxdp;i++) d[i]=-INF,v[i].clear();
}

int main()
{
    tot=n=read();low=read();up=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read(),w=read();
        ins(u,v,w);
    }
    for(int i=1;i<=n;i++)d[i]=-INF;
    double l=0,r=1000000;minn=INF;pre_dfs(1,0);getrt(1,0);double ans=0;
    root[++rtnum]=rt;pre_work(rt);
    while(l+eps<=r)
    {
        mid=(l+r)/2.0;yes=false;
        memset(mark,0,sizeof(mark));
        memset(b,0,sizeof(b));
        for(int i=1;i<=n&&!yes;i++)solve(root[i]);
        if(yes) ans=mid,l=mid;
        else r=mid;
    }

    printf("%0.3lf",ans);
    return 0;
}
// #include<cstdio>
// #include<cstring>
// #include<cstdlib>
// #include<cctype>
// #include<cmath>
// #include<iostream>
// #include<algorithm>
// #include<vector>
// #include<set>
// #include<map>
// #include<queue>
// #include<stack>
// #include<cassert>
// typedef long long ll;
// typedef unsigned long long ull;
// using namespace std;
// const int MAXN=1E5+5;
// const int MAXM=2E5+5;
// struct __edge{
//     int nxt,v,w;
// }Edge[MAXM];
// int head[MAXN],cnt_e,L,R;
// inline void add(int u,int v,int w)
// {
//     Edge[++cnt_e].v=v;
//     Edge[cnt_e].nxt=head[u];
//     Edge[cnt_e].w=w;head[u]=cnt_e;
//     Edge[++cnt_e].v=u;
//     Edge[cnt_e].nxt=head[v];
//     Edge[cnt_e].w=w;head[v]=cnt_e;
// }
// namespace Point_Divide_and_Conquer{
//     struct data{
//         int x,fa;
//         data(){}
//         data(int _,int __){x=_;fa=__;}
//     };
//     int siz[MAXN],rt,mx_rt,mxdep[MAXN],tmp[MAXN],top,bfn[MAXN],bfc,dep[MAXN];
//     bool vis[MAXN];
//     double dis[MAXN],mid;
//     queue<data> Q;
//     struct Queue{
//         int hd,tl,n,qx[MAXN+5];
//         void init(int size){hd=-1;tl=0;n=size;}
//         void ins(int x)
//         {
//             if(hd>=tl&&qx[hd]<=x)return;
//             if(hd<tl&&x>n)return;
//             while(dis[x]>=dis[qx[hd]]&&hd>=tl) hd--;
//             qx[++hd]=x;
//         }
//         double query(int x)
//         {
//             while(qx[tl]>x&&hd>=tl)++tl;
//             if(hd<tl) return -666666666;
//             return dis[qx[tl]];
//         }
//     }q;
//     void get_rt(int x,int fa,int sz)
//     {
//         int mx=1;
//         siz[x]=1;
//         for(int i=head[x];i;i=Edge[i].nxt)
//         {
//             int v=Edge[i].v;
//             if(v==fa) continue;
//             get_rt(v,x,sz);
//             siz[x]+=siz[v];
//             mx=max(mx,siz[v]);
//         }
//         mx=max(mx,sz-siz[x]);
//         if(mx>mx_rt) rt=x,mx_rt=mx;
//     }
//     int dfs0(int x,int fa)
//     {
//         int ret=0;
//         for(int i=head[x];i;i=Edge[i].nxt)
//             if(Edge[i].v!=fa&&!vis[Edge[i].v])
//                 ret=max(ret,dfs0(Edge[i].v,x)+1);
//         return mxdep[x]=ret;
//     }
//     void dfs1(int x,int fa,int dep,double ds)
//     {
//         dis[dep]=max(dis[dep],ds);
//         for(int i=head[x];i;i=Edge[i].nxt)
//             if(Edge[i].v!=fa&&!vis[Edge[i].v])
//                 dfs1(Edge[i].v,x,dep+1,ds+Edge[i].w-mid);
//     }
//     void bfs()
//     {
//         bfc=0;
//         while(!Q.empty())
//         {
//             data t=Q.front();Q.pop();
//             bfn[++bfc]=t.x;
//             for(int i=head[t.x];i;i=Edge[i].nxt)
//             {
//                 int v=Edge[i].v;
//                 if(v==t.fa||vis[v]) continue;
//                 Q.push(data(v,t.x));dep[v]=dep[t.x]+1;
//             }
//         }
//     }
//     void __solve(int x)
//     {
//         int xmxdep=dfs0(x,0);
//         memset(dis,0xc2,sizeof(double)*(xmxdep+3));
//         for(int i=head[x];i;i=Edge[i].nxt)
//             if(!vis[Edge[i].v]) tmp[++top]=i;
//         sort(tmp+1,tmp+1+top,[](int i,int j)->bool{return mxdep[Edge[i].v]<mxdep[Edge[j].v];});
//         for(int i=1;i<=top;i++)
//         {
//             int v=Edge[tmp[i]].v;
//             Q.push(data(v,x));dep[v]=1;bfs();
//             for(int j=R-1;j>=L-1;j--)
//             for(int j=1;j<=bfc;j++)
//             {
//
//             }
//         }
//     }
// }
// int main()
// {
//
// }
