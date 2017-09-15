#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
#define M 310
#define N 5000
struct edge{
    int u,v,val;
    friend bool operator < (edge a,edge b)
    {
        return a.val>b.val;
    }
    edge(){}
    edge(int _u,int _v,int _val){v=_v;u=_u;val=_val;}
};
priority_queue<edge> q;
int cnt=0;
 int fa[M];
int find(int x)
{
    if(fa[x]==x) return x;
    else return fa[x]=find(fa[x]);
}
int n,m;
int ans=0;
int main()
{
    scanf("%d%d",&n,&m);
    int u,v,c;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&c);
        q.push(edge(u,v,c));
    }
    for(int i=1;i<=n;i++) fa[i]=i;
    while(q.size())
    {
        edge tmp=q.top();
        q.pop();
        int fv=find(tmp.v);
        int fu=find(tmp.u);
        if(fv!=fu)
        {
            fa[fv]=fu;
            ans=tmp.val;
        }
    }
    printf("%d %d\n",n-1,ans);
}
