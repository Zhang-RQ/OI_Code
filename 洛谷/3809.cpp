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
using namespace std;
char str[1000010];
int rnk[1000010],sa[1000010];
int sum[1000010],tp[1000010];
void get_sa(int n)
{
    int m=127;
    for(int i=1;i<=n;i++) rnk[i]=str[i],tp[i]=i;
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
}
int main()
{
    scanf("%s",str+1);
    int n=strlen(str+1);
    get_sa(n);
    for(int i=1;i<=n;i++)
        printf("%d ",sa[i]);
    puts("");
}
