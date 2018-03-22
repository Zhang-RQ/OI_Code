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
const int P=100003;
const int MAXN=100010;
vector<int> v[MAXN];
ll n,k,a[MAXN],fac[MAXN],inv[MAXN],ans,tans;
ll f[MAXN];
int main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%P;
    inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=(1ll*P-(P/i)*inv[P%i]%P)%P;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j+=i)
            v[j].push_back(i);
    for(int i=n;i>=1;i--)
    {
        if(a[i])
        {
            ans++;
            for(int j=0;j<(int)v[i].size();j++)
                a[v[i][j]]^=1;
        }
    }
    if(ans<=k) printf("%lld\n",1ll*fac[n]*ans%P);
    else
    {
        f[n]=1;
        for(int i=n-1;i>=1;i--)
            f[i]=1+1ll*(n-i)*(f[i+1]+1)%P*inv[i]%P;
        for(int i=ans;i>k;i--) (tans+=f[i])%=P;
        (tans+=k)%=P;
        printf("%lld\n",1ll*tans*fac[n]%P);
    }
}
