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
ll a,b;
ll f[12][12][10],ans[2][10];
int x[12];
ll dfs(int len,int sum,int num,bool zero,bool lim)
{
    if(len==0) {return sum;}
    if(!zero&&!lim&&f[len][sum][num]!=-1) {return f[len][sum][num];}
    ll mx=lim?x[len]:9,ret=0;
    for(int i=0;i<=mx;i++)
        ret+=dfs(len-1,sum+((i==num)&&(i!=0||(!zero))),num,zero&&i==0,lim&&i==mx);
    if(!zero&&!lim) f[len][sum][num]=ret;
    return ret;
}
void solve(ll x,int t)
{
    int tot=1;
    for(tot=1;x;x/=10,tot++)
        ::x[tot]=x%10;
    tot--;
    for(int i=0;i<=9;i++)
        memset(f,-1,sizeof f),ans[t][i]=dfs(tot,0,i,1,1);
}
int main()
{
    scanf("%lld%lld",&a,&b);
    solve(a-1,0);solve(b,1);
    for(int i=0;i<=9;i++)
        printf("%lld ",ans[1][i]-ans[0][i]);
    puts("");
}
