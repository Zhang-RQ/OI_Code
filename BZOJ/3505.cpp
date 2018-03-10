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
ll c[1010][1010];
void calc()
{
    c[0][0]=1;
    for(int i=1;i<=1000;i++)
        for(int j=1;j<=1000;j++)
            c[i][j]=c[i-1][j-1]+c[i-1][j];
}
ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
int n,m;
int main()
{
    calc();
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
