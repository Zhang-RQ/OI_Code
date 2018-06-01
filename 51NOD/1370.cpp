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
const int MAXN=210;
const int P=1E9+7;
int a[MAXN],f[MAXN][MAXN][MAXN],s[MAXN][MAXN][MAXN],n,m,ans,T;
void solve()
{
    memset(f,0,sizeof f);
    memset(s,0,sizeof s);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    a[0]=a[n+1]=1<<30;
    f[0][0][0]=1;
    for(int j=1;j<=n+1;j++) s[0][0][j]=1;
    for(int i=1,l,r;i<=n;i++)
    {
        l=r=i;
        for(;a[l-1]<a[i];l--); 
        for(;a[r+1]<a[i];r++);
        for(int j=l;j<=r;j++)
            if(i!=j)
                for(int k=1;k<=min(i,m);k++)
                   (f[i][j][k]+=(s[i-1][k-1][j]-s[i-1][k-1][l-1]+P)%P)%=P;
            else
                for(int k=0;k<=min(i,m);k++)
                {
                    if(k) (f[i][j][k]+=(s[i-1][k-1][j-1]-s[i-1][k-1][l-1]+P)%P)%=P;
                    (f[i][j][k]+=f[i-1][j-1][k])%=P;
                }
        for(int j=0;j<=n;j++) for(int k=0;k<=min(i-1,m);k++) (f[i][j][k]+=f[i-1][j][k])%=P;
        for(int k=0;k<=min(i,m);k++)
            for(int j=1;j<=n+1;j++) s[i][k][j]=(f[i][j-1][k]+s[i][k][j-1])%P;
    }
    ans=0;
    for(int i=0;i<=m;i++) (ans+=f[n][n][i])%=P;
    printf("%d\n",ans);
}
int main()
{
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}