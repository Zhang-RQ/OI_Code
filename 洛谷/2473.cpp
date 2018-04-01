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
double f[110][(1<<15)+10];
int st[20],n,k,p[20],tt;
int main()
{
    scanf("%d%d",&k,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&p[i],&tt);
        while(tt!=0) st[i]|=1<<(tt-1),scanf("%d",&tt);
    }
    for(int i=k;i>=1;i--)
    {
        for(int s=0;s<1<<n;s++)
        {
            for(int j=1;j<=n;j++)
            {
                if((st[j]&s)==st[j]) f[i][s]+=max(f[i+1][s],f[i+1][s|(1<<(j-1))]+p[j]);
                else f[i][s]+=f[i+1][s];
            }
            f[i][s]/=n;
        }
    }
    printf("%.6lf\n",f[1][0]);
}
