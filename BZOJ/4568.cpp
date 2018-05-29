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
const int MAXN=20010;
const int MAXM=4E4+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,jmp[MAXN][17],n,q,dep[MAXN],flag;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
struct Linear_Base{
    ll b[64];
    inline ll& operator [] (const int &i) {return b[i];}
    inline const ll& operator [] (const int &i) const {return b[i];}
    Linear_Base(){memset(b,0,sizeof b);}
    inline void clear(){memset(b,0,sizeof b);}
    inline void insert(ll val)
    {
        for(int i=60;~i;i--)
            if((val>>i)&1)
            {
                if(b[i]) val^=b[i];
                else {b[i]=val;break;}
            }
    }
}LB[MAXN][17],T1;
ll val[MAXN];
inline Linear_Base merge(const Linear_Base &lhs,const Linear_Base &rhs)
{
    Linear_Base ret=lhs;
    for(int i=60;~i;i--) if(rhs[i]) ret.insert(rhs[i]);
    return ret;
}
void dfs(int x,int fa)
{
    jmp[x][0]=fa;LB[x][0].insert(val[fa]);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dep[v]=dep[x]+1;
        dfs(v,x);
    }
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%lld",&val[i]),LB[i][0].insert(val[i]);
    for(int i=1,u,v;i<n;i++)  scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dfs(1,0);
    for(int j=1;j<=16;j++)
        for(int i=1;i<=n;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1],LB[i][j]=merge(LB[i][j-1],LB[jmp[i][j-1]][j-1]);
    ll ans=0;
    for(int i=1,u,v;i<=q;i++)
    {
        T1.clear();
        ans=0;
        scanf("%d%d",&u,&v);
        if(dep[u]>dep[v]) swap(u,v);
        T1.insert(val[u]);T1.insert(val[v]);
        for(int j=16;~j;j--)
            if(dep[jmp[v][j]]>=dep[u]) T1=merge(T1,LB[v][j]),v=jmp[v][j];
        for(int j=16;~j;j--)
            if(jmp[u][j]!=jmp[v][j])
                T1=merge(T1,LB[u][j]),T1=merge(T1,LB[v][j]),u=jmp[u][j],v=jmp[v][j];
        T1=merge(T1,T1);
        if(u!=v) T1.insert(val[jmp[u][0]]);
        for(int j=60;~j;j--)
            if((ans^T1[j])>ans) ans=ans^T1[j];
        printf("%lld\n",ans);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}