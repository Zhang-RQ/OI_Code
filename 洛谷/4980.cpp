#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1E9+7;

int n,tot;
pair<int,int> pr[40];
ll Ans=0;

ll ksm(ll a,ll b)
{
    ll ret=1;a%=P;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

void dfs(int x,int now,int ph)//ph=phi(n/now)
{
    if(x>tot)  return  (Ans+=ksm(n,now-1)*ph%P)%=P,void();
    for(int pw=1,e=0;e<=pr[x].second;e++,pw*=pr[x].first)
        dfs(x+1,now*pw,ph/(e==pr[x].second?(pw/pr[x].first*(pr[x].first-1)):(pw)));
}

void solve()
{
    scanf("%d",&n);Ans=0;
    int _n=n;tot=0;
    for(int i=2;i*i<=n;i++)
        if(!(_n%i))
        {
            pr[++tot].first=i;
            pr[tot].second=0;
            while(!(_n%i))
                pr[tot].second++,_n/=i;
        }
    if(_n!=1) ++tot,pr[tot].first=_n,pr[tot].second=1;
    int Phi=1;
    for(int i=1;i<=tot;i++) Phi*=(pr[i].first-1)*ksm(pr[i].first,pr[i].second-1);
    dfs(1,1,Phi);
    printf("%lld\n",Ans);
}

int main()
{
    int T;
    for(scanf("%d",&T);T--;solve());
}