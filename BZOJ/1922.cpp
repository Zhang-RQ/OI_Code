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
#define MAXN 3100
#define MAXM 71000
struct node{
    int v,val,nxt;
}Edge[MAXM];
int head[MAXN],lim[MAXN];
int cnte=0;
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
int n,m,t1,t2,t3,dis1[MAXN],dis2[MAXN];
vector<int> lm[MAXN];
bool vis[MAXN];
struct A{
    int pnt,dis;
    A(){}
    A(int pnt,int dis):pnt(pnt),dis(dis){}
    bool operator < (const A a)const
    {
        return dis>a.dis;
    }
};
void dij(int s)
{
    memset(dis1,0x3f,sizeof(dis1));
    dis1[s]=0;dis2[s]=0;
    priority_queue<A> q;
    q.push(A(s,0));
    while(q.size())
    {
        int x=q.top().pnt;
        int ds=q.top().dis;
        q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        //printf("init:x=%d\n",x);
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            //printf("fst:i=%d\n",i);
            int v=Edge[i].v;
            if(dis1[v]>ds+Edge[i].val)
            {
                dis1[v]=Edge[i].val+ds;
                if(!lim[v])
                    q.push(A(v,max(dis1[v],dis2[v])));
            }
        }
        for(int i=0;i<lm[x].size();i++)
        {
            //printf("scd:i=%d\n",i);
            int v=lm[x][i];
            dis2[v]=max(dis2[v],ds);
            lim[v]--;
            if(!lim[v])
                q.push(A(v,max(dis1[v],dis2[v])));
        }
    //    printf("eve:x=%d,size=%d\n",x,q.size());
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&t1,&t2,&t3);
        add(t1,t2,t3);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&lim[i]);
        for(int j=1;j<=lim[i];j++)
            scanf("%d",&t1),
            lm[t1].push_back(i);
    }
    dij(1);
    //puts("233");
    printf("%d\n",max(dis1[n],dis2[n]));
}
