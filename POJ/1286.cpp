#include<cstdio>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

int gcd(int a,int b){return b?gcd(b,a%b):a;}

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,a*=a) if(b&1) ret*=a;
    return ret;
}

int main()
{
    int n;
    while(~scanf("%d",&n)&&~n)
    {
        if(n==0) {puts("0");continue;}
        ll Ans=0;
        for(int i=1;i<=n;i++) Ans+=ksm(3,gcd(i,n));
        if(n&1) Ans+=n*ksm(3,(n+1)/2);
        else Ans+=n/2*ksm(3,n/2+1)+n/2*ksm(3,n/2);
        Ans/=2*n;
        printf("%lld\n",Ans);
    }
}