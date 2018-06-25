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

#define DEBUG fprintf(stderr,"Passing Line %d in function \"%s\"\n",__LINE__,__FUNCTION__)

const int MAXN=1E5+10;

struct node{
    int x,v,n;
    node(){}
    node(int _x,int _v,int _n){x=_x;v=_v;n=_n;}
    inline bool operator < (const node &rhs) const {return v<rhs.v;}  
};


int n,m,k,cnt,num[MAXN];
int mx,fa[MAXN],q[MAXN],g[MAXN*10];
ll ans[MAXN];
bool vis[MAXN];
priority_queue<node> pq;

int find(int x) {return x>mx?find(mx):(x==fa[x]?x:fa[x]=find(fa[x]));}

int main()
{
    freopen("vegetables21.in","r",stdin);
    freopen("vegetables21.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1,a,s,c,x;i<=n;i++)
    {
        scanf("%d%d%d%d",&a,&s,&c,&x);
        if(c>1) pq.push(node(x,a,c-1));
        pq.push(node(-1*(x?(c-1)/x+1:100000),a+s,1));
    }
    for(int i=1;i<=k;i++) scanf("%d",&q[i]),mx=max(q[i],mx);
    for(int i=1;i<=mx;i++) fa[i]=i,num[i]=m;
    while(!pq.empty())
    {
        node t=pq.top();pq.pop();
        if(t.x<0)
        {
            int p=find(-t.x);
            if(!p) continue;
            num[p]-=1;
            g[++cnt]=t.v;ans[mx]+=t.v;
            if(!num[p]) fa[p]=find(p-1);
        }
        else
        {
            int p=t.x?(t.n-1)/t.x+1:mx,np=find(p);
            int cur=t.n-(np-1)*t.x,nm;p=np;
            while(p)
            {
                if(!cur) break;
                nm=min(num[p],cur);
                ans[mx]+=1ll*nm*t.v;
                num[p]-=nm;cur-=nm;
                while(nm--) g[++cnt]=t.v;
                if(!num[p]) fa[p]=find(p-1);
                np=find(p-1);cur+=(p-np)*t.x;
                p=np;
            }
        }
    }
    sort(g+1,g+1+cnt);
    int pt=1;ll cur=ans[mx];
    for(int i=mx-1;i>=1;i--)
    {
        while(cnt-pt+1>i*m) cur-=g[pt++]; 
        ans[i]=cur;
    }
    for(int i=1;i<=k;i++)
        printf("%lld\n",ans[q[i]]);
    #ifdef LOCAL
        system("pause");
    #endif
}