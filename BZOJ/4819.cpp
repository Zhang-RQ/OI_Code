#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=300;
const int MAXM=5E4+5;
struct __edge{
    int nxt,v,f;
    double c;
}Edge[MAXM];
int head[MAXN],cnt_e=1,pre[MAXN],preedge[MAXN],S=0,T=MAXN-1,a[110][110],b[110][110],n,flw[MAXN];
double dis[MAXN];
bool inq[MAXN];
inline void add(int u,int v,int f,double c)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].f=f;
    Edge[cnt_e].c=c;
    head[u]=cnt_e;
}
inline void add2(int u,int v,int f,double c) {add(u,v,f,c),add(v,u,0,-c);}
bool spfa()
{
    queue<int> q;
    memset(dis,0xc2,sizeof dis);
    dis[S]=0;q.push(S);inq[S]=1;
    flw[S]=1<<30;
    while(q.size())
    {
        int x=q.front();q.pop();inq[x]=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            if(!Edge[i].f) continue;
            int v=Edge[i].v;
            if(dis[v]<dis[x]+Edge[i].c)
            {
                flw[v]=min(flw[x],Edge[i].f);
                dis[v]=dis[x]+Edge[i].c;
                pre[v]=x;preedge[v]=i;
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
    return dis[T]>-1E9;
}
bool check(double x)
{
    cnt_e=1;memset(head,0,sizeof head);
    for(int i=1;i<=n;i++) add2(S,i,1,0),add2(i+105,T,1,0);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            add2(i,j+105,1,a[i][j]-x*b[i][j]);
    double ans=0;
    while(spfa())
    {
        int t=T,f=flw[T];
        ans+=dis[T]*f;
        while(t!=S)
        {
            Edge[preedge[t]].f-=f;
            Edge[preedge[t]^1].f+=f;
            t=pre[t];
        }
    }
    return ans>=0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&b[i][j]);
    double L=0,R=100000;
    while(fabs(L-R)>1e-7)
    {
        double mid=(L+R)/2;
        if(check(mid)) L=mid;
        else R=mid;
    }
    printf("%lf\n",L);
}
