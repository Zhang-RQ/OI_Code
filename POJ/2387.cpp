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
#define M 1010
#define N 1010
#define v(i) Edge[i].v
int head[M];
struct Node{
    int val,nxt,v;
}Edge[N<<2];
int cnte=0;
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
int n,dis[N];
bool inq[N];
queue<int> q;
void spfa(int s)
{
    memset(dis,0x3f,sizeof(dis));
    memset(inq,0,sizeof(inq));
    inq[s]=1;q.push(s);
    dis[s]=0;
    while(q.size())
    {
        int x=q.front();
        q.pop();inq[x]=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            if(dis[v(i)]>Edge[i].val+dis[x])
            {
                dis[v(i)]=Edge[i].val+dis[x];
                if(!inq[v(i)]) q.push(v(i)),inq[v(i)]=1;
            }
        }
    }
}
int main()
{
    int n,t,u,v,val;
    scanf("%d%d",&t,&n);
    for(int i=1;i<=t;i++)
    {
        scanf("%d%d%d",&u,&v,&val);
        add(u,v,val);
        add(v,u,val);
    }
    spfa(n);
    printf("%d\n",dis[1]);
}
