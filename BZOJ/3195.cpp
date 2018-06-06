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
const int P=1E9+7;
int f[35][35][1<<10][10];
int n,m,k;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    f[1][0][0][1]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            for(int s=0;s<1<<(k+1);s++)
            {
                for(int l=1;l<=k;l++)
                {
                    int t=f[i][j][s][l];
                    (f[i][j][s][l+1]+=t)%=P;
                    if(l<=i-1) (f[i][j+1][s^(1<<k)^(1<<(k-1))][l]+=t)%=P;
                }
                if((s&1)==0) (f[i+1][j][s>>1][1]+=f[i][j][s][k])%=P;
            }
        }
    }
    printf("%d\n",f[n][m][0][k]);
    #ifdef LOCAL
        system("pause");
    #endif
}