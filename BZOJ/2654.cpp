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
const int MAXN=50010;
const int MAXM=100010;
int x,fa[MAXN],n,m,ned;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
struct node{
    int u,v,val,c; //c=1 white c=0 black
    bool operator < (const node &rhs) const
    {
        if(val+c*x!=rhs.val+rhs.c*x) return val+c*x<rhs.val+rhs.c*x;
        return c>rhs.c;
    }
}E[MAXM];
int main()
{
    
    scanf("%d%d%d",&n,&m,&ned);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].val,&E[i].c),E[i].c^=1,E[i].u++,E[i].v++;
    int L=-1000000,R=1000000,cnt,ccnt;
    ll tans=0,ans=0;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        for(int i=1;i<=n;i++) fa[i]=i;
        tans=0;
        x=mid;ccnt=cnt=0;
        sort(E+1,E+1+m);
        for(int i=1;i<=m;i++)
        {
            int __x=find(E[i].u),__y=find(E[i].v);
            if(__x!=__y)
            {
                ++ccnt;
                fa[__x]=__y;cnt+=E[i].c;
                tans+=E[i].val+E[i].c*x;
                if(ccnt==n-1) break;
            }
        }
        
        if(cnt>=ned) L=mid+1,ans=tans-1ll*ned*x;
        else R=mid-1;
    }
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}