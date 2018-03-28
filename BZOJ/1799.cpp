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
int num[19];
ll f[19][163][163];
ll dfs(int len,int sum,int now,int mod,bool zero,bool lim)
{
    if(sum>mod) return 0;
    if(!len) return sum==0?0:now%sum==0&&mod==sum;
    if(!zero&&!lim&&f[len][sum][now]!=-1) return f[len][sum][now];
    int mx=lim?num[len]:9;
    ll ret=0;
    for(int i=0;i<=mx;i++)
        ret+=dfs(len-1,sum+i,(now*10+i)%mod,mod,zero&&i==0,lim&&mx==i);
    if(!zero&&!lim) f[len][sum][now]=ret;
    return ret;
}
ll solve(ll x)
{
    int tot=1;
    for(tot=1;x;x/=10,tot++)
        num[tot]=x%10;
    tot--;
    ll ret=0;
    for(int i=1;i<=162;i++)
        memset(f,-1,sizeof f),ret+=dfs(tot,0,0,i,1,1);
    return ret;
}
ll L,R;
int main()
{
    scanf("%lld%lld",&L,&R);
    printf("%lld\n",solve(R)-solve(L-1));
}
