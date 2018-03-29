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
ll f[2][65],op[2][65][2010],L,R,g[2][65];
int k,num[65],tot;
ll dfs(int len,bool lim)
{
    if(!len) return g[lim][len]=1,0;
    if(f[lim][len]!=-1) return f[lim][len];
    int mx=lim?num[len]:k-1;
    ll ret=0;
    for(int i=0;i<=mx;i++)
        ret+=dfs(len-1,lim&&i==mx)+g[lim&&i==mx][len-1]*i*(len-1),
        g[lim][len]+=g[lim&&i==mx][len-1];
    f[lim][len]=ret;
    return ret;
}
ll opt(int len,int sum,bool lim,int d)
{
    if(!len) return sum;
    if(op[lim][len][sum]!=-1) return op[lim][len][sum];
    int mx=lim?num[len]:k-1,f=(len>=d?1:-1);
    ll ret=0;
    for(int i=0;i<=mx;i++)
    {
        if(f<0&&sum+i*f<=0) break;
        ret+=opt(len-1,sum+i*f,lim&&i==mx,d);
    }
    return op[lim][len][sum]=ret;
}
ll solve(ll x)
{
    tot=1;
    for(tot=1;x;x/=k,tot++)
        num[tot]=x%k;
    tot--;
    memset(f,-1,sizeof f);memset(g,0,sizeof g);
    ll ret=dfs(tot,1);
    for(int i=2;i<=tot;i++)
        memset(op,-1,sizeof op),ret-=opt(tot,0,1,i);
    return ret;
}
int main()
{
    scanf("%lld%lld%d",&L,&R,&k);
    printf("%lld\n",solve(R)-solve(L-1));
}
