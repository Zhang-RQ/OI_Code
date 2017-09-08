#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int cnt=0;
int head[310],val[310];
int DP[310][310];
struct Node{
    int v,nxt;
}Edge[310];
void add(int u,int v)
{
    Edge[++cnt].nxt=head[u];
    Edge[cnt].v=v;
    head[u]=cnt;
}
int n,m;
void dfs(int x)
{
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        dfs(v);
        for(int j=m+1;j>1;j--)
        {
            for(int k=j-1;k>0;k--)
            {
                DP[x][j]=max(DP[x][j],DP[v][k]+DP[x][j-k]);
            }
        }
    }
}
int main()
{
    int k;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&k,&val[i]);
        DP[i][1]=val[i];
        if(k!=0)    add(k,i);
        else    add(0,i);
    }
    dfs(0);
    printf("%d\n",DP[0][m+1]);
}
