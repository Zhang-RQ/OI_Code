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
const int MAXN=5E4+5;
struct Query{
    int opt,l,r,val,id;
}Q[MAXN];
int tp[MAXN],tl[MAXN],tr[MAXN],n,m,ans[MAXN];
ll t[MAXN<<3],tag[MAXN<<3];
bool cls[MAXN<<3];
void pushup(int x)
{
    t[x]=t[x<<1]+t[x<<1|1];
}
void pushdown(int x,int l,int r)
{
    if(cls[x])
    {
        cls[x]=0;
        t[x<<1]=t[x<<1|1]=0;
        tag[x<<1]=tag[x<<1|1]=0;
        cls[x<<1]=cls[x<<1|1]=1;
    }
    if(tag[x])
    {
        int mid=(l+r)>>1;
        t[x<<1]+=tag[x]*(mid-l+1);
        t[x<<1|1]+=tag[x]*(r-mid);
        tag[x<<1]+=tag[x];
        tag[x<<1|1]+=tag[x];
        tag[x]=0;
    }
}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&r<=cr) {tag[x]+=val;t[x]+=val*(r-l+1);return;}
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
    if(cr>mid) change(x<<1|1,mid+1,r,cl,cr,val);
    pushup(x);
}
ll query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return t[x];
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    ll ret=0;
    if(ql<=mid) ret+=query(x<<1,l,mid,ql,qr);
    if(qr>mid) ret+=query(x<<1|1,mid+1,r,ql,qr);
    return ret;
}
void solve(int l,int r,int L,int R)  //L~R 操作范围  l~r 答案范围
{
    //printf("%d %d %d %d\n",l,r,L,R);
    if(l==r)
    {
        for(int i=L;i<=R;i++)
            ans[Q[tp[i]].id]=l;
        return;
    }
    int mid=(l+r)>>1;
    bool fl=0,fr=0;
    int cnl=0,cnr=0;
    cls[1]=1;t[1]=tag[1]=0;
    for(int i=L;i<=R;i++)
        if(Q[tp[i]].opt==1)
        {
            if(Q[tp[i]].val>mid) change(1,1,n,Q[tp[i]].l,Q[tp[i]].r,1),tr[++cnr]=tp[i];
            else tl[++cnl]=tp[i];
        }
        else
        {
            ll tval=query(1,1,n,Q[tp[i]].l,Q[tp[i]].r);
            if(tval>=Q[tp[i]].val) tr[++cnr]=tp[i],fr=1;
            else Q[tp[i]].val-=tval,tl[++cnl]=tp[i],fl=1;
        }
    for(int i=1;i<=cnl;i++)
        tp[i+L-1]=tl[i];
    for(int i=1;i<=cnr;i++)
        tp[L+cnl+i-1]=tr[i];
    if(fl) solve(l,mid,L,L+cnl-1);
    if(fr) solve(mid+1,r,L+cnl,R);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d%d",&Q[i].opt,&Q[i].l,&Q[i].r,&Q[i].val),Q[i].id=i,tp[i]=i;
    solve(-n,n,1,m);
    for(int i=1;i<=m;i++)
        if(Q[i].opt==2)
            printf("%d\n",ans[i]);
}
