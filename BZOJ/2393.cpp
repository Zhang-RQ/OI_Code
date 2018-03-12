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
std::vector<ll> v1,v;
ll tans=0,ans=0;
ll L,R;
ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
inline ll lcm(ll a,ll b)
{
    return a*b/gcd(a,b);
}
void dfs1(int num,ll now)
{
    if(num>9) return;
    if(now!=0) v1.push_back(now);
    dfs1(num+1,now*10+2);
    dfs1(num+1,now*10+9);
}
void dfs2(ll now,int pos,int flag)
{
    if(pos>=v.size())
    {
        if(now!=1) ans+=(R/now-(L-1)/now)*flag;
        return;
    }
    dfs2(now,pos+1,flag);
    ll tmp=lcm(now,v[pos]);
    if(tmp>R) return;
    dfs2(tmp,pos+1,-flag);
}
int main()
{
    dfs1(0,0);
    sort(v.begin(),v.end());
    scanf("%lld %lld",&L,&R);
    for(int i=0;i<v1.size();i++)
    {
        bool flag=0;
        for(int j=0;j<i;j++)
            if(v1[i]%v1[j]==0)
                flag=1;
        if(!flag) v.push_back(v1[i]);
    }
    dfs2(1,0,-1);
    printf("%lld\n",ans);
}
