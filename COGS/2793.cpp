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
int ch[200010],sum[200010];
int main()
{
    freopen("coffee.in","r",stdin);
    freopen("coffee.out","w",stdout);
    int n,q,k;
    int l,r;
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&l,&r);
        ch[l]++;
        ch[r+1]--;
    }
    for(int i=1;i<=200005;i++)
    {
        ch[i]=ch[i]+ch[i-1];
        sum[i]=sum[i-1];
        if(ch[i]>=k) sum[i]++;
    }
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&l,&r);
        printf("%d\n",sum[r]-sum[l-1]);
    }
}
