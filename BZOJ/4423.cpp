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
const int MAXN=1510;
int id[MAXN][MAXN],n,k,lstans,cnt,fa[MAXN*MAXN],siz[MAXN*MAXN],a,b,x,y;
char opt;
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    x=find(x);y=find(y);
    if(siz[x]<siz[y]) swap(x,y);
    fa[y]=x;siz[x]+=siz[y];
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            id[i][j]=MAXN*MAXN-1;
    for(int i=1;i<n;i++)
        for(int j=1;j<n;j++)
            id[i][j]=++cnt;
    for(int i=1;i<=cnt;i++) fa[i]=i,siz[i]=1;
    fa[MAXN*MAXN-1]=MAXN*MAXN-1,siz[MAXN*MAXN-1]=1;
    for(int i=1;i<=k;i++)
    {
        if(!lstans) scanf("%d %d %c %*d %*d %*c",&a,&b,&opt);
        else scanf("%*d %*d %*c %d %d %c",&a,&b,&opt);
        if(opt=='N') x=id[a-1][b],y=id[a][b];
        else x=id[a][b-1],y=id[a][b];
        lstans=(find(x)==find(y));
        if(!lstans) merge(x,y);
        puts(lstans?"NIE":"TAK");
    }
}
