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
#define int long long
char str[100010];
int sa[100010],Rank[100010],tp[100010],height[100010];
int sum[100010];
int lg2[100010],st[1000010][25];
int n,K;
void get_sa()
{
    int m=127;
    for(int i=1;i<=n;i++) Rank[i]=str[i],tp[i]=i;
    for(int i=0;i<=m;i++) sum[i]=0;
    for(int i=1;i<=n;i++) sum[Rank[tp[i]]]++;
    for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
    for(int i=n;i>=1;i--) sa[sum[Rank[tp[i]]]--]=tp[i];
    int p=1;
    for(int len=1;p<n;len<<=1,m=p)
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
            Rank[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+len]==tp[sa[i]+len])?p:++p;
    }
    int lst=0,j;
    for(int i=1;i<=n;height[Rank[i++]]=lst)
        for(lst=lst?lst-1:lst,j=sa[Rank[i]-1];str[j+lst]==str[i+lst];lst++);
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
    if(l==r) return n-sa[l]; //notice
    if(l>r) swap(l,r);
    int len=lg2[r-l];
    return min(st[l+1][len],st[r-(1<<len)+1][len]);
}
bool cmp(int l1,int r1,int l2,int r2)  //当[l1,r1]<=[l2,r2]时返回true
{
    int len1=r1-l1+1,len2=r2-l2+1;
    int lcp=query(Rank[l1],Rank[l2]);
    //printf("%d %d %d %d %d %d %d %d %d\n",l1,r1,l2,r2,len1,len2,Rank[l1],Rank[l2],lcp);
    if (lcp>=len1) return len1<=len2;
    else if (lcp>=len2) return 0;
    else return str[l1+lcp]<=str[l2+lcp];
}
void kth(int k,int &lpos,int &rpos)
{
    for(int i=1;i<=n;i++)
        if(k>n-height[i]-sa[i]+1)
            k-=(n-height[i]-sa[i]+1);
        else {lpos=sa[i];rpos=lpos+height[i]+k-1;return;}
}
bool check(int x)
{
    int L=0,R=0,ans=1,lst=n;
    kth(x,L,R);
    //printf("%lld %lld %lld\n",x,L,R);
    for(int i=n;i>=1;i--)
    {
        if(str[L]<str[i])
            {return false;}
        if(!cmp(i,lst,L,R))
            ans++,lst=i;
        //printf("%d %d\n",ans,K);
        if(ans>K)
            {return false;}
    }
    {return true;}
}
signed main()
{
    scanf("%lld",&K);
    scanf("%s",str+1);
    n=strlen(str+1);
    get_sa();
    get_st();
    int L=1,R=0,ans=0;
    for(int i=1;i<=n;i++)
        R+=n-height[i]-sa[i]+1;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(check(mid)) ans=mid,R=mid-1;
        else L=mid+1;
    }
    kth(ans,L,R);
    for(int i=L;i<=R;i++)
        putchar(str[i]);
    puts("");
    return 0;
}
