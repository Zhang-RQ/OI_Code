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
const int MAXN=1E5+5;
const int MAXK=2E5+5;
struct node{
    int a,b,c,id;
    bool operator < (const node &rhs) const
    {
        if(a!=rhs.a) return a<rhs.a;
        if(b!=rhs.b) return b<rhs.b;
        return c<rhs.c;
    }
    bool operator == (const node &rhs) const
    {
        return a==rhs.a&&b==rhs.b&&c==rhs.c;
    }
}f[MAXN],tmp[MAXN];
int ans[MAXN],n,t[MAXK],k,cnt[MAXN];
void add(int pos,int val)
{
    for(int i=pos;i<=k;i+=(-i)&i)
        t[i]+=val;
}
int query(int pos)
{
    int ret=0;
    for(int i=pos;i>=1;i-=(-i)&i)
        ret+=t[i];
    return ret;
}
void CDQ(int l,int r)
{
    if(l==r) return;
    int mid=(l+r)>>1;
    CDQ(l,mid);CDQ(mid+1,r);
    int L=l,R=mid+1,cntt=0;
    while(L<=mid&&R<=r)
    {
        if(f[L].b<=f[R].b)  add(f[L].c,1),tmp[++cntt]=f[L],L++;
        else ans[f[R].id]+=query(f[R].c),tmp[++cntt]=f[R],R++;
    }
    while(L<=mid) add(f[L].c,1),tmp[++cntt]=f[L++];
    while(R<=r) ans[f[R].id]+=query(f[R].c),tmp[++cntt]=f[R++];
    for(int i=l;i<=mid;i++) add(f[i].c,-1);
    for(int i=1;i<=cntt;i++) f[i+l-1]=tmp[i];
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&f[i].a,&f[i].b,&f[i].c),f[i].id=i;
    sort(f+1,f+1+n);
    node tp=f[n];int tt=1;
    for(int i=n-1;i>=1;i--)
        if(f[i]==tp) ans[f[i].id]+=tt,tt++;
        else tt=1,tp=f[i];
    CDQ(1,n);
    for(int i=1;i<=n;i++)
        cnt[ans[i]]++;
    for(int i=0;i<n;i++)
        printf("%d\n",cnt[i]);
}
