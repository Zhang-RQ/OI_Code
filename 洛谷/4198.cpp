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
const int MAXN=100010;
struct node{
    double mx;
    int cnt;
}t[MAXN<<2];
int n,m;
int calc(int x,int l,int r,double k)
{
    if(l==r) return t[x].mx>k;
    int mid=(l+r)>>1;
    if(t[x<<1].mx<=k) return calc(x<<1|1,mid+1,r,k);
    else return t[x].cnt-t[x<<1].cnt+calc(x<<1,l,mid,k);
}
void pushup(int x,int l,int r)
{
    t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);
    t[x].cnt=t[x<<1].cnt+calc(x<<1|1,((l+r)>>1)+1,r,t[x<<1].mx);
}
void change(int x,int l,int r,int pos,double k)
{
    if(l==r) return t[x].mx=k,t[x].cnt=1,void();
    int mid=(l+r)>>1;
    if(pos<=mid) change(x<<1,l,mid,pos,k);
    else change(x<<1|1,mid+1,r,pos,k);
    pushup(x,l,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        change(1,1,n,x,1.0*y/x);
        printf("%d\n",t[1].cnt);
    }
    return 0;
    #ifdef LOCAL
        system("pause");
    #endif
}