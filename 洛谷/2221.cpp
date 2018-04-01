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
const int MAXN=100100;
struct node{
    ll sum[3],tag;
}t[MAXN<<3];
int n,m,l,r,v;
char opt[10];
ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
void pushup(int x)
{
    t[x].sum[0]=t[x<<1].sum[0]+t[x<<1|1].sum[0];
    t[x].sum[1]=t[x<<1].sum[1]+t[x<<1|1].sum[1];
    t[x].sum[2]=t[x<<1].sum[2]+t[x<<1|1].sum[2];
}
void aaa(int x,int l,int r,ll val)
{
    t[x].sum[0]+=val*(r-l+1);
    t[x].sum[1]+=val*((l+r)*(r-l+1)/2);
    t[x].sum[2]+=val*((r*(r+1)*(2*r+1)/6)-(((l-1)*l*(2*l-1))/6));
}
void pushdown(int x,int l,int r)
{
    if(t[x].tag!=0)
    {
        int mid=(l+r)>>1;
        aaa(x<<1,l,mid,t[x].tag);aaa(x<<1|1,mid+1,r,t[x].tag);
        t[x<<1].tag+=t[x].tag;t[x<<1|1].tag+=t[x].tag;
        t[x].tag=0;
    }
}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&r<=cr) {t[x].tag+=val;aaa(x,l,r,val);return;}
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
    if(cr>mid) change(x<<1|1,mid+1,r,cl,cr,val);
    pushup(x);
}
ll query(int x,int l,int r,int ql,int qr,int f)
{
    if(ql<=l&&r<=qr) return t[x].sum[f];
    int mid=(l+r)>>1;ll ret=0;
    pushdown(x,l,r);
    if(ql<=mid) ret+=query(x<<1,l,mid,ql,qr,f);
    if(qr>mid)  ret+=query(x<<1|1,mid+1,r,ql,qr,f);
    return ret;
}
void solve(ll l,ll r)
{
    ll aa=(r-l+2)*(r-l+1)/2;
    ll bb=query(1,1,n,l,r,1)*(l+r)-query(1,1,n,l,r,2)+(r-l*r-l+1)*query(1,1,n,l,r,0);
    if(aa==0) {printf("0/1");return;}
    // printf("%lld %lld %lld\n",query(1,1,n,l,r,0),query(1,1,n,l,r,1),query(1,1,n,l,r,2));
    ll gc=gcd(aa,bb);
    printf("%lld/%lld\n",bb/gc,aa/gc);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",opt+1);
        switch(opt[1])
        {
            case 'C':scanf("%d%d%d",&l,&r,&v);change(1,1,n,l,r-1,v);break;
            case 'Q':scanf("%d%d",&l,&r);solve(l,r-1);break;
        }
    }
}
