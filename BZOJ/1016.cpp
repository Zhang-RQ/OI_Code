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

const int MAXN=1010;
const int P=31011;

int n,m,a[MAXN],tot[MAXN],fa[MAXN],ccnt;
vector<pair<int,int> > v[MAXN];

struct E{
    int u,v,w;
}Edge[MAXN];

int find(int x){return x==fa[x]?x:find(fa[x]);}

int dfs(int x,int val,int cnt)
{
    if(x>v[val].size()-1) return cnt==tot[val];
    int U=find(v[val][x].first),V=find(v[val][x].second),ret=0;
    if(U!=V)
    {
        fa[U]=V;
        ret+=dfs(x+1,val,cnt+1);
        fa[U]=U;fa[V]=V;
    }
    ret+=dfs(x+1,val,cnt);
    return ret;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&Edge[i].u,&Edge[i].v,&Edge[i].w),a[i]=Edge[i].w;
    sort(a+1,a+1+m);
    int cnt=unique(a+1,a+1+m)-a-1;
    for(int i=1;i<=m;i++) v[lower_bound(a+1,a+1+cnt,Edge[i].w)-a].push_back(make_pair(Edge[i].u,Edge[i].v));
    int ans=1;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,x,y;i<=cnt;i++)
    {
        for(int j=0;j<v[i].size();j++)
        {
            x=find(v[i][j].first);y=find(v[i][j].second);
            if(x!=y) tot[i]++,fa[x]=y;
        }
        ccnt+=tot[i];
    }
    if(ccnt!=n-1) return puts("0"),0;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,x,y;i<=cnt;i++)
    {
        (ans*=dfs(0,i,0))%=P;
        for(int j=0;j<v[i].size();j++)
        {
            x=find(v[i][j].first);y=find(v[i][j].second);
            if(x!=y) tot[i]++,fa[x]=y;
        }
    }
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}