#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
int sum[10010],a[10010];
int flag[10010];
int N,t;
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&a[i]);
        sum[i]=sum[i-1]+a[i];
        if(sum[i]%N==0)
        {
            printf("%d\n",i);
            for(int j=1;j<=i;j++) printf("%d\n",a[j]);
            return 0;
        }
        if(flag[sum[i]%N])
        {
            printf("%d\n",i-flag[sum[i]%N]);
            for(int j=flag[sum[i]%N]+1;j<=i;j++)  printf("%d\n",a[j]);
            return 0;
        }
        flag[sum[i]%N]=i;
    }
    return 0;
}
