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
const int P=20170408;
const int MAXM=2E7+10;
bool vis[MAXM];
int prime[MAXM>>1],cnt,n,m,p;
struct Polynomial{
    ll a[201];
    inline ll &operator [] (int i) {return a[i];}
    inline Polynomial operator + (Polynomial &rhs)
    {
        Polynomial ret;
        for(int i=0;i<p;i++) ret[i]=(a[i]+rhs[i])%P;
        return ret;
    }
    inline Polynomial operator - (Polynomial &rhs)
    {
        Polynomial ret;
        for(int i=0;i<p;i++) ret[i]=((a[i]-rhs[i])%P+P)%P;
        return ret;
    }
    inline Polynomial operator * (Polynomial &rhs)
    {
        Polynomial ret;
        memset(&ret,0,sizeof(ret));
        for(int i=0;i<p;i++)
            for(int j=0;j<p;j++)
                (ret[i+j]+=(a[i]*rhs[j])%P)%=P;
        for(int i=p;i<2*p;i++)
            (ret[i%p]+=ret[i])%=P;
        return ret;
    }
}t,ans,_ans;
Polynomial ksm(Polynomial a,int b)
{
    Polynomial ret;
    memset(&ret,0,sizeof(ret));ret[0]=1;
    while(b)
    {
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}
void sieve()
{
    for(int i=2;i<=m;i++)
    {
        if(!vis[i]) prime[++cnt]=i;
        for(int j=1;j<=cnt&&prime[j]*i<MAXM;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    sieve();
    int tmp=m/p;
    for(int i=0;i<p;i++) t[i]=tmp;
    for(int i=0;i<=m%p;i++) t[i]++;
    t[0]--;
    ans=ksm(t,n);
    for(int i=1;i<=cnt;i++) t[prime[i]%p]--;
    _ans=ksm(t,n);
    ans=ans-_ans;
    printf("%lld\n",ans[0]);
}
