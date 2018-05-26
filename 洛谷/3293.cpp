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
#define do_nothing
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=2E5+10;
const int MX=1E5+1;
struct node{
    int ls,rs,val;
}t[MAXN<<4];
int cnt,rt[MAXN],n,m;
void insert(int &x,int l,int r,int pos,int _x)
{
    x=++cnt;
    t[x]=t[_x];
    t[x].val++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) insert(t[x].ls,l,mid,pos,t[_x].ls);
    else insert(t[x].rs,mid+1,r,pos,t[_x].rs);
}
int query(int x,int l,int r,int ql,int qr,int _x)
{
    if(ql<=l&&r<=qr) return t[x].val-t[_x].val;
    int mid=(l+r)>>1,ret=0;
    if(ql<=mid) ret+=query(t[x].ls,l,mid,ql,qr,t[_x].ls);
    if(qr>mid)  ret+=query(t[x].rs,mid+1,r,ql,qr,t[_x].rs);
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        insert(rt[i],1,MX,x,rt[i-1]);
    }
    for(int i=1,b,x,l,r,ans;i<=m;i++)
    {
        scanf("%d%d%d%d",&b,&x,&l,&r);
        ans=0;
        for(int j=18;~j;j--)
        {
            if((b>>j)&1)
            {
                if(query(rt[r],1,MX,max(1,ans-x),min(MX,ans+(1<<j)-1-x),rt[l-1])>0) do_nothing;
                else ans|=(1<<j);
            }
            else
            {
                if(query(rt[r],1,MX,max(1,ans+(1<<j)-x),min(MX,ans+(1<<j)+(1<<j)-1-x),rt[l-1])>0) ans|=(1<<j);
                else do_nothing;
            }
        }
        printf("%d\n",ans^b);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}