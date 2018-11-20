namespace exLucas{

    typedef long long ll;

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

            ll fac(ll N,int pi,int pk)
            {
                if(!N) return 1;
                ll Res=1;
                for(int i=1;i<pk;i++)
                    if(i%pi) (Res*=i)%=pk;
                Res=ksm(Res,N/pk,pk);
                for(int i=1;i<=N%pk;i++)
                    if(i%pi) (Res*=i)%=pk;
                return Res*fac(N/pi,pi,pk)%pk;
            }

            inline ll base_C(ll N,ll M,int pi,int pk)
            {
                int cnt=0;
                ll u=fac(N,pi,pk),d1=fac(M,pi,pk),d2=fac(N-M,pi,pk);
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
                    (Res+=base_C(N,M,Pi[i],Pk[i])*iPr[i]%P*Pr[i]%P)%=P;
                return Res;
            }
    };
}