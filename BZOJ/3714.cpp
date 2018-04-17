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
const int MAXN=2010;
const int MAXM=4000010;
struct Edge{
    int u,v,w;
    bool operator <(const Edge &rhs){return w<rhs.w;}
}E[MAXM];
int n,t,fa[MAXN],cnt;
ll ans=0;
void add(int u,int v,int w){E[++cnt].u=u;E[cnt].v=v;E[cnt].w=w;}
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
            scanf("%d",&t),add(i-1,j,t);
        fa[i]=i;
    }
    sort(E+1,E+1+cnt);
    for(int i=1;i<=cnt;i++)
    {
        if(find(E[i].u)==find(E[i].v)) continue;
        ans+=E[i].w;
        fa[find(E[i].u)]=find(E[i].v);
    }
    printf("%lld\n",ans);
}
