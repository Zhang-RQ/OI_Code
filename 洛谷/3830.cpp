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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int n,q;
void solve1()
{
    double res=0;
    for(int i=2;i<=n;i++) res+=2.0/i;
    printf("%lf\n",res);
}
double f[110][110];
void solve2()
{
    double res=0;
    f[1][0]=1;f[2][1]=1;f[3][2]=1;
    for(int i=4;i<=n;i++)
        for(int j=1;j<i;j++)
            for(int k=0;k<j;k++)
                for(int l=0;l<i-j;l++)
                    f[i][max(k,l)+1]+=f[j][k]*f[i-j][l]/(i-1);
    for(int i=1;i<=n;i++) res+=f[n][i]*i;
    printf("%lf\n",res);
}
int main()
{
    scanf("%d%d",&q,&n);
    if(q==1) solve1();
    else if(q==2) solve2();
}
