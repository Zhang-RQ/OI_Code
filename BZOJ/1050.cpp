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

const int MAXN=510;
const int MAXM=5010;

struct __edge{
    int u,v,w;
    bool operator < (const __edge &rhs) const {return w<rhs.w;}
}Edge[MAXM];

int fa[MAXN],n,m,s,t;
int ans1,ans2; //ans=ans1/ans2

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

inline void init(){for(int i=1;i<=n;i++) fa[i]=i;}

inline bool check(int L,int R)
{
    init();
    for(int i=L,x,y;i<=R;i++)
    {
        x=find(Edge[i].u);y=find(Edge[i].v);
        if(x!=y) fa[x]=y;
    } 
    return find(s)==find(t);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&Edge[i].u,&Edge[i].v,&Edge[i].w);
    scanf("%d%d",&s,&t);
    sort(Edge+1,Edge+1+m);
    for(int L=1,lstval;L<=m;)
    {
        int l=L,r=m,ans=0;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(check(L,mid)) r=mid-1,ans=mid;
            else l=mid+1;
        }
        if(ans)
        {
            if(!ans1||(1ll*ans1*Edge[L].w>1ll*ans2*Edge[ans].w))
                ans1=Edge[ans].w,ans2=Edge[L].w;
        }
        lstval=Edge[L].w;
        while(Edge[L+1].w==lstval) ++L;
        ++L;
    }
    if(ans1==0) return puts("IMPOSSIBLE"),0;
    int d=__gcd(ans1,ans2);
    ans1/=d;ans2/=d;
    if(ans2!=1) printf("%d/%d\n",ans1,ans2);
    else printf("%d\n",ans1);
    #ifdef LOCAL
        system("pause");
    #endif
}