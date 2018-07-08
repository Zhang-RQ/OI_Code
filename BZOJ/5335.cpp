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
const int MAXM=1E5+5;

struct __edge{
    int nxt,v;
}Edge[MAXM];


int head[MAXN],cnt_e,mat[MAXN];
bool g[510][510],S=0,T=MAXN-1,g2[MAXN][MAXN];
int n,m,val[MAXN],mx,lvl[MAXN];
bool usd[MAXN];
queue<int> q;

inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

bool dfs(int x)
{
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(usd[v]) continue;
        usd[v]=1;
        if(!mat[v]||dfs(mat[v]))
            return mat[v]=x,1;
    }
    return 0;
}

bool check(int x)
{
    memset(head,0,sizeof head);memset(g2,0,sizeof g2);
    cnt_e=0;int ans=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            if(val[i]<=x&&val[j]<=x&&g[i][j]) g2[i][j]=1;
    for(int k=1;k<=m;k++)
        for(int i=1;i<=m;i++)
            if(g2[i][k])
                for(int j=1;j<=m;j++)
                    g2[i][j]|=g2[i][k]&&g2[k][j];
    for(int i=1;i<=m;i++)
    {
        if(val[i]<=x) ++ans;
        else continue;
        for(int j=1;j<=m;j++)
            if(g2[i][j]) add(i,j);
    }
    memset(mat,0,sizeof mat);
    for(int i=1;i<=m;i++)
    {
        if(val[i]>x) continue;
        memset(usd,0,sizeof usd);
        if(dfs(i)) --ans;
    }
    return ans<=n;
}

int main()
{
    scanf("%d%d",&n,&m);++n;
    for(int i=1,k;i<=m;i++)
    {
        scanf("%d%d",&val[i],&k);
        mx=max(mx,val[i]);
        for(int j=1,x;j<=k;j++)
            scanf("%d",&x),g[i][x]=1;
    }
    for(int k=1;k<=m;k++)
        for(int i=1;i<=m;i++)
            if(g[i][k])
                for(int j=1;j<=m;j++)
                    if(i!=j) g[i][j]|=g[i][k]&&g[k][j];
    int L=0,R=mx;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(check(mid)) L=mid+1;
        else R=mid-1;
    }
    if(L>mx) puts("AK");
    else  printf("%d\n",L);
    #ifdef LOCAL
        system("pause");
    #endif
}