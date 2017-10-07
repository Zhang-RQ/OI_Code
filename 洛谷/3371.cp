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

#define M 10010
#define N 500100
int head[M];
struct Node{
    int val,nxt,v;
}Edge[N];
int cnte=0;
int dis[M];
bool inq[M];
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}

void spfa(int s)
{
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;
    q.push(s);
    inq[s]=1;
    dis[s]=0;
    while(q.size())
    {
        int tmp=q.front();
        q.pop();inq[tmp]=0;
        for(int i=head[tmp];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[v]>dis[tmp]+Edge[i].val)
            {
                dis[v]=dis[tmp]+Edge[i].val;
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
}

int main()
{
    int n,m,s,u,v,val;
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>val;
        add(u,v,val);
    }
    spfa(s);
    for(int i=1;i<=n;i++)
    {
        if(dis[i]!=0x3f3f3f3f) printf("%d ",dis[i]);
        else printf("2147483647 ");
    }
    puts("");
}
