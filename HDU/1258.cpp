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
#define M 510
#define N 1100
int alist[M];
struct Node{
    int v,nxt;
}Edge[N];
int cnt=0;
void add(int u,int v)
{
    Edge[++cnt].nxt=alist[u];
    Edge[cnt].v=v;
    alist[u]=cnt;
 }
int in[N];
bool vis[N];
queue<int>  q;
vector<int> ve;
int n,m;
int u,v;
void bfs()
{
    while(q.size())
    {
        int tmp=q.front();q.pop();
        ve.push_back(tmp);
        vis[tmp]=1;
        for(int i=alist[tmp];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            --in[v];
            if(!in[v]&&!vis[v]) q.push(v);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);
        in[v]++;
    }
    for(int i=1;i<=n;i++)  if(!in[i]) q.push(i);
    bfs();
    for(int i=0;i<ve.size();i++) printf("%d ",ve[i]);
    printf("\n");
}
