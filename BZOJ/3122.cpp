%:pragma GCC optimize(2)
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
ll gcd(ll a,ll b)
{
    if(!b)
        return a;
    else return gcd(b,a%b);
}
ll ksm(ll a,ll b,ll p)
{
    ll ret=1;
    while(b)
    {
        if(b&1)  (ret*=a)%=p;
        (a*=a)%=p;
        b>>=1;
    }
    return ret%p;
}
ll get_inv(ll a,ll p)
{
    return ksm(a,p-2,p);
}
map<ll,ll> mp;
ll BSGS(ll a,ll k,ll p) //a^x=k(mod p)
{
    a%=p;k%=p;
    mp.clear();
    ll st=sqrt(p),inv=1LL*get_inv(a,p)%p,tmp,ans=-1;
    tmp=inv*k%p;
    for(ll i=1;i<=st;i++)
    {
        if(!mp.count(tmp%p)) mp[tmp%p]=i;
        (tmp*=inv)%=p;
    }
    for(ll i=0;i<=st;i++)
        if(mp.count(ksm(a,i*st,p)))
            {ans=i*st+mp[ksm(a,i*st,p)];break;}
    return ans==-1?-1:ans+1;
}
int T;
ll P,a,b,x1,t;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld%lld%lld",&P,&a,&b,&x1,&t);
        if(x1==t){
            printf("1\n");
            continue;
        }
        if(a==0){
            if(b==t) printf("2\n");
            else printf("-1\n");
            continue;
        }
        if(a==1){
            t=(t-x1+P)%P;
            ll e=gcd(b,P);
            if(t%e){
                printf("-1\n");
                continue;
            }
            printf("%lld\n",(t*ksm(b,P-2,P))%P+1);
        }
        if(a!=1)
            printf("%lld\n",BSGS(a,(t+b*get_inv(a-1,P))%P*get_inv(x1+b*get_inv(a-1,P)%P,P),P));
    }
}
