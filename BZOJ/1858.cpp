#include <cstdio>
#include <iostream>
#include <cmath>
#include <stack>
#include <algorithm>
#include <cstring>
#include <climits>
#define MAXN (100000+10)
using namespace std;
int n,m,l0[MAXN<<2],r0[MAXN<<2],m0[MAXN<<2];
int l1[MAXN<<2],r1[MAXN<<2],m1[MAXN<<2],mark[MAXN<<2],rev[MAXN<<2],num[MAXN<<2];
int L[MAXN<<2],R[MAXN<<2],a[MAXN];
void pushup(int rt)
{
    l1[rt]=l1[rt<<1];r1[rt]=r1[rt<<1|1];
    l0[rt]=l0[rt<<1];r0[rt]=r0[rt<<1|1];
    if(l1[rt]==R[rt<<1]-L[rt<<1]+1) l1[rt]+=l1[rt<<1|1];
    if(r1[rt]==R[rt<<1|1]-L[rt<<1|1]+1) r1[rt]+=r1[rt<<1];
    if(l0[rt]==R[rt<<1]-L[rt<<1]+1) l0[rt]+=l0[rt<<1|1];
    if(r0[rt]==R[rt<<1|1]-L[rt<<1|1]+1) r0[rt]+=r0[rt<<1];
    m1[rt]=max(max(m1[rt<<1],m1[rt<<1|1]),l1[rt<<1|1]+r1[rt<<1]);
    m0[rt]=max(max(m0[rt<<1],m0[rt<<1|1]),l0[rt<<1|1]+r0[rt<<1]);
    num[rt]=num[rt<<1]+num[rt<<1|1];
}
void pushdown(int rt,int l,int r)
{
    if(mark[rt]!=-1||rev[rt])
    {
        int m=(l+r)>>1;
        if(l==r) return ;
        else
        {
            if(mark[rt]!=-1)
            {
                mark[rt<<1]=mark[rt<<1|1]=mark[rt];
                r1[rt<<1]=l1[rt<<1]=m1[rt<<1]=num[rt<<1]=mark[rt]*(m-l+1);
                r1[rt<<1|1]=l1[rt<<1|1]=m1[rt<<1|1]=num[rt<<1|1]=mark[rt]*(r-m);
                r0[rt<<1]=l0[rt<<1]=m0[rt<<1]=!mark[rt]*(m-l+1);
                r0[rt<<1|1]=l0[rt<<1|1]=m0[rt<<1|1]=!mark[rt]*(r-m);
                rev[rt<<1]=rev[rt<<1|1]=0;
            }
            if(rev[rt]==1)
            {
                num[rt<<1]=(m-l+1)-num[rt<<1];
                num[rt<<1|1]=(r-m)-num[rt<<1|1];
                swap(r1[rt<<1],r0[rt<<1]);
                swap(r1[rt<<1|1],r0[rt<<1|1]);
                swap(l1[rt<<1],l0[rt<<1]);
                swap(l1[rt<<1|1],l0[rt<<1|1]);
                swap(m1[rt<<1],m0[rt<<1]);
                swap(m1[rt<<1|1],m0[rt<<1|1]);
                rev[rt<<1]^=rev[rt];
                rev[rt<<1|1]^=rev[rt];
            }
        }
        rev[rt]=0;mark[rt]=-1;
    }
}
void build(int rt,int l,int r)
{
    mark[rt]=-1;L[rt]=l;R[rt]=r;
    if(l==r)
    {
        l1[rt]=m1[rt]=r1[rt]=num[rt]=a[l];
        l0[rt]=m0[rt]=r0[rt]=!a[l];
        return ;
    }
    int m=(l+r)>>1;
    build(rt<<1,l,m);
    build(rt<<1|1,m+1,r);
    pushup(rt);
}
void update(int L,int R,int c,int l,int r,int rt)
{
    pushdown(rt,l,r);
    if(L<=l&&r<=R)
    {
        if(c<2)
        {
            r1[rt]=l1[rt]=m1[rt]=num[rt]=c*(r-l+1);
            r0[rt]=l0[rt]=m0[rt]=(!c)*(r-l+1);
            mark[rt]=c;
        }else
        {
            swap(r1[rt],r0[rt]);swap(l1[rt],l0[rt]);swap(m1[rt],m0[rt]);
            num[rt]=(r-l+1)-num[rt];
            rev[rt]^=1;
        }
        return ;
    }
    int m=(l+r)>>1;
    if(L<=m) update(L,R,c,l,m,rt<<1);
    if(R>m) update(L,R,c,m+1,r,rt<<1|1);
    pushup(rt);
}
int query(int L,int R,int v,int l,int r,int rt,int &ln,int &rn)
{
    if(L<=l&&r<=R)
    {
        ln=l1[rt];rn=r1[rt];
        return v?m1[rt]:num[rt];
    }
    int m=(l+r)>>1,lans=0,rans=0,aans=0,ln1=0,rn1=0,ln2=0,rn2=0;

    pushdown(rt,l,r);

    if(L<=m) lans=query(L,R,v,l,m,rt<<1,ln1,rn1),aans+=rn1;
    if(R>m) rans=query(L,R,v,m+1,r,rt<<1|1,ln2,rn2),aans+=ln2;
    if(v)
    {
        ln=ln1;if(ln1==m-l+1) ln+=ln2;
        rn=rn2;if(rn2==r-m) rn+=rn1;
        return max(max(lans,rans),aans);
    }
    else return lans+rans;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(1,1,n);
    int x,b,c,t1,t2;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&b,&c);
        b++,c++;
        if(x<=2) update(b,c,x,1,n,1);
        else
        if(x==3) printf("%d\n",query(b,c,0,1,n,1,t1,t2));
        else if(x==4) printf("%d\n",query(b,c,1,1,n,1,t1,t2));
    }
    return 0;
}
/*#include<cstdio>
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
#define MAXN 100010
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
struct node{
    int l,r;
    int L0,L1,R0,R1,M0,M1;
    int cnt0,cnt1;
    bool all[2];
    bool tag[2],tag_r;
}tree[MAXN<<2];
int arr[MAXN];
inline node merge(const node &a,const node &b)
{
    node ret;
    ret.l=a.l;ret.r=b.r;
    if(a.all[0]&&b.all[0])
        ret.all[0]=1;
    else ret.all[0]=0;
    if(a.all[1]&&b.all[1])
        ret.all[1]=1;
    else ret.all[1]=0;
    /////////////////////////////////////////////
    if(a.all[0])
        ret.L0=a.cnt0+b.L0;
    else ret.L0=a.L0;
    if(a.all[1])
        ret.L1=a.cnt1+b.L1;
    else ret.L1=a.L1;
    /////////////////////////////////////////////
    if(b.all[0])
        ret.R0=b.cnt0+a.R0;
    else ret.R0=b.R0;
    if(b.all[1])
        ret.R1=b.cnt1+a.R1;
    else ret.R1=b.R1;
    /////////////////////////////////////////////
    ret.M0=max(a.M0,max(b.R0,a.R0+b.L0));
    ret.M1=max(a.M1,max(b.M1,a.R1+b.L1));
    ret.cnt0=a.cnt0+b.cnt0;
    ret.cnt1=a.cnt1+b.cnt1;
    return ret;
}
inline void pushup(int x)
{
    tree[x]=merge(tree[x<<1],tree[x<<1|1]);
    return;
}
inline void color(int x,int l,int r,int c)
{
    if(c==0)
    {
        tree[x].L0=tree[x].R0=tree[x].M0=tree[x].cnt0=r-l+1;
        tree[x].L1=tree[x].R1=tree[x].M1=tree[x].cnt1=0;
        tree[x].all[0]=1;tree[x].all[1]=0;
    }
    else
    {
        tree[x].L1=tree[x].R1=tree[x].M1=tree[x].cnt1=r-l+1;
        tree[x].L0=tree[x].R0=tree[x].M0=tree[x].cnt0=0;
        tree[x].all[1]=1;tree[x].all[0]=0;
    }
    return;
}
inline void rev(int x)
{
    swap(tree[x].L0,tree[x].L1);swap(tree[x].R0,tree[x].R1);
    swap(tree[x].M0,tree[x].M1);swap(tree[x].cnt0,tree[x].cnt1);
    swap(tree[x].all[0],tree[x].all[1]);
    return;
}
inline void pushdown(int x,int l,int r)
{
    if(l==r) return;
    int mid=(l+r)>>1;
    if(tree[x].tag[0])
    {
        tree[x<<1].tag_r=tree[x<<1|1].tag_r=0;
        tree[x<<1].tag[0]^=1;tree[x<<1|1].tag[0]^=1;
        color(Ls,0);color(Rs,0);
        tree[x].tag[0]=0;
    }
    if(tree[x].tag[1])
    {
        tree[x<<1].tag_r=tree[x<<1|1].tag_r=0;
        tree[x<<1].tag[1]^=1;tree[x<<1|1].tag[1]^=1;
        color(Ls,1);color(Rs,1);
        tree[x].tag[1]=0;
    }
    if(tree[x].tag_r)
    {
        tree[x<<1].tag_r^=1;tree[x<<1|1].tag_r^=1;
        rev(x<<1);rev(x<<1|1);
    }
    pushup(x);
}
void build(int x,int l,int r)
{
    tree[x].l=l;tree[x].r=r;
    if(l==r)
    {
        if(arr[l]) tree[x].cnt1=tree[x].L1=tree[x].R1=tree[x].M1=tree[x].all[1]=1;
        else tree[x].cnt0=tree[x].L0=tree[x].R0=tree[x].M0=tree[x].all[0]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(Ls);build(Rs);
    pushup(x);
    return;
}
void change(int x,int l,int r,int cl,int cr,int c)
{
    pushdown(x,l,r);
    if(cl<=l&&r<=cr) {color(x,l,r,c);tree[x].tag[c]=1;return;}
    int mid=(l+r)>>1;
    if(cr>mid) change(Rs,cl,cr,c);
    if(cl<=mid) change(Ls,cl,cr,c);
    pushup(x);
    return;
}
int query(int x,int l,int r,int ql,int qr)
{
    pushdown(x,l,r);
    if(ql<=l&&r<=qr) return tree[x].cnt1;
    int mid=(l+r)>>1;
    int ret=0;
    if(qr>mid) ret+=query(Rs,ql,qr);
    if(ql<=mid) ret+=query(Ls,ql,qr);
    return ret;
}
node querymax(int x,int l,int r,int ql,int qr)
{
    pushdown(x,l,r);
    if(ql<=l&&r<=qr) return tree[x];
    int mid=(l+r)>>1;
    if(qr<=mid) return querymax(Ls,ql,qr);
    if(ql>mid) return querymax(Rs,ql,qr);
    node tl,tr,ret;
    tl=querymax(Ls,ql,qr);tr=querymax(Rs,ql,qr);
    ret.l=tl.l;ret.r=tr.r;
    if(tl.r+1==tr.l) ret=merge(tl,tr);
    else
    {
        ret.L1=tl.L1;ret.R1=tr.R1;
        ret.M1=max(tl.M1,tr.M1);
    }
    return ret;
}
void reverse(int x,int l,int r,int rl,int rr)
{
    if(rl<=l&&r<=rr)
    {
        rev(x);
        tree[x].tag_r=1;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    if(rr>mid) reverse(Rs,rl,rr);
    if(rl<=mid) reverse(Ls,rl,rr);
    pushup(x);
    return;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]);
    build(1,1,n);
    int ops,a,b;
    for(int i=1;i<=n<<2;i++)
        if(tree[i].l!=0&&tree[i].r!=0)
            printf("%d:[%d,%d]:L1:%d,R1:%d,M1:%d\n",i,tree[i].l,tree[i].r,tree[i].L1,tree[i].R1,tree[i].M1);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&ops,&a,&b);
        a++;b++;
        switch(ops)
        {
            case 0: change(1,1,n,a,b,0);break;
            case 1: change(1,1,n,a,b,1);break;
            case 2: reverse(1,1,n,a,b);break;
            case 3: printf("%d\n",query(1,1,n,a,b));break;
            case 4: printf("%d\n",querymax(1,1,n,a,b).M1);break;
        }
        for(int i=1;i<=n;i++)
            printf("%d ",query(1,1,n,i,i));
        puts("");
        for(int i=1;i<=n<<2;i++)
            if(tree[i].l!=0&&tree[i].r!=0)
                printf("%d:[%d,%d]:L1:%d,R1:%d,M1:%d,all0:%d,all1:%d\n",i,tree[i].l,tree[i].r,tree[i].L1,tree[i].R1,tree[i].M1,tree[i].all[0],tree[i].all[1]);
    }
}
*/
