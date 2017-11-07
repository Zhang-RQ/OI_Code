#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=100010;
int l[MAXN],r[MAXN],n,cnt=0,ans=0;
int arr[MAXN<<1];
int tmp[MAXN<<1];
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld",&l[i],&r[i]),tmp[++cnt]=l[i],tmp[++cnt]=r[i];
    sort(tmp+1,tmp+1+cnt);
    int cnt2=unique(tmp+1,tmp+1+cnt)-tmp-1;
    for(int i=1;i<=n;i++)
        l[i]=lower_bound(tmp+1,tmp+1+cnt2,l[i])-tmp,
        r[i]=lower_bound(tmp+1,tmp+1+cnt2,r[i])-tmp,
        ++arr[l[i]],--arr[r[i]+1];
    for(int i=1;i<=cnt2;i++)
        arr[i]+=arr[i-1],
        ans=max(ans,arr[i]*tmp[i]);
    printf("%lld\n",ans);
}
