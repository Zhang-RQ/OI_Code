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
bool vis[1000000010];
std::vector<int> primes;
void eular(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]) primes.push_back(i);
        for(int j=0;j<(signed)primes.size()&&i*primes[j]<=n;j++)
        {
            vis[primes[j]*i]=1;
            if(!i%primes[j]) break;
        }
    }
}
int main()
{
    int n,m,k;
    scanf("%d%d",&n,&m);
    eular(n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&k);
        if(*lower_bound(primes.begin(),primes.end(),k)==k) puts("Prime");
        else puts("Not Prime");
    }
}
