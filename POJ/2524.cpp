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
int fa[51000];
int n,m,x,y;
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
    int t=0;
    while(scanf("%d%d",&n,&m)&&n&&m)
    {
        int ans=0;
        for(int i=1;i<=n;i++)
            fa[i]=i;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&x,&y);
            fa[find(x)]=find(y);
        }
        for(int i=1;i<=n;i++)
            if(fa[i]==i) ans++;
        t++;
        printf("Case %d: %d\n",t,ans);
    }
}
