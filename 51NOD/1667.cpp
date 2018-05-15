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
int T,n,m,l,r,len[20];
ll ans1,ans2,ans3,sum,tot;
ll ksm(ll a,int b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;b>>=1;
    }
    return ret;
}
ll C(ll n,ll m)
{
    if(m>n) return 0;
    ll ret=1;
    for(int i=1;i<=m;i++) (ret*=(n-i+1))%=P;
    for(int i=2;i<=m;i++) (ret*=ksm(i,P-2))%=P; 
    return ret;
}
void dfs(int x,int f,int t)
{
    if(x>n+m)
    {
        (ans1+=f*C(sum-t+n+m-1,n+m)%P)%=P;
        (ans1+=P)%=P;
        (ans2+=f*C(sum-t+n+m-1,n+m-1)%P)%=P;
        (ans2+=P)%=P;
        return;
    }
    dfs(x+1,f,t);
    dfs(x+1,-f,t+len[x]);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        ans1=ans2=ans3=sum=0;tot=1;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d%d",&l,&r),sum+=r,len[i]=r-l+1,(tot*=len[i])%=P;
        scanf("%d",&m);
        for(int i=1;i<=m;i++) scanf("%d%d",&l,&r),sum-=l,len[i+n]=r-l+1,(tot*=len[i+n])%=P;
        dfs(1,1,0);
        ans3=((tot-ans1-ans2)%P+P)%P;
        tot=ksm(tot,P-2);
        (ans1*=tot)%=P;(ans2*=tot)%=P;(ans3*=tot)%=P;
        printf("%lld %lld %lld\n",ans1,ans2,ans3);
    }
}
