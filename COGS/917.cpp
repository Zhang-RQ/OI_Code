#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
int n,k;
int in[100010];
bool check(ll x)
{
    int tot=0;
    ll cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(in[i]+cnt>x)
        {
            tot++;
            cnt=in[i];
        }else{
            cnt+=in[i];
        }
    }
    if(cnt) tot++;
    return tot<=k;
}
int main()
{
    freopen("seqa.in","r",stdin);
    freopen("seqa.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&in[i]);
    ll l=1;
    ll r=(ll)1e9;
    ll ans;
    while(l<=r)
    {
        ll mid=(l+r)>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%lld\n",ans);
}
