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
char mp[110][110];
bool vis[110][110];
int n,m,ans;
void dfs(int x,int y,bool flag)
{
    if(vis[x][y]||mp[x][y]!='W') return;
    if(flag) ans++;
    vis[x][y]=1;
    dfs(x,y+1,0);
    dfs(x,y-1,0);
    dfs(x+1,y+1,0);
    dfs(x+1,y-1,0);
    dfs(x+1,y,0);
    dfs(x-1,y,0);
    dfs(x-1,y+1,0);
    dfs(x-1,y-1,0);
}
int main()
{
    scanf("%d%d",&n,&m);
    ans=0;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dfs(i,j,1);
    printf("%d\n",ans);
}
