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
const int MAXN=200010;
int tp[MAXN],Rank[MAXN],sa[MAXN],sum[MAXN];
int height[MAXN],st[MAXN][25],lg2[MAXN];
int n,ans;
char str[MAXN];
void get_sa()
{
    int m=127;
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
        Rank[sa[1]]=1;
        p=1;
        for(int i=2;i<=n;i++)
            Rank[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
    }
    int lst=0,j;
    for(int i=1;i<=n;height[Rank[i++]]=lst)
        for(lst=lst?lst-1:lst,j=sa[Rank[i]-1];str[i+lst]==str[j+lst];lst++);
}
void get_st()
{
    for(int i=2;i<=n;i++)
        lg2[i]=lg2[i>>1]+1;
    for(int i=1;i<=n;i++)
        st[i][0]=height[i];
    for(int j=1;j<=lg2[n];j++)
        for(int i=1;i<=n;i++)
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int query(int l,int r)
{
    l=Rank[l],r=Rank[r];
    if(l>r) swap(l,r);
    l++;
    int len=lg2[r-l+1];
    return min(st[l][len],st[r-(1<<len)+1][len]);
}
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    get_sa();
    get_st();
    //for(int i=1;i<=n;i++)
    //    printf("%d ",Rank[i]);
    //puts("");
    for(int len=1;len<=n;len++)
    {
        for(int i=1;i+len<=n;i+=len)
        {
            int R=query(i,i+len);
            ans=max(ans,R/len+1);
            if(i>=len-R%len)
                ans=max(ans,query(i-len+R%len,i+R%len)/len+1);
        }
    }
    printf("%d\n",ans);
}
