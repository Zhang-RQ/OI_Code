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
int num[12];
ll f[12][12][12][2][2][2];
ll dfs(int len,int llst,int lst,bool h8,bool h4,bool lim,bool _f)
{
    if(h8&&h4) return 0;
    if(!len) return _f&&(!(h8&&h4));
    if(!lim&&f[len][llst][lst][h8][h4][_f]!=-1) return f[len][llst][lst][h8][h4][_f];
    int mx=lim?num[len]:9;
    ll ret=0;
    for(int i=len==11?1:0;i<=mx;i++)
        ret+=dfs(len-1,lst,i,h8||i==8,h4||i==4,lim&&i==mx,_f||(llst==lst&&lst==i));
    if(!lim) f[len][llst][lst][h8][h4][_f]=ret;
    return ret;
}
ll solve(ll x)
{
    int tot=1;
    for(tot=1;tot<=11;tot++,x/=10)
        num[tot]=x%10;
    memset(f,-1,sizeof f);
    return dfs(tot,10,10,0,0,1,0);
}
int main()
{
    ll L,R;
    scanf("%lld%lld",&L,&R);
    printf("%lld\n",solve(R)-solve(L-1));
}
