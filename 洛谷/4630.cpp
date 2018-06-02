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
const int MAXN=1E5+5;
const int MAXM=4E5+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int cnt,w[MAXN<<1],siz[MAXN<<1],dfn[MAXN],dft,low[MAXN],n,m,tsiz;
ll ans;
vector<int> son[MAXN<<1];
stack<int> stk;
void tarjan(int x,int fa)
{
    dfn[x]=low[x]=++dft;stk.push(x);
    w[x]=-1;siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        if(dfn[v]) low[x]=min(low[x],dfn[v]);
        else
        {
            tarjan(v,x);low[x]=min(low[x],low[v]);
            if(low[v]>=dfn[x])
            {
                int t;++cnt;w[cnt]=1;
                do{
                    t=stk.top();stk.pop();
                    son[cnt].push_back(t);
                    w[cnt]++;
                    siz[cnt]+=siz[t];
                }while(t!=v);
                son[x].push_back(cnt);
                siz[x]+=siz[cnt];
            }
        }
    }
}
void dfs(int x)
{
    int tmp=x<=n;
    for(auto v:son[x])
    {
        dfs(v);
        ans+=1ll*w[x]*tmp*siz[v];
        tmp+=siz[v];
    }
    ans+=1ll*w[x]*(tsiz-siz[x])*siz[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    cnt=n;
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i,0),tsiz=siz[i],dfs(i);
    printf("%lld\n",ans<<1);
    #ifdef LOCAL
        system("pause");
    #endif
}