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
#define int ll
#define id(x,y) (x)+(y)*40
int val[45][45];
const int MAXN=2100;
const int MAXM=4E4+10;
const ll INF=1ll<<60;
struct node{
    int nxt,v;ll w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,ll w,ll w2)
{
    //printf("%d %d %d\n",u,v,w);
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
    Edge[++cnt_e].v=u;
    Edge[cnt_e].nxt=head[v];
    Edge[cnt_e].w=w2;
    head[v]=cnt_e;
}
int lvl[MAXN],n,m,s=0,t=MAXN-1,T;
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof lvl);
    lvl[s]=1;q.push(s);
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].w)
                continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[t]!=0;
}
int dfs(int x,ll flow)
{
    if(x==t) return flow;
    ll add_flow=0;
    for(int i=head[x];i&&add_flow<flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].w)
            continue;
        ll min_flow=dfs(v,min(flow-add_flow,Edge[i].w));
        if(!min_flow) lvl[v]=0;
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
bool check(ll X)
{
    ll tot=0,ans=0;
    cnt_e=1;memset(head,0,sizeof head);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if((i+j)&1)
            {
                add(s,id(i,j),X-val[i][j],0),tot+=X-val[i][j];
                if(i!=1) add(id(i,j),id(i-1,j),INF,0);
                if(i!=n) add(id(i,j),id(i+1,j),INF,0);
                if(j!=1) add(id(i,j),id(i,j-1),INF,0);
                if(j!=m) add(id(i,j),id(i,j+1),INF,0);
            }
            else add(id(i,j),t,X-val[i][j],0);
        }
    while(bfs())
        ans+=dfs(s,INF);
    return ans==tot;
}
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        ll sum1=0,sum2=0;
        ll cnt1=0,cnt2=0,maxv=0;
        scanf("%lld%lld",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                scanf("%lld",&val[i][j]),maxv=max(maxv,(ll)val[i][j]);
                if((i+j)&1) sum1+=val[i][j],cnt1++;
                else sum2+=val[i][j],cnt2++;
            }
        if(cnt1!=cnt2)
        {
            ll X=(sum1-sum2)/(cnt1-cnt2);
            if(X<=maxv) puts("-1");
            else if(check(X)) printf("%lld\n",1ll*X*cnt1-sum1);
            else puts("-1");
        }
        if(cnt1==cnt2)
        {
            ll ans=-1,L=maxv,R=1ll<<50;
            while(L<=R)
            {
                ll mid=(L+R)>>1;
                if(check(mid)) R=mid-1,ans=mid;
                else L=mid+1;
            }
            if(ans!=-1) printf("%lld\n",ans*cnt1-sum1);
            else puts("-1");
        }
    }
}
