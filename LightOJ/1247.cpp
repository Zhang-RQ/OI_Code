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
int T,n,m,x,Cs;
ll ans=0;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        ans=0;
        for(int i=1;i<=n;i++)
        {
            ll tmp=0;
            for(int j=1;j<=m;j++) scanf("%d",&x),tmp+=x;
            ans^=tmp;
        }
        printf("Case %d: ",++Cs);
        puts(ans?"Alice":"Bob");
    }
}
