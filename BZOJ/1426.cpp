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
const int MAXN=1E5+10;
double f[MAXN],g[MAXN];
int n;
int main()
{
    scanf("%d",&n);
    f[n]=0;
    for(int i=n-1;~i;i--)
        f[i]=f[i+1]+1.0*n/(n-i);
    g[n]=0;
    for(int i=n-1;~i;i--)
        g[i]=1.0*i/(n-i)*f[i]+f[i+1]+g[i+1]+1.0*n/(n-i);
    printf("%.2lf\n",g[0]);
    #ifdef LOCAL
        system("pause");
    #endif
}