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
#include<cassert>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=5050;
const int P=1E9+7;
int sum[MAXN],cnt[2],a[MAXN],b[MAXN],pw[MAXN],n,m,q,tsum[MAXN];
char s[MAXN];
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    pw[0]=1;
    for(int i=1;i<=n+3;i++) pw[i]=(pw[i-1]*2)%P;
    for(int i=1;i<=m;i++) a[i]=i;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        cnt[0]=0;cnt[1]=m;
        for(int j=1;j<=m;j++)  s[j]=='0'?++cnt[0]:(sum[j]+=pw[i-1])%=P;
        for(int j=m;j>=1;j--)  b[cnt[s[a[j]]-'0']--]=a[j];
        swap(a,b);
    }
    for(int i=1;i<=m;i++) tsum[i]=sum[a[i]];
    tsum[m+1]=pw[n];
    for(int i=1,up,dw;i<=q;i++)
    {
        up=m+1;dw=0;
        scanf("%s",s+1);
        for(int j=m;j>=1;j--) if(s[a[j]]=='0') {dw=j;break;}
        for(int j=1;j<=m;j++) if(s[a[j]]=='1') {up=j;break;}
        printf("%d\n",up>dw?((tsum[up]-tsum[dw])%P+P)%P:0);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}