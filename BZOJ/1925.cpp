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

const int MAXN=4250;

int n,P;
ll f[2][MAXN];

int main()
{
    scanf("%d%d",&n,&P);
    f[1][1]=1;
    for(int i=2;i<=n;i++)
    {
        int now=i&1;
        for(int j=1;j<=i;j++)
            f[now][j]=(f[now][j-1]+f[now^1][i-j])%P;
    }
    if(n==1) return puts("1"),0;
    printf("%lld\n",f[n&1][n]*2%P);
    #ifdef LOCAL
        system("pause");
    #endif
}