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
#define MAXN 110
#define MAXM 200010
int U[MAXN],C[MAXN];
int in[MAXN],lvl[MAXN];
int n,m,maxl=1;
int head[MAXN];
struct Node{
    int val,nxt,v;
}Edge[MAXM];
int cnte=0;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
    ++in[v];
}
void bfs()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(!in[i])  q.push(i),lvl[i]=1;
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            C[v]+=C[x]*Edge[i].val;
            --in[v];
            lvl[v]=lvl[x]+1;
            maxl=max(lvl[v],maxl);
            if(!in[v])
            {
                C[v]-=U[v];
                if(C[v]>0)
                    q.push(v);
            }
        }
    }
}
int main()
{
    vector<int> ans;
    int u,v,val;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&C[i],&U[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&val);
        add(u,v,val);
    }
    bfs();
    for(int i=1;i<=n;i++)
        if(lvl[i]==maxl&&C[i]>0)
            ans.push_back(i);
    if(!ans.size())
        puts("NULL");
    else for(int i=0;i<(signed)ans.size();i++)
        printf("%d %d\n",ans[i],C[ans[i]]);
}
