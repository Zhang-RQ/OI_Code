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
const int MAXN=1E5+10;
const int P=1E9+7;
int f[MAXN][22],n,m,cnt;
int find(int x,int y){return f[x][y]==x?f[x][y]:f[x][y]=find(f[x][y],y);}
void merge(int x,int y,int len)
{
    if(find(x,len)!=find(y,len))
        f[f[x][len]][len]=f[y][len];
}
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;
        b>>=1;
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=0;j<=20;j++) f[i][j]=i;
    for(int i=1,a,b,c,d;i<=m;i++)
    {
        scanf("%d%d%d%d",&a,&b,&c,&d);
        for(int j=20;j>=0;j--)
            if(a+(1<<j)-1<=b) merge(a,c,j),a+=1<<j,c+=1<<j;
    }
    for(int j=20;j;j--)
        for(int i=1;i+(1<<j)-1<=n;++i)
            merge(i,find(i,j),j-1),merge(i+(1<<(j-1)),f[i][j]+(1<<(j-1)),j-1);
    for(int i=1;i<=n;i++) if(find(i,0)==i) cnt++;
    ll ans=9*ksm(10,cnt-1)%P;
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}