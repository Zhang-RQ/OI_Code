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
#define v(i) Edge[i].v
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
using namespace std;
typedef long long ll;
int n;
//graph begin
#define M 100200
#define N 100200
int head[M];
struct Node{
    int val,nxt,v;
}Edge[N<<1];
struct node{
    int u,v,val;
}edge[N];
int cnte=0;
char ops[15];
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
//graph begin
//segtree begin
int tree[M<<2];
void insert(int x,int l,int r,int pos,int val)
{
    if(l==r) {tree[x]=val;return;}
    int mid=(l+r)>>1;
    if(pos<=mid) insert(Ls,pos,val);
    else insert(Rs,pos,val);
    tree[x]=max(tree[x<<1],tree[x<<1|1]);
}
int query(int x,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr) return tree[x];
    if(ql>r||qr<l) return 0;
    int mid=(l+r)>>1;
    return max(query(Ls,ql,qr),query(Rs,ql,qr));
}
//segtree end
//树链剖分 begin
int fa[M],top[M],dfn[M],son[M],siz[M],dep[M],pnt[M];
int cnt=0;
void dfs_1(int x,int father){
    siz[x]=1;
    fa[x]=father;
    dep[x]=dep[father]+1;
    for(int i=head[x];i;i=Edge[i].nxt){
        if(fa[x]==v(i))
            continue;
        dfs_1(v(i),x);
        siz[x]+=siz[v(i)];
        if(siz[v(i)]>siz[son[x]]) son[x]=v(i);
    }
}
void dfs_2(int x,int tp){
    pnt[dfn[x]=++cnt]=x;
    top[x]=tp;
    if(son[x]) dfs_2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
        if(v(i)!=fa[x]&&v(i)!=son[x])
            dfs_2(v(i),v(i));
}
int get_ans(int x,int y){
    int tx=top[x],ty=top[y];
    int ret=0;
    while(tx!=ty){
        if(dep[tx]<dep[ty])
            swap(x,y),swap(tx,ty);
        ret=max(ret,query(1,1,n,dfn[tx],dfn[x]));
        x=fa[tx];
        tx=top[x];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ret=max(query(1,1,n,dfn[x]+1,dfn[y]),ret);
    return ret;
}
//树链剖分 end
int main(){
    int t,x,y;
    scanf("%d",&t);
    while(t--){
        memset(head,0,sizeof(head));
        memset(Edge,0,sizeof(Edge));
        memset(tree,0,sizeof(tree));
        cnte=cnt=0;
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].val);
            add(edge[i].u,edge[i].v,edge[i].val);
            add(edge[i].v,edge[i].u,edge[i].val);
        }
        dfs_1(1,0);
        dfs_2(1,1);
        for(int i=1;i<n;i++){
            if(dep[edge[i].u]>dep[edge[i].v])  swap(edge[i].u,edge[i].v);
            insert(1,1,n,dfn[edge[i].v],edge[i].val);
        }
        while(scanf("%s",ops+1)&&ops[1]!='D')
        {
            scanf("%d%d",&x,&y);
            if(ops[1]=='Q')
                printf("%d\n",get_ans(x,y));
            else insert(1,1,n,dfn[edge[x].v],y);
        }
    }
}
