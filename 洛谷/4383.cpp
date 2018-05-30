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
#include<cassert>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=3E5+10;
const int MAXM=6E5+5;
struct __edge{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e,n,k;
ll mid;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
struct _data{
    ll x,y;
    _data(){}
    _data(ll _,ll __):x(_),y(__){}
    inline bool operator < (const _data &rhs) const {return x==rhs.x?y>rhs.y:x<rhs.x;}
    inline _data operator + (const _data &rhs) const {return _data(x+rhs.x,y+rhs.y);}
    inline _data operator + (const ll &rhs)  const {return _data(x+rhs,y);}
}f[3][MAXN];
inline _data upd(const _data &rhs) {return _data(rhs.x-mid,rhs.y+1);}
void dfs(int x,int fa)
{
    f[2][x]=max(f[2][x],_data(-mid,1));
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x);
        f[2][x]=max(f[2][x]+f[0][v],upd(f[1][x]+f[1][v]+Edge[i].w));
        f[1][x]=max(f[1][x]+f[0][v],f[0][x]+f[1][v]+Edge[i].w);
        f[0][x]=f[0][x]+f[0][v];
    }
    f[0][x]=max(f[0][x],max(upd(f[1][x]),f[2][x]));
}
int main()
{
    ll sum=0;
    scanf("%d%d",&n,&k);++k;
    for(int i=1,u,v,w;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        sum+=abs(w);
        add(u,v,w);add(v,u,w);
    }
    ll L=-sum,R=sum;
    while(L<=R)
    {
        mid=(L+R)>>1;
        memset(f,0,sizeof f);
        dfs(1,0);
        if(f[0][1].y<=k) R=mid-1;
        else L=mid+1;
    }
    mid=L;memset(f,0,sizeof f);
    dfs(1,0);
    printf("%lld\n",1ll*L*k+f[0][1].x);
    #ifdef LOCAL
        system("pause");
    #endif
}