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

const int MAXN=1E6+10;

int a[MAXN],n;
ll s[MAXN],sum;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];
    sum/=n;
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i]-sum;
    sort(s+1,s+1+n);
    ll mid=s[(n>>1)+1],ans=0;
    for(int i=1;i<=n;i++) ans+=abs(mid-s[i]);
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}