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
#define MAXM 500010
#define MAXN 500010
struct mp{
    int head[MAXM];
    struct Node{
        int v,nxt,u;
    }Edge[MAXN];
    int cnte;
    inline void add(const int &u,const int &v)
    {
        Edge[++cnte].nxt=head[u];
        Edge[cnte].u=u;
        Edge[cnte].v=v;
        head[u]=cnte;
    }
}map1,map2;
int DFN[MAXN],LOW[MAXN],belong[MAXN],money[MAXN],sum[MAXN],ans[MAXN];
int cnt=0,n,m,cntt=0,t1,t2,S,P,anss;
bool ins[MAXN],inq[MAXN];
vector<int> pub;
stack<int> s;
void tarjan(int x,int fa)
{
    s.push(x);ins[x]=1;
    DFN[x]=LOW[x]=++cnt;
    for(int i=map1.head[x];i;i=map1.Edge[i].nxt)
    {
        int v=map1.Edge[i].v;
        if(v==fa) continue;
        if(!DFN[v])
            tarjan(v,x),
            LOW[x]=min(LOW[x],LOW[v]);
        else if(ins[v])
            LOW[x]=min(LOW[x],DFN[v]);
    }
    if(LOW[x]==DFN[x])
    {
        ++cntt;
        while(s.top()!=x)
        {
            sum[cntt]+=money[s.top()];
            belong[s.top()]=cntt;
            ins[s.top()]=0;
            s.pop();
        }
        sum[cntt]+=money[x];
        ins[x]=0;
        s.pop();
        belong[x]=cntt;
    }
}
void spfa()
{
    for(int i=1;i<=cntt;i++)
        ans[i]=sum[i];
    queue<int> q;
    q.push(belong[S]);
    inq[belong[S]]=1;
    while(q.size())
    {
        int x=q.front();
        q.pop();inq[x]=0;
        for(int i=map2.head[x];i;i=map2.Edge[i].nxt)
        {
            int v=map2.Edge[i].v;
            if(ans[v]<ans[x]+sum[v])
            {
                ans[v]=ans[x]+sum[v];
                if(!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
}
int main()
{
    map1.cnte=map2.cnte=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&t1,&t2);
        map1.add(t1,t2);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&money[i]);
    scanf("%d%d",&S,&P);
    for(int i=1;i<=P;i++)
        scanf("%d",&t1),
        pub.push_back(t1);
    tarjan(S,0);
    for(int i=1;i<=m;i++)
        if(belong[map1.Edge[i].u]!=belong[map1.Edge[i].v])
            map2.add(belong[map1.Edge[i].u],belong[map1.Edge[i].v]);
    spfa();
    for(int i=0;i<(signed)pub.size();i++)
        anss=max(anss,ans[belong[pub[i]]]);
    printf("%d\n",anss);
}
