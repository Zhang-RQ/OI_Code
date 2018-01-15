#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN=300010;
const ll INF=(1ll<<62);
char str[MAXN];
int sa[MAXN],Rank[MAXN],tp[MAXN],height[MAXN],sum[MAXN];
int fa[MAXN],siz[MAXN],maxv[MAXN],minv[MAXN];
int n,val[MAXN];
ll ans2[MAXN],ans1[MAXN];
void get_sa()
{
    int m=127;
    int p=1;
    for(int i=1;i<=n;i++) tp[i]=i,Rank[i]=str[i];
    for(int i=1;i<=m;i++) sum[i]=0;
    for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
    for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
    for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
    for(int len=1;p<n;m=p,len<<=1)
    {
        p=0;
        for(int i=n-len+1;i<=n;i++) tp[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
        for(int i=1;i<=m;i++) sum[i]=0;
        for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
        for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
        for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
        swap(Rank,tp);
        Rank[sa[1]]=1;p=1;
        for(int i=2;i<=n;i++)
            Rank[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+len]==tp[sa[i]+len])?p:++p;
    }
    int lst=0,j;
    for(int i=1;i<=n;height[Rank[i++]]=lst)
        for(lst=lst?lst-1:lst,j=sa[Rank[i]-1];str[j+lst]==str[i+lst];++lst);
}
int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    if(siz[x]<siz[y]) swap(x,y);  //  y->x
    maxv[x]=max(maxv[x],maxv[y]);
    minv[x]=min(minv[x],minv[y]);
    siz[x]+=siz[y];
    fa[y]=x;
}
bool cmp(int x,int y)
{
    if(height[x]!=height[y])
        return height[x]>height[y];
    return x<y;
}
int main()
{
    scanf("%d",&n);
    scanf("%s",str+1);
    get_sa();
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    for(int i=1;i<=n;i++) siz[i]=1,fa[i]=i,maxv[i]=minv[i]=val[sa[i]];
    for(int i=1;i<n;i++) tp[i]=i+1;
    for(int i=0;i<n;i++) ans2[i]=-INF;
    sort(tp+1,tp+n,cmp);
    for(int i=1;i<n;i++)
    {
        int x=find(tp[i]),y=find(tp[i]-1);
        ans1[height[tp[i]]]+=1ll*siz[x]*siz[y];
        ans2[height[tp[i]]]=max(ans2[height[tp[i]]],1ll*maxv[x]*maxv[y]);
        ans2[height[tp[i]]]=max(ans2[height[tp[i]]],1ll*maxv[x]*minv[y]);
        ans2[height[tp[i]]]=max(ans2[height[tp[i]]],1ll*minv[x]*maxv[y]);
        ans2[height[tp[i]]]=max(ans2[height[tp[i]]],1ll*minv[x]*minv[y]);
        merge(x,y);
    }
    for(int i=n-2;i>=0;i--)
        ans1[i]+=ans1[i+1],
        ans2[i]=max(ans2[i],ans2[i+1]);
    for(int i=0;i<=n-1;i++)
        printf("%lld %lld\n",ans1[i],ans2[i]==-INF?0:ans2[i]);
    return 0;
}
