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
ll b[60],a[60];
int n;
void insert(ll val)
{
    for(int i=50;~i;i--)
        if((val>>i)&1)
        {
            if(b[i]) val^=b[i];
            else {b[i]=val;break;}
        }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),insert(a[i]);
    int cnt=0;ll mx=0,ans=0;
    for(int i=50;~i;i--)
    {
        if(b[i])
        {
            ++cnt;
            if((mx^b[i])>mx) mx=mx^b[i];
        }
    }
    ans=mx*(n-cnt+1);cnt--;
    for(int i=0;i<=50&&cnt;i++)
        if(b[i])
        {
            for(int j=i-1;j>=0;j--)
                if(b[j]&&((b[i]>>j)&1))
                    b[i]^=b[j];
            cnt--;
            ans+=mx^b[i];
        }
    printf("%lld\n",ans);  
    #ifdef LOCAL
        system("pause");
    #endif
}