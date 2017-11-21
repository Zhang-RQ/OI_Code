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
const int MAXN=1000010;
const int MAXM=2000010;
const int P=100003;
int head[MAXN];
struct Node{
    int val,nxt,v;
}Edge[MAXM<<1];
int cnte=0;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
int ans[MAXN],n,m,u,v,dis[MAXN];
bool inq[MAXN];
void spfa()
{
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;
    q.push(1);
    inq[1]=1;
    ans[1]=1;dis[1]=0;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();inq[x]=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[v]>dis[x]+Edge[i].val)
            {
                dis[v]=dis[x]+Edge[i].val;
                if(!inq[v])
                {
                    inq[v]=1;
                    ans[v]=ans[x];
                    q.push(v);
                }
            }
            else if(dis[v]==dis[x]+Edge[i].val)
                (ans[v]+=ans[x])%=P;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v,1);
        add(v,u,1);
    }
    spfa();
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
}
