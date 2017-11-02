#include <bits/stdc++.h>
using namespace std;
const int maxn=1001;
int n,m,v,tot,head[maxn*2],match[maxn],inCrossPath[maxn];
struct near{
    int to,nxt;
}Edge[maxn*maxn];
bool dfs(int x)
{
    int i=head[x];
    while (i)
    {
        int p=Edge[i].to;
        if (!inCrossPath[p])
        {
            inCrossPath[p]=1;
            if (!match[p]||dfs(match[p]))
            {
                match[p]=x;
                return 1;
            }
        }
        i=Edge[i].nxt;
    }
    return 0;
}
int main()
{
    scanf("%d %d %d",&n,&m,&v);
    int x,y;
    for (int i=1;i<=v;i++)
    {
        scanf("%d %d",&x,&y);
        if (x>n||y>m) continue;
        Edge[++tot]=(near){y,head[x]};
        head[x]=tot;
    }
    int ans=0;
    for (int i=1;i<=n;i++)
    {
        memset(inCrossPath,0,sizeof(inCrossPath));
        if (dfs(i)) ans++;
    }
    printf("%d\n",ans);
    return 0;
}


/*#include<cstdio>
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
#define MAXM 1000010
#define MAXN 1000100
int head[MAXM<<1];
struct Node{
    int v,nxt;
}Edge[MAXN<<1];
int cnte=0;
inline void add(const int u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
int n,m,e,u,v;
bool inCrossPath[100020];
int match[100200];
bool findpath(int x)
{
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int vv=Edge[i].v;
        if(!inCrossPath[vv])
        {
            inCrossPath[vv]=true;
            if(match[vv]==-1||findpath(match[vv]))
            {
                match[vv]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int ret=0;
    memset(match,-1,sizeof(match));
    for(int i=1;i<=n;i++)
    {
        memset(inCrossPath,0,sizeof(inCrossPath));
        if(findpath(i))
            ret++;
    }
    return ret;
}
int main()
{
    scanf("%d%d%d",&n,&m,&e);
    for(int i=1;i<=e;i++)
    {
        scanf("%d%d",&u,&v);
        if(v>m||u>n) continue;
        v+=2000;
        add(u,v);
    }
    printf("%d\n",hungary());
}*/
