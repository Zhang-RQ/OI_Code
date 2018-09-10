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
#include<cassert>
 
typedef long long ll;
typedef unsigned long long ull;
 
using namespace std;
 
int tot,num[20],Cnt;
ll a[70000],L,R,L1,R1,f[19][70000][2];
map<ll,ll> t;
 
void DFS(ll x)
{
    if (x>R1||t.find(x)!=t.end()) return;
    a[++Cnt]=x;
    t.insert(make_pair(x,Cnt));
    for (int i=2;i<=9;i++) if(x<=R1/i) DFS(x*i);
}
 
ll dfs(int x,ll cur,bool lim,bool zero)//cur chengji
{
    if(x==0) return L1<=cur&&cur<=R1;
    if((!lim)&&(~f[x][t[cur]][zero]))
        return f[x][t[cur]][zero];
    ll ret=0;int lm=lim?num[x]:9;
    if(zero) ret+=dfs(x-1,cur,lim&&num[x]==0,zero);
    else ret+=dfs(x-1,0,lim&&num[x]==0,zero);
    for(int i=1;i<=lm;i++)
        ret+=dfs(x-1,cur*i,lim&&i==lm,0);
    if(!lim) f[x][t[cur]][zero]=ret;
    return ret;
}
 
ll solve(ll x)
{
    if(x<0) return 0;
    tot=0;memset(f,-1,sizeof f);
    while(x) num[++tot]=x%10,x/=10;
    return dfs(tot,1,1,1);
}
 
int main()
{
    cin>>R1;L1=1;
    cin>>L>>R;
    memset(f,-1,sizeof f);
    a[++Cnt]=0;t[0]=Cnt;DFS(1);
    printf("%lld\n",solve(R-1)-solve(L-1));
}