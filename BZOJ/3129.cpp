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


#include<ctime>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b) return x=1,y=0,void();
    exgcd(b,a%b,y,x);y-=(a/b)*x;
}

ll inv(ll v,ll p)
{
    ll x,y;
    exgcd(v,p,x,y);
    assert(1ll*(x%p+p)%p*v%p==1);
    return (x%p+p)%p;
}

ll ksm(ll a,ll b,ll p)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=p) if(b&1) (ret*=a)%=p;
    return ret;
}

class Combination_solver{
    private:
        int Pi[10],Pk[10],Pr[10],iPr[10],P,cnt;
        map<int,ll> mp[10];

        ll fac(ll N,int pi,int pk,int num)
        {
            if(mp[num].count(N)) return mp[num][N];
            if(!N) return 1;
            ll Res=1;
            for(int i=1;i<pk;i++)
                if(i%pi) (Res*=i)%=pk;
            Res=ksm(Res,N/pk,pk);
            for(int i=1;i<=N%pk;i++)
                if(i%pi) (Res*=i)%=pk;
            return mp[num][N]=Res*fac(N/pi,pi,pk,num)%pk;
        }

        inline ll base_C(ll N,ll M,int pi,int pk,int num)
        {
            int cnt=0;
            ll u=fac(N,pi,pk,num),d1=fac(M,pi,pk,num),d2=fac(N-M,pi,pk,num);
            for(int x=N;x;x/=pi) cnt+=x/pi;
            for(int x=M;x;x/=pi) cnt-=x/pi;
            for(int x=N-M;x;x/=pi) cnt-=x/pi;
            return u*inv(d1,pk)%pk*inv(d2,pk)%pk*ksm(pi,cnt,pk)%pk;
        }
    public:
        void init(int _p)
        {
            int x=P=_p;
            for(int i=2,v;1ll*i*i<=P;i++)
                if(!(x%i))
                {
                    v=1;
                    while(!(x%i)) x/=i,v*=i;
                    Pi[++cnt]=i;
                    Pk[cnt]=v;
                }
            if(x!=1) Pi[++cnt]=x,Pk[cnt]=x;
            for(int i=1;i<=cnt;i++)
                Pr[i]=P/Pk[i],iPr[i]=inv(Pr[i],Pk[i]);
        }
        inline ll C(ll N,ll M)
        {
            if(N<M) return 0;
            if(N==M) return 1;
            ll Res=0;
            for(int i=1;i<=cnt;i++)
                (Res+=base_C(N,M,Pi[i],Pk[i],i)*iPr[i]%P*Pr[i]%P)%=P;
            return Res;
        }
}Cs;

int T,P,n,n1,n2,m,w[20];
ll Ans;

void dfs(int now,int f,int s)
{
    if(s<=0) return;
    if(now>n1) return Ans=(Ans+f*Cs.C(s-1,n-1)%P+P)%P,void();
    dfs(now+1,f,s);dfs(now+1,-f,s-w[now]);
}

void solve()
{
    scanf("%d%d%d%d",&n,&n1,&n2,&m);
    for(int i=1;i<=n1;i++) scanf("%d",&w[i]);
    for(int i=1,x;i<=n2;i++) scanf("%d",&x),m-=x-1;
    Ans=0;dfs(1,1,m);
    printf("%lld\n",Ans);
}

int main()
{
    for(scanf("%d%d",&T,&P),Cs.init(P);T--;solve());
}