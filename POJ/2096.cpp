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
double f[1005][1005];
int n,s;
double ns;
int main()
{
    scanf("%d%d",&n,&s);
    f[n][s]=0;ns=n*s;
    for(int i=n;~i;i--)
        for(int j=s;~j;j--)
            if(!(i==n&&j==s))
                f[i][j]=(f[i+1][j]*(n-i)*j+f[i][j+1]*i*(s-j)+f[i+1][j+1]*(n-i)*(s-j)+ns)/(ns-i*j);
    printf("%.4lf\n",f[0][0]);
}
