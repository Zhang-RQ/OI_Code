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
ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    n++;m++;
    ll t=n*m;
    ll ans=t*(t-1)*(t-2)/6;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(i||j)
            {
                t=1ll*(gcd(i,j)-1)*(n-i)*(m-j);
                if(!i||!j) ans-=t;
                else ans-=2*t;
            }
    printf("%lld\n",ans);
}
