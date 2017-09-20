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
int F[60];
int main()
{
    F[1]=1;F[2]=2;F[3]=3;
    for(int i=4;i<=55;i++)
    {
        F[i]=F[i-1]+F[i-3];
    }
    int n;
    while(scanf("%d",&n)&&n)
    {
        printf("%d\n",F[n]);
    }
}
