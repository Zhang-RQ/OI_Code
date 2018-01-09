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
int arr[200100],arr1[200100];
int sa[200100],rnk[200100],height[200100];
int tp[200100],sum[200100];
int n,k;
int lg2[300000],st[200100][20];
void get_sa(int n,int m)
{
    for(int i=1;i<=n;i++) rnk[i]=arr[i],tp[i]=i;
    for(int i=0;i<=m;i++) sum[i]=0;
    for(int i=1;i<=n;i++) sum[rnk[tp[i]]]++;
    for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
    for(int i=n;i>=1;i--) sa[sum[rnk[tp[i]]]--]=tp[i];
    int p=1;
    for(int len=1;p<n;len<<=1,m=p)
    {
        p=0;
        for(int i=n-len+1;i<=n;i++) tp[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>len) tp[++p]=sa[i]-len;
        for(int i=0;i<=m;i++) sum[i]=0;  //rnk为第一关键字，tp为第二关键字
        for(int i=1;i<=n;i++) sum[rnk[tp[i]]]++;
        for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
        for(int i=n;i>=1;i--) sa[sum[rnk[tp[i]]]--]=tp[i];
        swap(rnk,tp);rnk[sa[1]]=1;p=1;
        for(int i=2;i<=n;i++)
            rnk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+len]==tp[sa[i-1]+len])?p:++p;
    }
    int lst=0,j;
    for(int i=1;i<=n;height[rnk[i++]]=lst)
        for(lst=lst?lst-1:lst,j=sa[rnk[i]-1];arr[j+lst]==arr[i+lst];++lst);
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
    int len=lg2[r-l+1];
    return min(st[l][len],st[r-(1<<len)+1][len]);
}
bool check(int length)
{
    int l=1,r=l+k-2;
    while(r<=n)
    {
        int ok=query(l,r);
        if(ok>=length)
            return true;
        l++;r++;
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr1[i]),arr[i]=arr1[i];
    sort(arr1+1,arr1+1+n);
    int cnt=unique(arr1+1,arr1+1+n)-arr1-1;
    for(int i=1;i<=n;i++)
        arr[i]=lower_bound(arr1+1,arr1+1+cnt,arr[i])-arr1;
    get_sa(n,n);
    get_st();
    int l=0,r=20000,ans=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) l=mid+1,ans=mid;
        else r=mid-1;
    }
    printf("%d\n",ans);
}
