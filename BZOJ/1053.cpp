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

const int pri[]={1,2,3,5,7,11,13,17,19,23,29,31};

ll ans=1,ans1=1,n;

void dfs(int x,ll now,ll tans,int lst)
{
    if(x>11)
    {
        if(ans1<tans||(ans1==tans&&ans>now)) ans=now,ans1=tans;
        return;
    }
    ll tmp=1;
    for(int i=0;i<=lst;i++,tmp*=pri[x])
    {
        if(now*tmp>n) break;
        dfs(x+1,now*tmp,tans*(i+1),i);

    }
}

int main()
{
    scanf("%lld",&n);
    dfs(1,1,1,40);
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}