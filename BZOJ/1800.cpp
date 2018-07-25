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

const int MAXN=25;

int n;
ll sum[MAXN],tot,ans;

int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++) scanf("%d",&x),sum[i]=sum[i-1]+x;
    tot=sum[n];
    if(tot&1) return puts("0"),0;
    tot>>=1;
    for(int i=1,j=1;i<n;i++)
    {
        while(sum[i]-sum[j-1]>tot) ++j;
        if(sum[i]-sum[j-1]==tot) ++ans,++j; 
    }
    printf("%lld\n",ans*(ans-1)/2);
    #ifdef LOCAL
        system("pause");
    #endif
}