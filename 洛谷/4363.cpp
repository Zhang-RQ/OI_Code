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
const int MAXN=12;
int sts[MAXN],n;
map<ll,int> mp;
int a[MAXN][MAXN],b[MAXN][MAXN],m;
ll zip()
{
    ll ret=0;
    for(int i=1;i<=n;i++)  ret=sts[i]+ret*MAXN;
    return ret;
}
void unzip(ll s)
{
    for(int i=n;i>=1;i--) sts[i]=s%MAXN,s/=MAXN;
}
int dfs(ll s)
{
    if(mp.find(s)!=mp.end()) return mp[s];
    unzip(s);
    int tpe=0;
    for(int i=1;i<=n;i++) tpe+=sts[i];
    tpe&=1; //tpe=0,max;tpe=1,min
    int ret=tpe?1<<30:-1<<30;
    for(int i=1;i<=n;i++)
    {
        if(sts[i-1]<=sts[i]) continue;
        sts[i]++;
        ll t=zip();
        if(tpe) ret=min(ret,dfs(t)-b[i][sts[i]]);
        else ret=max(ret,dfs(t)+a[i][sts[i]]);
        sts[i]--;
    }
    return mp[s]=ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&b[i][j]);
    sts[0]=m;
    for(int i=1;i<=n;i++)  sts[i]=m;
    ll ful=zip();mp[ful]=0;
    printf("%d\n",dfs(0));
}
