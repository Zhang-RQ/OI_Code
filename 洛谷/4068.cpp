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
const int MAXN=1010;
const int MAXM=1E5+5;
struct node{
    int nxt,v,f;
    ll c;
}Edge[MAXM];
int head[MAXN],cnt_e=1,S,T=MAXN-1,n,a[210],b[210],c[210],cnt[210];
inline void add(int u,int v,int f,ll c)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].f=f;
    Edge[cnt_e].c=c;
    head[u]=cnt_e;
}
int pre[MAXN],preedge[MAXN],flw[MAXN];
bool inq[MAXN];
ll dis[MAXN];
int get(int x){
    int ret=0;
    for(int i=2;i*i<=x;i++){
        if(x%i)
            continue;
        while(x%i==0)
            ret++,x/=i;
    }
    return ret+(x>1);
}
bool spfa()
{
    memset(dis,192,sizeof dis);
    queue<int> q;
    q.push(S);dis[S]=0;inq[S]=1;
    flw[S]=0x3f3f3f3f;
    while(!q.empty())
    {
        int x=q.front();q.pop();inq[x]=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[v]>=dis[x]+Edge[i].c||!Edge[i].f) continue;
            flw[v]=min(flw[x],Edge[i].f);
            dis[v]=dis[x]+Edge[i].c;
            pre[v]=x;preedge[v]=i;
            if(!inq[v]) q.push(v),inq[v]=1;
        }
    }
    return dis[T]!=-4557430888798830400ll;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),cnt[i]=get(a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<=n;i++)
        if(cnt[i]&1)
        {
            add(S,i,b[i],0),add(i,S,0,0);
            for(int j=1;j<=n;j++)
                if((cnt[j]==cnt[i]-1&&a[i]%a[j]==0)||(cnt[i]==cnt[j]-1&&a[j]%a[i]==0))
                    add(i,j,0x3f3f3f3f,1ll*c[i]*c[j]),add(j,i,0,-1ll*c[i]*c[j]);
        }
        else add(i,T,b[i],0),add(T,i,0,0);
    ll maxcost=0,maxflow=0;
    while(spfa())
    {
        int t=T,fw=flw[T];
        if(fw*dis[T]+maxcost<0)
        {
            maxflow+=maxcost/(-dis[T]);
            break;
        }
        while(t!=S)
        {
            Edge[preedge[t]].f-=fw;
            Edge[preedge[t]^1].f+=fw;
            t=pre[t];
        }
        maxflow+=fw;maxcost+=fw*dis[T];
    }
    printf("%lld\n",maxflow);
}
