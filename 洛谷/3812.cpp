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
ll n,a[60],b[60],ans;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=50;j>=0;j--)
            if((a[i]>>j)&1)
            {
                if(b[j]) a[i]^=b[j];
                else
                {
                    b[j]=a[i];
                    for(int k=j-1;k>=0;k--)  if((b[j]>>k)&1) b[j]^=b[k];
                    for(int k=j+1;k<=50;k++) if((b[k]>>j)&1) b[k]^=b[j];
                    break;
                }
            }
    for(int i=50;i>=0;i--)
        ans^=b[i];
    printf("%lld\n",ans);
}
