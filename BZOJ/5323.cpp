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
const int P=1E9+7;
const int MAXN=1E7+10;
bool vis[MAXN];
ll fac[MAXN],ifac[MAXN],ans;
int l,r,cnt;
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;b>>=1;
    }
    return ret;
}

int main()
{
    scanf("%d%d",&l,&r);fac[0]=ifac[0]=1;
    for(int i=1;i<=r;i++) fac[i]=fac[i-1]*i%P;
    ifac[r]=ksm(fac[r],P-2);
    for(int i=r-1;i;i--) ifac[i]=ifac[i+1]*(i+1)%P;
    if(l==1) return printf("%lld\n",fac[r]*(r+1)%P*ksm(2,P-2)%P),0;
    int n=r-l+1;
    for(int i=l;i<=r;i++)
        if(!vis[i])
        {
            cnt++;
            for(int j=i;j<=r;j+=i)
                vis[j]=1;
        }
    for(int i=cnt;i<=n;i++)
        (ans+=cnt*fac[n-cnt]%P*ifac[i-cnt]%P*fac[i]%P)%=P;
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}