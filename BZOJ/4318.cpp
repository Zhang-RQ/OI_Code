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

int n;
double l1[MAXN],l2[MAXN],f[MAXN],a;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf",&a);
        l1[i]=(l1[i-1]+1)*a;
        l2[i]=(l2[i-1]+2*l1[i-1]+1)*a;
        f[i]=f[i-1]+(3*l2[i-1]+3*l1[i-1]+1)*a;
    }
    printf("%.1lf\n",f[n]);
    #ifdef LOCAL
        system("pause");
    #endif
}