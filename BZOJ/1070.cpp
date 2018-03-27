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
#define id(i,j) ((i-1)*n+(j)+200)//i技术人员 倒数第j个车
const int MAXN=1E5+5;
const int MAXM=1E5+5;
struct node{
    int nxt,v,w,c;
}Edge[MAXM];
int head[MAXN],cnt_e=1,S,T=MAXN-1,n,m,a[65][65],ans;
int dis[MAXN],pre[MAXN],preedge[MAXN],flw[MAXN];
bool inq[MAXN];
inline void add(int u,int v,int w,int c)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].c=c;
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
bool spfa()
{
    queue<int> q;
    memset(inq,0,sizeof inq);
    memset(dis,0x3f,sizeof dis);
    memset(flw,0,sizeof flw);
    q.push(S);inq[S]=1;flw[S]=0x3f3f3f3f;dis[S]=0;
    while(!q.empty())
    {
        int x=q.front();q.pop();inq[x]=0;
        // printf("%d %d\n",x,dis[x]);
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(!Edge[i].w||dis[v]<=dis[x]+Edge[i].c) continue;
            dis[v]=dis[x]+Edge[i].c;
            pre[v]=x;preedge[v]=i;
            flw[v]=min(flw[x],Edge[i].w);
            if(!inq[v]) q.push(v),inq[v]=1;
        }
    }
    return dis[T]!=0x3f3f3f3f;
}
int main() //车 1~100 人 200~
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++) add(S,i,1,0),add(i,S,0,0);
    for(int i=1;i<=n*m;i++) add(i+200,T,1,0),add(T,i+200,0,0);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
                add(k,id(i,j),1,a[k][i]*j),add(id(i,j),k,0,-a[k][i]*j);
    while(spfa())
    {
        int t=T;ans+=dis[T]*flw[T];
        // printf("%d\n",flw[T]);
        while(t!=S)
        {
            Edge[preedge[t]].w-=flw[T];
            Edge[preedge[t]^1].w+=flw[T];
            t=pre[t];
        }
    }
    printf("%.2lf\n",1.0*ans/n);
}
