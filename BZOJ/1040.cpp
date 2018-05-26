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
#define MAXM 2000010
#define MAXN 1000010

char B[1<<26],*S=B;
int F()
{
    for(;*S<'-';S++);
    int x=*S++-'0';
    for(;*S>='0';x=(x<<3)+(x<<1)+*S++-'0');
    return x;
}
int head[MAXM];
struct Node{
    int v,nxt;
}Edge[MAXM];
int cnte=0;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
struct node{
    int u,v;
    node(){}
    node(int u,int v):u(u),v(v){}
}EE[MAXN];
int fa[MAXN],val[MAXN],top;
ll f[MAXN][2],ans=0;
int n,t1;
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void dfs(int x,int father)
{
    f[x][0]=0;f[x][1]=val[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) continue;
        dfs(v,x);
        f[x][1]+=f[v][0];
        f[x][0]+=max(f[v][0],f[v][1]);
    }
}
signed main()
{
    fread(B,1,1<<25,stdin);
    n=F();
    for(int i=1;i<=n;i++)  fa[i]=i;
    for(int i=1;i<=n;i++)
    {
        val[i]=F();t1=F();
        if(find(i)!=find(t1))
        {
            add(i,t1);add(t1,i);
            fa[find(i)]=find(t1);
        }
        else EE[++top]=node(i,t1);
    }
    for(int i=1;i<=top;i++)
    {
        ll t=0;
        dfs(EE[i].u,0);t=f[EE[i].u][0];
        dfs(EE[i].v,0);t=max(t,f[EE[i].v][0]);
        ans+=t;
    }
    printf("%lld\n",ans);
}
