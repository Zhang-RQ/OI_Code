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
typedef long long ll;
ll F[10010];
int main()
{
    F[1]=2;F[2]=7;
    for(int i=3;i<=10000;i++)
        F[i]=F[i-1]+4*(i-1)+1;
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int l;
        scanf("%d",&l);
        printf("%lld\n",F[l]);
    }
}
