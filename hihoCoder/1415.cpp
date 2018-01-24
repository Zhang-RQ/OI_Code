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
const int MAXN=200100;
int tp[MAXN],Rank[MAXN],sa[MAXN],sum[MAXN];
int height[MAXN];
int n,len1,len2;
char s1[MAXN],s2[MAXN];
void get_sa()
{
    int m=127;
    for(int i=1;i<=n;i++) Rank[i]=s1[i],tp[i]=i;
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
    for(int i=1;i<=n;height[Rank[i++]]=lst)
        for(lst=lst?lst-1:lst,j=sa[Rank[i]-1];s1[i+lst]==s1[j+lst];lst++);
}
int main()
{
    scanf("%s%s",s1+1,s2+1);
    len1=strlen(s1+1);
    len2=strlen(s2+1);
    s2[0]='#';
    strcat(s1+1,s2);
    n=strlen(s1+1);
    get_sa();
    int ans=0;
    for(int i=2;i<=n;i++)
        if(((1<=sa[i]&&sa[i]<=len1)!=(1<=sa[i-1]&&sa[i-1]<=len1))&&i!=len1+1&&i-1!=len1+1)
            ans=max(ans,height[i]);
    printf("%d\n",ans);
}
