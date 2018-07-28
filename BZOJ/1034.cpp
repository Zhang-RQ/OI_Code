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

const int MAXN=100100;

int n,a[MAXN],b[MAXN];

int solve(int* a,int *b)
{
    int ret=0;
    int L1=1,R1=n,L2=1,R2=n;
    while(L1<=R1&&L2<=R2)
    {
        if(a[L1]>b[L2]) ++L1,++L2,ret+=2;
        else if(a[R1]>b[R2]) --R1,--R2,ret+=2;
        else ret+=(a[L1]==b[R2]),++L1,--R2;
    }
    return ret;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    sort(a+1,a+1+n);sort(b+1,b+1+n);
    printf("%d %d\n",solve(a,b),2*n-solve(b,a));
    #ifdef LOCAL
        system("pause");
    #endif
}