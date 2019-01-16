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
    int e,s;
    while(~scanf("%d%d",&e,&s)&&e&&s)
    {
        ll Ans=0;
        for(int i=1;i<=s;i++)
            Ans+=ksm(e,gcd(i,s));
        if(s&1) Ans+=s*ksm(e,(s+1)/2);
        else Ans+=s/2*ksm(e,s/2)+s/2*ksm(e,s/2+1);
        printf("%lld\n",Ans/2/s);
    }
}