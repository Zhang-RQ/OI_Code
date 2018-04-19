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
const int MAXN=5E5+10;
ll a[MAXN],sum[MAXN],ans;
int n,k,L,R,st[MAXN][25],lg2[MAXN];
struct data{
    int i,l,r,t;
    data(){}
    data(int _i,int _l,int _r,int _t):i(_i),l(_l),r(_r),t(_t){}
    inline bool operator < (const data &rhs) const
    {
        return sum[t]-sum[i-1]<sum[rhs.t]-sum[rhs.i-1];
    }
};
priority_queue<data> q;
int mx(int a,int b){return sum[a]>sum[b]?a:b;}
void st_init()
{
    for(int i=1;i<=n;i++)  st[i][0]=i;
    for(int i=2;i<=n;i++) lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i+(1<<(j-1))<=n;i++)
            st[i][j]=mx(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int query(int l,int r)
{
    if(l>r) return -1;
    int len=lg2[r-l+1];
    return mx(st[l][len],st[r-(1<<len)+1][len]);
}
int main()
{
    scanf("%d%d%d%d",&n,&k,&L,&R);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
    st_init();
    for(int i=1;i<=n;i++)
    {
        int l=min(n,i+L-1),r=min(n,i+R-1);
        if(l-i+1>=L) q.push(data(i,l,r,query(l,r)));
    }
    for(int i=1;i<=k;i++)
    {
        data t=q.top();q.pop();
        ans+=sum[t.t]-sum[t.i-1];
        int Q1=query(t.l,t.t-1),Q2=query(t.t+1,t.r);
        if(Q1!=-1) q.push(data(t.i,t.l,t.t-1,Q1));
        if(Q2!=-1) q.push(data(t.i,t.t+1,t.r,Q2));
    }
    printf("%lld\n",ans);
}
