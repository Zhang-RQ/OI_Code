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
const int INF=0x3f3f3f3f;
const int MAXN=50010;
struct Matrix{
    int a[4];
    Matrix(){memset(a,0xcf,sizeof a);}
    inline int& operator [](int i) {return a[i];}
    inline Matrix operator * (const Matrix &rhs) const
    {
        Matrix ret;
        ret[0]=a[0]+rhs.a[0];
        ret[1]=max(a[0]+rhs.a[1],a[1]);
        ret[2]=max(a[2]+rhs.a[0],rhs.a[2]);
        ret[3]=max(a[2]+rhs.a[1],max(a[3],rhs.a[3]));
        return ret;
    }
}t[MAXN<<2];
int val[MAXN],n,m,opt,x,y;
inline void pushup(int x){t[x]=t[x<<1]*t[x<<1|1];}
void build(int x,int l,int r)
{
    if(l==r)
    {
        t[x][0]=t[x][1]=t[x][2]=t[x][3]=val[l];
        return;
    }
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    pushup(x);
}
void change(int x,int l,int r,int pos,int val)
{
    if(l==r)
    {
        t[x][0]=t[x][1]=t[x][2]=t[x][3]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid) change(x<<1,l,mid,pos,val);
    if(pos>mid)  change(x<<1|1,mid+1,r,pos,val);
    pushup(x);
}
Matrix query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return t[x];
    int mid=(l+r)>>1;
    if(qr<=mid) return query(x<<1,l,mid,ql,qr);
    else if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
    else return query(x<<1,l,mid,ql,qr)*query(x<<1|1,mid+1,r,ql,qr);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&opt,&x,&y);
        if(opt==0) change(1,1,n,x,y);
        else
        {
            Matrix t=query(1,1,n,x,y);
            printf("%d\n",max(t[1],t[3]));
        }
    }
}
