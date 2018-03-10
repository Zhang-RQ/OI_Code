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
const int P=2007;
ll n,t;
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;
        b>>=1;
    }
    return ret%P;
}
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        printf("%lld\n",(4ll*n*ksm(5,n-1))%P);
    }
}
