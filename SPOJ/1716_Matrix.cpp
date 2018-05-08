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
    int a[3][3];
    Matrix(){memset(a,0xcf,sizeof a);}
    inline int* operator [](int i) {return a[i];}
    inline Matrix operator * (const Matrix &rhs) const
    {
        Matrix ret;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    ret[i][j]=max(ret[i][j],a[i][k]+rhs.a[k][j]);
        return ret;
    }
}t[MAXN<<2];
int val[MAXN],n,m,opt,x,y;
inline void pushup(int x){t[x]=t[x<<1]*t[x<<1|1];}
void build(int x,int l,int r)
{
    if(l==r)
    {
        t[x][0][0]=val[l];t[x][0][1]=val[l];t[x][0][2]=-INF;
        t[x][1][0]=-INF  ;t[x][1][1]=0     ;t[x][1][2]=-INF;
        t[x][2][0]=val[l];t[x][2][1]=val[l];t[x][2][2]=0   ;
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
        t[x][0][0]=val ;t[x][0][1]=val;t[x][0][2]=-INF;
        t[x][1][0]=-INF;t[x][1][1]=0  ;t[x][1][2]=-INF;
        t[x][2][0]=val ;t[x][2][1]=val;t[x][2][2]=0   ;
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
    int mid=(l+r)>>1;Matrix ret;
    ret[0][0]=ret[0][2]=0;
    if(ql<=mid) ret=ret*query(x<<1,l,mid,ql,qr);
    if(qr>mid)  ret=ret*query(x<<1|1,mid+1,r,ql,qr);
    return ret;
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
        else printf("%d\n",query(1,1,n,x,y)[0][1]);
    }
}
