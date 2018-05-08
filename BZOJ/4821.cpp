// luogu-judger-enable-o2
%:pragma GCC optimize(2)
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
const int MAXN=1E5+10;
struct node{
    long double sumx,sumy,xy,sumx2,tagS,tagT;
    bool tag;
}t[MAXN<<3];
int X[MAXN],Y[MAXN],n,m,opt,L,R,S,T;
inline void pushup(const int &x)
{
    t[x].sumx=t[x<<1].sumx+t[x<<1|1].sumx;
    t[x].sumy=t[x<<1].sumy+t[x<<1|1].sumy;
    t[x].xy=t[x<<1].xy+t[x<<1|1].xy;
    t[x].sumx2=t[x<<1].sumx2+t[x<<1|1].sumx2;
}
inline void pushdown(const int &x,const int &l,const int &r)
{
    if(t[x].tag)
    {
        int mid=(l+r)>>1;
        t[x<<1].sumx=t[x<<1].sumy=1.0*(mid-l+1)*(l+mid)/2;
        t[x<<1].sumx2=t[x<<1].xy=1.0*mid*(mid+1)*(2*mid+1)/6-1.0*(l-1)*l*(2*l-1)/6;
        t[x<<1|1].sumx=t[x<<1|1].sumy=1.0*(r-mid)*(r+mid+1)/2;
        t[x<<1|1].sumx2=t[x<<1|1].xy=1.0*r*(r+1)*(2*r+1)/6-1.0*mid*(mid+1)*(2*mid+1)/6;
        t[x<<1].tagS=t[x<<1].tagT=t[x<<1|1].tagS=t[x<<1|1].tagT=0;
        t[x<<1].tag=t[x<<1|1].tag=1;
        t[x].tag=0;
    }
    if(t[x].tagS||t[x].tagT)
    {
        int mid=(l+r)>>1;
        t[x<<1].xy+=t[x].tagT*t[x<<1].sumx+t[x].tagS*t[x<<1].sumy+(mid-l+1)*t[x].tagT*t[x].tagS;
        t[x<<1].sumx2+=2.0*t[x<<1].sumx*t[x].tagS+(mid-l+1)*t[x].tagS*t[x].tagS;
        t[x<<1].sumx+=t[x].tagS*(mid-l+1);t[x<<1].sumy+=t[x].tagT*(mid-l+1);

        t[x<<1|1].xy+=t[x].tagT*t[x<<1|1].sumx+t[x].tagS*t[x<<1|1].sumy+(r-mid)*t[x].tagT*t[x].tagS;
        t[x<<1|1].sumx2+=2.0*t[x<<1|1].sumx*t[x].tagS+(r-mid)*t[x].tagS*t[x].tagS;
        t[x<<1|1].sumx+=t[x].tagS*(r-mid);t[x<<1|1].sumy+=t[x].tagT*(r-mid);

        t[x<<1].tagS+=t[x].tagS;t[x<<1].tagT+=t[x].tagT;
        t[x<<1|1].tagS+=t[x].tagS;t[x<<1|1].tagT+=t[x].tagT;
        t[x].tagS=t[x].tagT=0;
    }
}
void build(int x,int l,int r)
{
    if(l==r) {t[x].sumx=X[l];t[x].sumy=Y[l];t[x].xy=1.0*X[l]*Y[l];t[x].sumx2=1.0*X[l]*X[l];return;}
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    pushup(x);
}
long double query(int x,int l,int r,int ql,int qr,int tp) // tp
{
    if(ql<=l&&r<=qr) return tp==1?t[x].sumx:(tp==2?t[x].sumy:(tp==3?t[x].xy:t[x].sumx2));
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    long double ret=0;
    if(ql<=mid) ret+=query(x<<1,l,mid,ql,qr,tp);
    if(qr>mid)  ret+=query(x<<1|1,mid+1,r,ql,qr,tp);
    return ret;
}
void change(int x,int l,int r,int cl,int cr,ll S,ll T)
{
    if(cl<=l&&r<=cr)
    {
        t[x].tagS+=S;t[x].tagT+=T;
        t[x].xy+=1.0*T*t[x].sumx+S*t[x].sumy+1.0*(r-l+1)*T*S;
        t[x].sumx2+=2.0*t[x].sumx*S+1.0*(r-l+1)*S*S;
        t[x].sumx+=1.0*S*(r-l+1);t[x].sumy+=1.0*T*(r-l+1);
        return;
    }
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    if(cl<=mid) change(x<<1,l,mid,cl,cr,S,T);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,S,T);
    pushup(x);
}
void change(int x,int l,int r,int cl,int cr)
{
    if(cl<=l&&r<=cr)
    {
        t[x].sumx=t[x].sumy=1.0*(l+r)*(r-l+1)/2;
        t[x].sumx2=t[x].xy=1.0*r*(r+1)*(2*r+1)/6-1.0*(l-1)*l*(2*l-1)/6;
        t[x].tag=1;t[x].tagS=t[x].tagT=0;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    if(cl<=mid) change(x<<1,l,mid,cl,cr);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr);
    pushup(x);
}
signed main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&X[i]);
    for(int i=1;i<=n;i++) scanf("%d",&Y[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&opt,&L,&R);
        switch (opt)
        {
            case 1:
            {
                long double sumx=query(1,1,n,L,R,1),sumy=query(1,1,n,L,R,2);
                printf("%.10Lf\n",(1.0*query(1,1,n,L,R,3)-1.0*sumx/(R-L+1)*sumy)/(query(1,1,n,L,R,4)-1.0*sumx/(R-L+1)*sumx));
                break;
            }
            case 2:
            {
                scanf("%d%d",&S,&T);
                change(1,1,n,L,R,S,T);
                break;
            }
            case 3:
            {
                scanf("%d%d",&S,&T);
                change(1,1,n,L,R);
                change(1,1,n,L,R,S,T);
                break;
            }
        }
    }
}
