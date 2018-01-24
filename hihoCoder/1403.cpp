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
deque<int> q;
const int MAXN=20010;
int Rank[MAXN],sa[MAXN],tp[MAXN],sum[MAXN],height[MAXN];
int str[MAXN];
int n,k;
void get_sa()
{
    int m=101;
    for(int i=1;i<=n;i++) Rank[i]=str[i],tp[i]=i;
    for(int i=0;i<=m;i++) sum[i]=0;
    for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
    for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
    for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
    int p=1;
    for(int len=1;p<n;m=p,len<<=1)
    {
        p=0;
        for(int i=n-len+1;i<=n;i++) tp[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
        for(int i=0;i<=m;i++) sum[i]=0;
        for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
        for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
        for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
        swap(Rank,tp);
        Rank[sa[1]]=1;p=1;
        for(int i=2;i<=n;i++)
            Rank[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
    }
    int lst=0,j;
    height[1]=0;
    for(int i=1;i<=n;height[Rank[i++]]=lst) //枚举pos
        for(lst=lst?lst-1:lst,j=sa[Rank[i]-1];str[i+lst]==str[j+lst];lst++);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&str[i]);
    get_sa();
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        while(q.size()&&height[q.back()]>=height[i]) q.pop_back();
        q.push_back(i);
        while(q.size()&&i-q.front()+1>k-1) q.pop_front();
        ans=max(ans,height[q.front()]);
    }
    printf("%d\n",ans);
}
