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
bitset<1000010> F[110];
int main()
{
    int n;
    int l,r;
    scanf("%d",&n);
    F[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&l,&r);
        for(int j=l;j<=r;j++)
            F[i]|=F[i-1]<<(j*j);
    }
    printf("%d\n",F[n].count());
}
