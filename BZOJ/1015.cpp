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

const int MAXN=4E5+10;

int n,m,k,a[MAXN],ans[MAXN],fa[MAXN],tans;
bool ban[MAXN];
vector<int> v[MAXN];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

bool merge(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return 0;
    fa[x]=y;
    return 1;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,x,y;i<=m;i++) scanf("%d%d",&x,&y),++x,++y,v[x].push_back(y),v[y].push_back(x);
    scanf("%d",&k);tans=n-k;
    for(int i=1;i<=k;i++) scanf("%d",&a[i]),ban[++a[i]]=1;
    for(int i=1;i<=n;i++)
        if(!ban[i])
            for(int j=0;j<v[i].size();j++)
                if(!ban[v[i][j]]) tans-=merge(i,v[i][j]);
    for(int i=k;i;i--)
    {
        ans[i]=tans;ban[a[i]]=0;
        for(int j=0;j<v[a[i]].size();j++)
            if(!ban[v[a[i]][j]]) tans-=merge(a[i],v[a[i]][j]);
        ++tans;
    }
    ans[0]=tans;
    for(int i=0;i<=k;i++) printf("%d\n",ans[i]);
    #ifdef LOCAL
        system("pause");
    #endif
}