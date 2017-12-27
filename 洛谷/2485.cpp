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
#define int ll
map<ll,ll> mp;
ll ksm(ll a,ll b,ll p)
{
    ll ret=1;
    while(b)
    {
        if(b&1)
            (ret*=a)%=p;
        (a*=a)%=p;
        b>>=1;
    }
    return ret;
}
ll inver(ll a,ll mod)
{
    return ksm(a,mod-2,mod);
}
void solve2(ll _y,ll _z,ll _p)
{
    ll ans;
    if(_y%_p==0&&_z%_p!=0)
    {
        puts("Orz, I cannot find x!");
        return;
    }
    ans=(_z*inver(_y,_p))%_p;
    printf("%lld\n",ans);
}
void BSGS(ll a,ll b,ll p)
{
    ll tmpx,tmpy,st=sqrt(p);
    mp.clear();
    mp[b]=0;
    if(a%p==0&&b%p!=0)
    {
        puts("Orz, I cannot find x!");
        return;
    }
    ll inv=1LL*inver(a,p)%p,tmp;
    tmp=inv;
    for(int i=1;i<=st;i++)
    {
        if(!mp.count((tmp*b)%p)) mp[(tmp*b)%p]=i;
        (tmp*=inv)%=p;
    }
    for(int i=0;i<=st;i++)
    {
        if(mp.count(ksm(a,i*st,p)))
        {
            printf("%lld\n",(i*st+mp[ksm(a,i*st,p)])%p);
            return;
        }
    }
    puts("Orz, I cannot find x!");
}
int t,type;
ll y,z,p,ans;
signed main()
{
    scanf("%lld%lld",&t,&type);
    for(int i=1;i<=t;i++)
    {
        scanf("%lld%lld%lld",&y,&z,&p);
        y%=p;
        switch(type)
        {
            case 1 : printf("%lld\n",ksm(y,z,p));break;
            case 2 : solve2(y,z%p,p);break;
            case 3 : BSGS(y,z%p,p);break;
        }
    }
}
