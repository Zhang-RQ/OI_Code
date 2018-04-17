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
const int MAXN=1000100;
int a[MAXN],n;
ll f[MAXN],mx;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    mx=a[1];
    for(int i=1;i<=n;i++)
    {
        f[i]=mx;
        mx=max(mx,a[i+1]-f[i]);
    }
    printf("%lld\n",f[n]);
}
