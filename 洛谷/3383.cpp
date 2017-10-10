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
std::vector<int> primes;
bool vis[10000100];
void solve(int end)
{
    for(int i=2;i<=end;i++)
    {
        if(!vis[i]) primes.push_back(i);
        for(int j=0;j<primes.size()&&primes[j]*i<=end;j++)
        {
            vis[primes[j]*i]=1;
            if(i%primes[j]==0) break;
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    int n,m,t1;
    cin>>n;
    cin>>m;
    solve(n);
    for(int i=1;i<=m;i++)
    {
        cin>>t1;
        if(*lower_bound(primes.begin(),primes.end(),t1)==t1) puts("Yes");
        else puts("No");
    }
}
