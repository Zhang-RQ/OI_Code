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
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
using namespace std;
typedef long long ll;
const int MAXN=100010;
struct node{
    ll val;
    ll tag_p,tag_m;
}tree[MAXN<<2];
int P,N,M,ops,x,y,k;
ll arr[MAXN];
void build(int x,int l,int r)
{
    tree[x].tag_m=1;
    if(l==r) {tree[x].val=arr[l];return;}
    int mid=(l+r)>>1;
    build(Ls);
    build(Rs);
    (tree[x].val=tree[x<<1].val+tree[x<<1|1].val)%=P;
}
void pushdown(int x,int l,int r)
{
    if(tree[x].tag_m!=1)
    {
        (tree[x<<1|1].tag_p*=tree[x].tag_m)%=P;
        (tree[x<<1].tag_p*=tree[x].tag_m)%=P;
        (tree[x<<1].val*=tree[x].tag_m)%=P;
        (tree[x<<1|1].val*=tree[x].tag_m)%=P;
        (tree[x<<1].tag_m*=tree[x].tag_m)%=P;
        (tree[x<<1|1].tag_m*=tree[x].tag_m)%=P;
        tree[x].tag_m=1;
    }
    if(tree[x].tag_p)
    {
        int mid=(l+r)>>1;
        (tree[x<<1].val+=tree[x].tag_p*(mid-l+1))%=P;
        (tree[x<<1|1].val+=tree[x].tag_p*(r-mid))%=P;
        (tree[x<<1].tag_p+=tree[x].tag_p)%=P;
        (tree[x<<1|1].tag_p+=tree[x].tag_p)%=P;
        tree[x].tag_p=0;
    }
}
void section_plus(int x,int l,int r,int sl,int sr,int val)
{
    if(sl>r||sr<l) return;
    if(sl<=l&&r<=sr)
        {(tree[x].val+=val*(r-l+1))%=P;(tree[x].tag_p+=val)%=P;return;}
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    if(sr>mid)   section_plus(Rs,sl,sr,val);
    if(sl<=mid)  section_plus(Ls,sl,sr,val);
    (tree[x].val=tree[x<<1].val+tree[x<<1|1].val)%=P;
}
void section_mutiply(int x,int l,int r,int sl,int sr,int val)
{
    if(sl>r||sr<l) return;
    if(sl<=l&&r<=sr)
        {(tree[x].val*=val)%=P;(tree[x].tag_m*=val)%=P;(tree[x].tag_p*=val)%=P;return;}
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    if(sr>mid)   section_mutiply(Rs,sl,sr,val);
    if(sl<=mid)  section_mutiply(Ls,sl,sr,val);
    (tree[x].val=tree[x<<1].val+tree[x<<1|1].val)%=P;
}
ll query(int x,int l,int r,int ql,int qr)
{
    if(ql>r||qr<l) return 0;
    if(ql<=l&&r<=qr) return tree[x].val;
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    return (query(Ls,ql,qr)+query(Rs,ql,qr))%P;
}
int main()
{
    scanf("%d%d%d",&N,&M,&P);
    for(int i=1;i<=N;i++)
        scanf("%lld",&arr[i]);
    build(1,1,N);
    for(int i=1;i<=M;i++)
    {
        scanf("%d%d%d",&ops,&x,&y);
        if(ops==1)
        {
            scanf("%d",&k);
            section_mutiply(1,1,N,x,y,k);
        }
        if(ops==2)
        {
            scanf("%d",&k);
            section_plus(1,1,N,x,y,k);
        }
        if(ops==3)
            printf("%lld\n",query(1,1,N,x,y));
    }
    return 0;
}
