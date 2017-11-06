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
const int MAXN=200100;
int v[MAXN],w[MAXN],n,l[MAXN],r[MAXN],m;
ll sum[MAXN],S,sub[MAXN];
ll calc(int W)
{
    int cnt=0;
    ll ret=0;
    for(int i=1;i<=n;i++)
    {
        sum[i]=sum[i-1];
        sub[i]=sub[i-1];
        if(w[i]>=W)
            sub[i]++,
            sum[i]+=v[i];
    }
    for(int i=1;i<=m;i++)
        ret+=(sum[r[i]]-sum[l[i]-1])*(sub[r[i]]-sub[l[i]-1]);
    return ret;
}
int main()
{
    ll ans=0x3f3f3f3f3f;
    int L=0,R=0;
    scanf("%d%d%lld",&n,&m,&S);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&w[i],&v[i]),R=max(R,w[i]);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&l[i],&r[i]);
    while(L<=R)
    {
        int mid=(L+R)>>1;
        ll tmp=calc(mid);
        ans=min(abs(tmp-S),ans);
        if(tmp==S) break;
        if(tmp<S) R=mid-1;
        if(tmp>S) L=mid+1;
    }
    printf("%lld\n",ans);
}
