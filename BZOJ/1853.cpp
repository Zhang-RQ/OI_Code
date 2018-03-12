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
#include<ctime>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
ll tans=0,ans=0,v[10010],v1[10010],top,top1;
ll L,R;
ll gcd(ll a,ll b)
{
    ll t=0;
    while(b)
    {
        t=b;
        b=a%b;
        a=t;
    }
    return a;
}
void dfs1(int num,ll now)
{
    if(now>R) return;
    if(now!=0) v1[++top1]=now;
    dfs1(num+1,now*10+6);
    dfs1(num+1,now*10+8);
}
void dfs2(ll now,ll pos,int flag)
{
    if(pos>top)
    {
        if(now!=1) ans+=(R/now-(L-1)/now)*flag;
        return;
    }
    dfs2(now,pos+1,flag);
    ll tmp=now/gcd(v[pos],now);
    if((double)tmp*v[pos]>R) return;
    dfs2(tmp*v[pos],pos+1,-flag);
}
int main()
{
    scanf("%lld%lld",&L,&R);
    dfs1(0,0);
    sort(v1+1,v1+1+top1);
    for(int i=1;i<=top1;i++)
    {
        bool flag=0;
        for(int j=1;j<i;j++)
            if(v1[i]%v1[j]==0) {flag=1;break;}
        if(!flag) v[++top]=v1[i];
    }
    reverse(v+1,v+1+top);
    dfs2(1,1,-1);
    printf("%lld\n",ans);
}
