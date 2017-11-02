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
    #define MAXM 200010
    #define MAXN 30010
    #define Ls x<<1,l,mid
    #define Rs x<<1|1,mid+1,r
    int head[MAXN];
    int arr[MAXN];
    int n,q,t1,t2;
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
    int son[MAXN],dep[MAXN],pos[MAXN],siz[MAXN],fa[MAXN],top[MAXN];
    int cnt=0;
    int x,y;
    char ops[20];
    void dfs_1(int x,int father)
    {
        fa[x]=father;
        dep[x]=dep[fa[x]]+1;
        siz[x]=1;
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
    struct node{
        int sum,mx;
    }tree[MAXN<<2];
    inline void pushup(int x)
    {
        tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;
        tree[x].mx=max(tree[x<<1].mx,tree[x<<1|1].mx);
        return;
    }
    void build(int x,int l,int r)
    {
        if(l==r)  {tree[x].sum=tree[x].mx=arr[l];return;}
        int mid=(l+r)>>1;
        build(Ls);
        build(Rs);
        pushup(x);
        return;
    }
    void change(int x,int l,int r,int pos,int val)
    {
        if(l==r) {tree[x].sum=tree[x].mx=val;return;}
        int mid=(l+r)>>1;
        if(pos<=mid) change(Ls,pos,val);
        else change(Rs,pos,val);
        pushup(x);
        return;
    }
    int query_sum(int x,int l,int r,int ql,int qr)
    {
        if(ql<=l&&r<=qr)    return tree[x].sum;
        int mid=(l+r)>>1;
        int ret=0;
        if(ql<=mid)    ret+=query_sum(Ls,ql,qr);
        if(qr>mid)     ret+=query_sum(Rs,ql,qr);
        return ret;
    }
    int query_max(int x,int l,int r,int ql,int qr)
    {
        if(ql<=l&&r<=qr)    return tree[x].mx;
        int  mid=(l+r)>>1;
        int ret=0xcfcfcfcf;
        if(ql<=mid) ret=max(ret,query_max(Ls,ql,qr));
        if(qr>mid)  ret=max(ret,query_max(Rs,ql,qr));
        return ret;
    }
    int path_sum(int x,int y)
    {
        int ret=0;
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]])
                swap(x,y);
            ret+=query_sum(1,1,n,pos[top[x]],pos[x]);
            x=fa[top[x]];
        }
        if(dep[x]<dep[y])
            swap(x,y);
        ret+=query_sum(1,1,n,pos[y],pos[x]);
        return ret;
    }
    int path_max(int x,int y)
    {
        int ret=0xcfcfcfcf;
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]])
                swap(x,y);
            ret=max(ret,query_max(1,1,n,pos[top[x]],pos[x]));
            x=fa[top[x]];
        }
        if(dep[x]<dep[y])
            swap(x,y);
        ret=max(ret,query_max(1,1,n,pos[y],pos[x]));
        return ret;
    }
    int main()
    {
        scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&t1,&t2);
            add(t1,t2);
            add(t2,t1);
        }
        dfs_1(1,0);
        dfs_2(1,1);
        for(int i=1;i<=n;i++)
            scanf("%d",&arr[pos[i]]);
        build(1,1,n);
        scanf("%d",&q);
        for(int i=1;i<=q;i++)
        {
            scanf("%s%d%d",ops+1,&x,&y);
            if(ops[1]=='C')
                change(1,1,n,pos[x],y);
            else if(ops[2]=='M')
                printf("%d\n",path_max(x,y));
            else if(ops[2]=='S')
                printf("%d\n",path_sum(x,y));
        }
    }
