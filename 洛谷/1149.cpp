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
typedef unsigned long long ull;
const int num[10]={6,2,5,5,4,5,6,3,7,6};
int calc(int x)
{
    int ret=0;
    if(!x) return num[0];
    while(x)
    {
        ret+=num[x%10];
        x/=10;
    }
    return ret;
}
int main()
{
    int n,ans=0;
    scanf("%d",&n);
    n-=4;
    for(int i=0;i<=1000;i++)
    {
        for(int j=0;j<=1000;j++)
        {
            if(calc(i)+calc(j)+calc(i+j)==n)
                ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
