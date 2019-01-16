#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

int main()
{
    int n;
    while(~scanf("%d",&n)&&n)
    {
        ll Ans=1ll*n*n*8+1ll*n*n*n*12+1ll*n*n*n*n*3+1ll*n*n*n*n*n*n;
        printf("%lld\n",Ans/24);
    }
}