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
int T,n,x,Cs;
ll ans;
int sg(int x)
{
    while(x&1) x>>=1;
    return x>>1;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ans=0;
        while(n--) scanf("%d",&x),ans^=sg(x);
        printf("Case %d: ",++Cs);
        puts(ans?"Alice":"Bob");
    }
}
