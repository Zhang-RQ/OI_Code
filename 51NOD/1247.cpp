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
ll gcd(ll a,ll b)
{
    if(!a||!b) return a|b;
    if(a<b) return gcd(b%a,a);
    else return gcd(a%b,b);
}
int main()
{
    int T;
    ll a,b,c,d;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld %lld %lld %lld",&a,&b,&c,&d);
        puts(gcd(a,b)==gcd(c,d)?"Yes":"No");

    }
    #ifdef LOCAL
        system("pause");
    #endif
}