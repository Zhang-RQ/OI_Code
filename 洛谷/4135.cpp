%:pragma GCC optimize(2)
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
const int MAXN=1E5+10;
int n,c,m,a[MAXN],tot,tcnt[MAXN],lstans,l,r;
int blocksize=320,cnt[323][MAXN],f[323][323],belong[MAXN],st[323],ed[323],tmp[643],tt;
void init()
{
    for(int i=1;i<=n;i++)
    {
        belong[i]=(i-1)/blocksize+1;++cnt[belong[i]][a[i]];
        if(!st[belong[i]]) st[belong[i]]=i;
        ed[belong[i]]=i;
    }
    tot=belong[n];
    for(int i=2;i<=tot;i++)
        for(int j=1;j<=c;j++)
            cnt[i][j]+=cnt[i-1][j];
    int tans=0;
    for(int i=1;i<=tot;i++)
    {
        tans=0;
        for(int j=st[i];j<=n;j++)
        {
            ++tcnt[a[j]];
            if(!(tcnt[a[j]]&1)) ++tans;
            else if(tcnt[a[j]]>2)  --tans;
            f[i][belong[j]]=tans;
        }
        for(int j=st[i+1];j<=n;j++)
            tcnt[a[j]]=0;
    }
    // memset(tcnt,0,sizeof tcnt);
}
int query(int l,int r)
{
    int ret=0;
    if(belong[r]-belong[l]<=1)
    {
        for(int i=l;i<=r;i++)
        {
            ++tcnt[a[i]];
            if(!(tcnt[a[i]]&1)) ++ret;
            else if(tcnt[a[i]]>2) --ret;
        }
        for(int i=l;i<=r;i++)
            tcnt[a[i]]=0;
    }
    else
    {
        ret=f[belong[l]+1][belong[r]-1];
        for(int i=l;i<=ed[belong[l]];i++)
        {
            ++tcnt[a[i]];
            if(!((tcnt[a[i]]+cnt[belong[r]-1][a[i]]-cnt[belong[l]][a[i]])&1)) ++ret;
            else if(tcnt[a[i]]+cnt[belong[r]-1][a[i]]-cnt[belong[l]][a[i]]>2) --ret;
        }
        for(int i=st[belong[r]];i<=r;i++)
        {
            ++tcnt[a[i]];
            if(!((tcnt[a[i]]+cnt[belong[r]-1][a[i]]-cnt[belong[l]][a[i]])&1)) ++ret;
            else if(tcnt[a[i]]+cnt[belong[r]-1][a[i]]-cnt[belong[l]][a[i]]>2) --ret;
        }
        for(int i=l;i<=ed[belong[l]];i++) tcnt[a[i]]=0;
        for(int i=st[belong[r]];i<=r;i++) tcnt[a[i]]=0;
    }
    return ret;
}
int main()
{
    scanf("%d%d%d",&n,&c,&m);
    for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
    init();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&l,&r);
        l=(l+lstans)%n+1;r=(r+lstans)%n+1;
        if(l>r) swap(l,r);
        printf("%d\n",lstans=query(l,r));
    }
}
