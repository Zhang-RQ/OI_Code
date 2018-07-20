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

const int MAXN=3E6+10;

int n,m;
int a[MAXN],cnt[MAXN];
ll ans[MAXN];


void build()
{
    scanf("%d%d",&n,&m);
    if(n>=200000)
    {
        scanf("%d",&a[1]);
        for(int i=2;i<=n;i++)
            a[i]=(1ll*a[i-1]*a[i-1]+7ll*a[i-1]+34221)%m+1;
    }
    else for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) cnt[a[i]]++;
}

int main()
{
    build();
    for(int i=1;i<=m;i++)
        if(cnt[i])
            for(int j=i,t=1;j<=m;j+=i,t++)
                ans[j]+=1ll*t*cnt[i],j+i<=m?ans[j+i]-=1ll*t*cnt[i]:0;
    for(int i=1;i<=m;i++) ans[i]+=ans[i-1];
    for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=m;i++)
        for(int j=i,t=1;j<=m;j+=i,t++)
            ans[i]+=1ll*t*((j+i-1>m?n:cnt[j+i-1])-cnt[j-1]);
    ll O=0;
    for(int i=1;i<=m;i++) O^=ans[i];
    printf("%lld\n",O);
    #ifdef LOCAL
        system("pause");
    #endif
}