#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
long long F[60];
int main()
{
    F[1]=F[2]=1;
    for(int i=3;i<=55;i++) F[i]=F[i-1]+F[i-2];
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%lld\n",F[r-l+1]);
    }
}
