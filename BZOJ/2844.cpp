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
const int MAXN=100010;
const int P=10086;
ll a[MAXN],b[64],n,q,Rank;
vector<ll> v;
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
void build()
{
    for(int i=1;i<=n;i++)
        for(int j=62;~j;j--)
            if(a[i]>>j&1)
            {
                if(b[j]) a[i]^=b[j];
                else
                {
                    b[j]=a[i];
                    break;
                }
            }
    for(int i=0;i<=62;i++)
        if(b[i]) v.push_back(i);
}
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    scanf("%lld",&q);
    build();
    for(int i=0;i<(signed)v.size();i++)
        if(q>>v[i]&1) (Rank+=1<<i)%=P;
    printf("%lld\n",(Rank*ksm(2,n-v.size())%P+1)%P);
}
