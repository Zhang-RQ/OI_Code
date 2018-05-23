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
#include<cassert>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=110;
struct node{
    double sum;
    int cov;
}t[MAXN<<4];
struct Segment{
    int l,r;
    double h;
    int f;
    Segment(){}
    Segment(int _,int __,double ___,int ____){l=_;r=__;h=___;f=____;}
    bool operator < (const Segment &rhs) const {return h<rhs.h;}
}s[MAXN<<2];
double xx[MAXN<<2],yy[MAXN<<2],x1[MAXN],x2[MAXN],__y1[MAXN],y2[MAXN];
int n,cnts,cntx,cnty,_x1[MAXN],_x2[MAXN];
void pushup(int x,int l,int r)
{
    if(t[x].cov) t[x].sum=xx[r+1]-xx[l];
    else if(l==r) t[x].sum=0;
    else t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
}
void change(int x,int l,int r,int cl,int cr,int f)
{
    if(cl<=l&&r<=cr)
    {
        t[x].cov+=f;
        pushup(x,l,r);
        return;
    }
    int mid=(l+r)>>1;
    if(cl<=mid) change(x<<1,l,mid,cl,cr,f);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,f);
    pushup(x,l,r);
}
int main()
{
    int Cs=0;
    while(~scanf("%d",&n)&&n)
    {
        cnts=cntx=cnty=0;
        memset(t,0,sizeof t);
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf%lf%lf",&x1[i],&__y1[i],&x2[i],&y2[i]);
            xx[++cntx]=x1[i];xx[++cntx]=x2[i];
        }
        sort(xx+1,xx+1+cntx);
        cntx=unique(xx+1,xx+1+cntx)-xx-1;
        for(int i=1;i<=n;i++)
        {
            _x1[i]=lower_bound(xx+1,xx+1+cntx,x1[i])-xx;
            _x2[i]=lower_bound(xx+1,xx+1+cntx,x2[i])-xx;
            s[++cnts]=Segment(_x1[i],_x2[i],__y1[i],1);
            s[++cnts]=Segment(_x1[i],_x2[i],y2[i],-1);
        }
        sort(s+1,s+cnts+1);
        double ans=0;
        for(int i=1;i<cnts;i++)
        {
            change(1,1,cntx,s[i].l,s[i].r-1,s[i].f);
            ans+=t[1].sum*(s[i+1].h-s[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",++Cs,ans);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}