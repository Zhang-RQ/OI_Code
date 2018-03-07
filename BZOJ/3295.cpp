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
    int t,pos,val;
    node(){}
    node(int _t,int _pos,int _val):t(_t),pos(_pos),val(_val) {}
    bool operator < (const node &rhs) const
    {
        return t<rhs.t;
    }
}num[MAXN],tmp[MAXN];
ll ans[MAXN];
int t[MAXN+5];
void add(int pos,int val)
{
    for(int i=pos;i<=MAXN;i+=i&-i)
        t[i]+=val;
}
ll query(int pos)
{
    ll ret=0;
    for(int i=pos;i>=1;i-=i&-i)
        ret+=t[i];
    return ret;
}
void CDQ(int L,int R)
{
    if(L==R) return;
    int mid=(L+R)>>1;
    CDQ(L,mid);CDQ(mid+1,R);
    int l=L,r=mid+1,ccnt=0;
    while(l<=mid&&r<=R)
    {
        if(num[l].pos<=num[r].pos)  add(num[l].val,1),tmp[++ccnt]=num[l++];
        else ans[num[r].t]+=query(MAXN)-query(num[r].val-1),tmp[++ccnt]=num[r++];
    }
    while(l<=mid) add(num[l].val,1),tmp[++ccnt]=num[l++];
    while(r<=R) ans[num[r].t]+=query(MAXN)-query(num[r].val-1),tmp[++ccnt]=num[r++];
    for(int i=L;i<=mid;i++) add(num[i].val,-1);
    for(int i=1;i<=ccnt;i++) num[L+i-1]=tmp[i];
    for(int i=R;i>=L;i--)
    {
        if(num[i].t<=mid) add(num[i].val,1);
        else ans[num[i].t]+=query(num[i].val);
    }
    for(int i=L;i<=R;i++)
        if(num[i].t<=mid) add(num[i].val,-1);
}
int n,m,arr[MAXN],tot,tim[MAXN],tt,tnow;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
    tnow=n;
    for(int i=0;i<m;i++)
    {
        scanf("%d",&tt);
        tim[tt]=tnow--;
    }
    for(int i=1;i<=n;i++) if(!tim[i]) tim[i]=tnow--;
    for(int i=1;i<=n;i++)
        num[i]=node(tim[arr[i]],i,arr[i]);
    sort(num+1,num+1+n);
    CDQ(1,n);
    for(int i=1;i<=n;i++)
        ans[i]+=ans[i-1];
    for(int i=n;i>n-m;i--)
        printf("%lld\n",ans[i]);
}
