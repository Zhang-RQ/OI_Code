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
const int MAXN=500010;
int Rank[MAXN],sa[MAXN],height[MAXN],sum[MAXN],tp[MAXN];
int pre[MAXN],lst[MAXN],stk[MAXN],top;
int n;
char str[MAXN];
ll ans=0;
void get_sa()
{
    int m=127;
    for(int i=1;i<=n;i++)  Rank[i]=str[i],tp[i]=i;
    for(int i=1;i<=m;i++)  sum[i]=0;
    for(int i=1;i<=n;i++)  sum[Rank[tp[i]]]++;
    for(int i=1;i<=m;i++)  sum[i]+=sum[i-1];
    for(int i=n;i>=1;i--)  sa[sum[Rank[tp[i]]]--]=tp[i];
    int p=1;
    for(int len=1;p<n;m=p,len<<=1)
    {
        p=0;
        for(int i=n-len+1;i<=n;i++) tp[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
        for(int i=1;i<=m;i++)  sum[i]=0;
        for(int i=1;i<=n;i++)  sum[Rank[tp[i]]]++;
        for(int i=1;i<=m;i++)  sum[i]+=sum[i-1];
        for(int i=n;i>=1;i--)  sa[sum[Rank[tp[i]]]--]=tp[i];
        swap(Rank,tp);
        Rank[sa[1]]=1;
        p=1;
        for(int i=2;i<=n;i++)
            Rank[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
    }
    int lst=0,j;
    for(int i=1;i<=n;height[Rank[i++]]=lst)
        for(lst=lst?lst-1:lst,j=sa[Rank[i]-1];str[i+lst]==str[j+lst];lst++);
}
void solve()
{
    height[0]=0xcfcfcfcf;
    for(int i=1;i<=n;i++)
    {
        while(height[stk[top]]>=height[i]) top--;
        pre[i]=stk[top]+1;
        stk[++top]=i;
    }
    height[n+1]=0xcfcfcfcf;top=0;stk[0]=n+1;
    for(int i=n;i>=1;i--)
    {
        while(height[stk[top]]>height[i])  top--;
        lst[i]=stk[top]-1;
        stk[++top]=i;
    }
    for(int i=1;i<=n;i++) ans+=1ll*i*(n-1)-2ll*(i-pre[i]+1)*(lst[i]-i+1)*height[i];
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    get_sa();solve();
    printf("%lld\n",ans);
}
