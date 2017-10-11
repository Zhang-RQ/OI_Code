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
int t,m;
int w[110],v[110];
int f[1100];
int main()
{
    scanf("%d%d",&t,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&w[i],&v[i]);
    for(int i=1;i<=m;i++)
        for(int j=t;j>=0;j--)
            f[j]=max(f[j],j>=w[i]?f[j-w[i]]+v[i]:0);
    printf("%d\n",f[t]);
}
