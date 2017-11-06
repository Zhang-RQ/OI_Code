%:pragma GCC optimize(2)
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
const int MAXN=4e5+10;
const int  MAXM=8e5+10;
int n,m,t1,t2,t3,opt;
int head[MAXN];
struct Node{
    int v,nxt;
}Edge[MAXM<<1];
int cnte=0;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
struct PQ{
    priority_queue<int> val,delv;
    void pop(int x)
    {
        delv.push(x);
    }
    void push(int x)
    {
        val.push(x);
    }
    int top()
    {
        while(!delv.empty()&&delv.top()==val.top())
            delv.pop(),val.pop();
        return val.empty()?-1:val.top();
    }
}tree[MAXN<<2];
struct section{
    int l,r;
    section(){}
    section(int l,int r):l(l),r(r){}
};
struct data_transfer{
    int x,y,val;
}data[MAXN];
inline bool operator <(section a,section b)
{
    if(a.l!=b.l)
        return a.l<b.l;
    else return a.r<b.r;
}
int son[MAXN],siz[MAXN],top[MAXN],fa[MAXN],dep[MAXN],pos[MAXN];
int cnt=0;
void dfs_1(int x,int father)
{
    siz[x]=1;fa[x]=father;
    dep[x]=dep[fa[x]]+1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x])
            continue;
        dfs_1(v,x);
        siz[x]+=siz[v];
        if(siz[son[x]]<siz[v])
            son[x]=v;
    }
}
void dfs_2(int x,int tp)
{
    pos[x]=++cnt;
    top[x]=tp;
    if(son[x])
        dfs_2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]||v==son[x])
            continue;
        dfs_2(v,v);
    }
}
void update(int x,int l,int r,int ul,int ur,int val,int opt)
{
    if(ul<=l&&r<=ur)
    {
        opt?tree[x].push(val):tree[x].pop(val);
        return;
    }
    int mid=(l+r)>>1;
    if(ul<=mid) update(Ls,ul,ur,val,opt);
    if(ur>mid)  update(Rs,ul,ur,val,opt);
    return;
}
void solve(int x,int y,int val,int opt)
{
    vector<section> v;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        v.push_back(section(pos[top[x]],pos[x]));
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])
        swap(x,y);
    v.push_back(section(pos[y],pos[x]));
    sort(v.begin(),v.end());
    int pnt=1;
    for(int i=0;i<(signed)v.size();pnt=max(pnt,v[i++].r+1))
        if(pnt<v[i].l)
            update(1,1,n,pnt,v[i].l-1,val,opt);
    if(pnt<=n)
        update(1,1,n,pnt,n,val,opt);
}
int query(int x,int l,int r,int pos)
{
    if(l==r)
        return tree[x].top();
    int mid=(l+r)>>1;
    int ret=tree[x].top();
    if(pos<=mid)
        ret=max(ret,query(Ls,pos));
    else ret=max(ret,query(Rs,pos));
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&t1,&t2);
        add(t1,t2);
        add(t2,t1);
    }
    dfs_1(1,0);
    dfs_2(1,1);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&opt);
        if(opt==0)
        {
            scanf("%d%d%d",&data[i].x,&data[i].y,&data[i].val);
            solve(data[i].x,data[i].y,data[i].val,1);
        }
        if(opt==1)
        {
            scanf("%d",&t1);
            solve(data[t1].x,data[t1].y,data[t1].val,0);
        }
        if(opt==2)
        {
            scanf("%d",&t1);
            printf("%d\n",query(1,1,n,pos[t1]));
        }
    }
}
