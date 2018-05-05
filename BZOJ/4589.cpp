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
const int P=1E9+7;
const int rev=500000004;
const int MAXN=50010;
bool vis[MAXN];
int prime[MAXN],cnt,n,m,t[262145],tot=1;
int ksm(int a,int b)
{
    int ret=1;
    while(b)
    {
        if(b&1) ret=1ll*ret*a%P;
        a=1ll*a*a%P;
        b>>=1;
    }
    return ret;
}
void FWT(int *a,int n) //0..n-1
{
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=0;k<(i>>1);k++)
            {
                int x=a[j+k],y=a[j+k+(i>>1)];
                a[j+k]=(x+y)%P;
                a[j+k+(i>>1)]=(x-y+P)%P;
            }
}
void IFWT(int *a,int n)
{
    for(int i=2;i<=n;i<<=1)
        for(int j=0;j<n;j+=i)
            for(int k=0;k<(i>>1);k++)
            {
                int x=a[j+k],y=a[j+k+(i>>1)];
                a[j+k]=1ll*(x+y)%P*rev%P;
                a[j+k+(i>>1)]=1ll*(x-y+P)%P*rev%P;
            }
}
void sieve()
{
    for(int i=2;i<=50000;i++)
    {
        if(!vis[i]) prime[++cnt]=i;
        for(int j=1;j<=cnt&&prime[j]*i<=50000;j++)
        {
            vis[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
}
int main()
{
    sieve();
    while(~scanf("%d%d",&n,&m))
    {
        memset(t,0,sizeof t);
        for(int i=1;i<=cnt&&prime[i]<=m;i++) t[prime[i]]=1;
        tot=1;
        while(tot<=m) tot<<=1;
        FWT(t,tot);
        for(int i=0;i<tot;i++) t[i]=ksm(t[i],n);
        IFWT(t,tot);
        printf("%d\n",t[0]);
    }
}
