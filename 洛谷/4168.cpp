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
int blocksize=200,f[210][210],cnt[210][40010],a[40010],st[210],ed[210],belong[40010],tot,tcnt[40010];
int n,tmp[410],m,l,r,ta[40010],lstans;
void init()
{
    for(int i=1;i<=n;i++)
    {
        belong[i]=i/blocksize+1,cnt[belong[i]][a[i]]++;
        if(!st[belong[i]]) st[belong[i]]=i;
        ed[belong[i]]=i;
    }
    tot=belong[n];
    for(int i=1;i<=tot;i++)
        for(int j=1;j<=n;j++)
            cnt[i][j]+=cnt[i-1][j];
    for(int i=1;i<=tot;i++)
    {
        int cur=0,ccnt=0;
        memset(tcnt,0,sizeof tcnt);
        for(int j=i;j<=tot;j++)
        {
            for(int k=st[j];k<=ed[j];k++)
            {
                tcnt[a[k]]++;
                if(tcnt[a[k]]>ccnt||(tcnt[a[k]]==ccnt&&a[k]<cur))
                    cur=a[k],ccnt=tcnt[a[k]];
            }
            f[i][j]=cur;
        }
    }
    memset(tcnt,0,sizeof tcnt);
}
int query(int l,int r)
{
    int ret=0,rcnt=0;
    if(belong[r]-belong[l]<=1)
    {
        for(int i=l;i<=r;i++)
        {
            ++tcnt[a[i]];
            if(tcnt[a[i]]>rcnt||(tcnt[a[i]]==rcnt&&a[i]<ret))
                ret=a[i],rcnt=tcnt[a[i]];
        }
        for(int i=l;i<=r;i++) tcnt[a[i]]=0;
    }
    else
    {
        ret=f[belong[l]+1][belong[r]-1];rcnt=cnt[belong[r]-1][ret]-cnt[belong[l]][ret];
        int tt=0;
        for(int i=l;i<=ed[belong[l]];i++) tmp[++tt]=a[i];
        for(int i=st[belong[r]];i<=r;i++) tmp[++tt]=a[i];
        for(int i=1;i<=tt;i++) tcnt[tmp[i]]=cnt[belong[r]-1][tmp[i]]-cnt[belong[l]][tmp[i]];
        for(int i=l;i<=ed[belong[l]];i++) tcnt[a[i]]++;
        for(int i=st[belong[r]];i<=r;i++) tcnt[a[i]]++;
        for(int i=1;i<=tt;i++)
            if(tcnt[tmp[i]]>rcnt||(tcnt[tmp[i]]==rcnt&&tmp[i]<ret))
                ret=tmp[i],rcnt=tcnt[tmp[i]];
        for(int i=1;i<=tt;i++)
            tcnt[tmp[i]]=0;
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),ta[i]=a[i];
    sort(ta+1,ta+1+n);
    int topt=unique(ta+1,ta+1+n)-ta-1;
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(ta+1,ta+1+topt,a[i])-ta;
    init();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&l,&r);
        l=(l+lstans-1)%n+1;
        r=(r+lstans-1)%n+1;
        if(l>r) swap(l,r);
        printf("%d\n",lstans=ta[query(l,r)]);
    }
}
