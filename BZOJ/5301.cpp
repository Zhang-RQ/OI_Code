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
const int MAXN=1E5+10;
int n,m,k,siz,a[MAXN],curL,curR;
ll ans[MAXN],tans;
int cnt[262145];
struct Query{
    int l,r,id;
    inline bool operator < (const Query &rhs) const
    {
        if(l/siz!=rhs.l/siz) return l/siz<rhs.l/siz;
        else return r<rhs.r;
    }
}Q[MAXN];
void add(int pos)
{
    cnt[a[pos]]++;
    tans+=cnt[a[pos]^k]+(a[pos]==k);
}
void del(int pos)
{
    tans-=cnt[a[pos]^k]+(a[pos]==k);
    cnt[a[pos]]--;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    siz=sqrt(n);
    for(int i=2,x;i<=n+1;i++)
        scanf("%d",&x),a[i]=a[i-1]^x;
    for(int i=1;i<=m;i++)
        scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].r++,Q[i].id=i;
    sort(Q+1,Q+1+m);
    for(int i=1;i<=m;i++)
    {
        while(curL<Q[i].l) del(curL++);
        while(curL>Q[i].l) add(--curL);
        while(curR<Q[i].r) add(++curR);
        while(curR>Q[i].r) del(curR--);
        ans[Q[i].id]=tans;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    #ifdef LOCAL
        system("pause");
    #endif
}