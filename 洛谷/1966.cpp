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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN=1E5+10;
const int P=99999997;
int vv[MAXN];
ll tree[MAXN];
int n;
struct data{
    int val,pos;
    bool operator < (data a)
    {
        return val<a.val;
    }
}arr1[MAXN],arr2[MAXN];
inline int lowbit(int x)
{
    return x&(-x);
}
void modify(int pos,int val)
{
    for(int i=pos;i<=n;i+=lowbit(i))
        (tree[i]+=val)%=P;
}
ll query(int pos)
{
    ll ret=0;
    for(int i=pos;i>=1;i-=lowbit(i))
        (ret+=tree[i])%=P;
    return ret;
}
int main()
{
    ll ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr1[i].val),arr1[i].pos=i;
    for(int i=1;i<=n;i++)
        scanf("%d",&arr2[i].val),arr2[i].pos=i;
    sort(arr1+1,arr1+1+n);
    sort(arr2+1,arr2+1+n);
    //int cnt1=unique(arr1+1,arr1+1+n)-arr1-1;
    //int cnt2=unique(arr2+1,arr2+1+n)-arr2-1;
    for(int i=1;i<=n;i++)
        vv[arr1[i].pos]=arr2[i].pos;
    for(int i=n;i>=1;i--)
    {
        (ans+=query(vv[i]-1))%=P;
        modify(vv[i],1);
    }
    printf("%lld\n",ans);
}
