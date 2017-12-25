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
const int P=80112002;
const int MAXN=6000;
const int MAXM=500010;
bool flag[MAXN];
int head[MAXN],in[MAXN],out[MAXN];
ll ans[MAXN],ansn;
struct Node{
    int v,nxt;
}Edge[MAXM];
int cnte=0,n,m;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    ++in[v];
    ++out[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
void solve()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(!in[i])
            q.push(i),
            ans[i]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            (ans[v]+=ans[x])%=P;
            --in[v];
            if(!in[v])
                q.push(v);
        }
    }
    for(int i=1;i<=n;i++)
        if(!out[i])
            (ansn+=ans[i])%=P;
}
int x,y;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&x,&y),
        add(x,y);
    solve();
    printf("%lld\n",ansn);
}
