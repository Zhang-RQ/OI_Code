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
int mp[110][110],f[110][110];
int n,m;
inline bool inside(const int &x,const int &y)
{
    return 1<=x&&x<=n&&1<=y&&y<=m;
}
int DP(int i,int j)
{
    if(f[i][j]) return f[i][j];
    if(inside(i-1,j)&&mp[i-1][j]>mp[i][j]) f[i][j]=max(f[i][j],DP(i-1,j)+1);
    if(inside(i,j+1)&&mp[i][j+1]>mp[i][j]) f[i][j]=max(f[i][j],DP(i,j+1)+1);
    if(inside(i+1,j)&&mp[i+1][j]>mp[i][j]) f[i][j]=max(f[i][j],DP(i+1,j)+1);
    if(inside(i,j-1)&&mp[i][j-1]>mp[i][j]) f[i][j]=max(f[i][j],DP(i,j-1)+1);
    return f[i][j];
}
int main()
{
    int ans=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans=max(ans,DP(i,j));
    printf("%d\n",ans+1);
}
