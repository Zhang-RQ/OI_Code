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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=150010;
int n,m,x,i,j,k,val[50010],tot,arr[MAXN];
struct operation{int t,i,j,k;} op[MAXN];
char opt[10];
namespace President_tree{
    struct node{
        int val,ls,rs;
    }t[MAXN<<3];
    int rt[MAXN],cnt;
    void insert(int &x,int l,int r,int pos,int f)
    {
        if(!x) {x=++cnt;}
        t[x].val+=f;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) insert(t[x].ls,l,mid,pos,f);
        else insert(t[x].rs,mid+1,r,pos,f);
    }
    int query(int x,int l,int r,int ql,int qr)
    {
        if(!x) return 0;
        if(ql<=l&&r<=qr) return t[x].val;
        int mid=(l+r)>>1,ret=0;
        if(ql<=mid) ret+=query(t[x].ls,l,mid,ql,qr);
        if(qr>mid)  ret+=query(t[x].rs,mid+1,r,ql,qr);
        return ret;
    }
}
namespace BIT{
    int query(int pos,int ql,int qr)  //1...pos
    {
        using President_tree::query;
        using President_tree::rt;
        int ret=0;
        for(int i=pos;i>=1;i-=i&-i)
            ret+=query(rt[i],1,tot,ql,qr);
        return ret;
    }
    void insert(int pos,int val,int f)
    {
        using President_tree::insert;
        using President_tree::rt;
        for(int i=pos;i<=n;i+=i&-i)
            insert(rt[i],1,tot,val,f);
    }
    int ask(int l,int r,int ql,int qr,int k)
    {
        if(l==r) return l;
        int mid=(l+r)>>1;
        int lsiz=query(qr,l,mid)-query(ql-1,l,mid);
        // printf("%d~~%d %d %d\n",l,r,k,lsiz);
        if(lsiz<k) return ask(mid+1,r,ql,qr,k-lsiz);
        else return ask(l,mid,ql,qr,k);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]),val[++tot]=arr[i];
    for(int i=1;i<=m;i++)
    {
        scanf("%s",opt+1);
        switch(opt[1])
        {
            case 'Q':scanf("%d%d%d",&op[i].i,&op[i].j,&op[i].k);op[i].t=1;break;
            case 'C':scanf("%d%d",&op[i].i,&op[i].k);op[i].t=2;val[++tot]=op[i].k;break;
        }
    }
    sort(val+1,val+1+tot);
    tot=unique(val+1,val+1+tot)-val-1;
    for(int i=1;i<=n;i++)
        arr[i]=lower_bound(val+1,val+1+tot,arr[i])-val,BIT::insert(i,arr[i],1);
    for(int i=1;i<=m;i++)
        if(op[i].t==2) op[i].k=lower_bound(val+1,val+1+tot,op[i].k)-val;
    for(int i=1;i<=m;i++)
    {
        switch(op[i].t)
        {
            case 1:printf("%d\n",val[BIT::ask(1,tot,op[i].i,op[i].j,op[i].k)]);break;
            case 2:BIT::insert(op[i].i,arr[op[i].i],-1);BIT::insert(op[i].i,op[i].k,1);arr[op[i].i]=op[i].k;break;
        }
    }
}
