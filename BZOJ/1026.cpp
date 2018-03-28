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
int f[12][10],num[12];
int dfs(int len,int last,bool zero,bool lim)
{
    if(len==0) return 1;
    if(!zero&&!lim&&f[len][last]!=-1) return f[len][last];
    int cnt=0,mx=lim?num[len]:9;
    for(int i=0;i<=mx;i++)
    {
        if(abs(i-last)<2&&!zero) continue;
        cnt+=dfs(len-1,i,zero&&i==0,lim&&i==mx);
    }
    if(!lim&&!zero) f[len][last]=cnt;
    return cnt;
}
int solve(ll x)
{
    int tot;
    for(tot=1;x;x/=10,tot++)
        num[tot]=x%10;
    tot--;
    memset(f,-1,sizeof f);
    return dfs(tot,-100,1,1);
}
int main()
{
    ll L,R;
    cin>>L>>R;
    cout<<solve(R)-solve(L-1)<<endl;
}
