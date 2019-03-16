#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXL=1048576;
const int P=998244353;
const int g[]={3,(P+1)/3};

template<typename T1,typename T2>
    void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
    void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
    T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
    T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

namespace Quadratic_residue{
	mt19937 RandEngine(chrono::steady_clock::now().time_since_epoch().count());
	inline int RandInt(int l,int r) {return uniform_int_distribution<int>(l,r)(RandEngine);}
	
	pair<ll,ll> Mul(pair<ll,ll> a,pair<ll,ll> b,ll f) //sec^2=f
	{
		return make_pair(Add(a.first*b.first%P,a.second*b.second%P*f%P),Add(a.first*b.second%P,a.second*b.first%P));
	}

	ll solve(ll n)
	{
		if(n<=1) return n;
		if(ksm(n,(P-1)/2)!=1) throw "N isn't quadratic residue";
		ll a=RandInt(1,n-1);
		while(ksm(Sub(a*a%P,n),(P-1)/2)!=P-1)
			a=RandInt(1,n-1);
		ll f=Sub(a*a%P,n);
		pair<ll,ll> Res=make_pair(1,0),t=make_pair(a,1);
		for(ll b=(P+1)/2;b;b>>=1,t=Mul(t,t,f))
			if(b&1) Res=Mul(Res,t,f);
		return min(Res.first,P-Res.first);
	}
}

namespace NTT_namespace{
    int rev[MAXL];
    ll inv[MAXL],G[2][MAXL];

    void preworks()
    {
        inv[1]=1;
        for(int i=2;i<MAXL;i++) inv[i]=Sub(P,P/i)*inv[P%i]%P;
        G[0][0]=G[1][0]=1;
        G[0][1]=ksm(g[0],(P-1)/MAXL);
        G[1][1]=ksm(g[1],(P-1)/MAXL);
        for(int i=2;i<MAXL;i++)
            G[0][i]=G[0][i-1]*G[0][1]%P,
            G[1][i]=G[1][i-1]*G[1][1]%P;
    }

    int init(int n)
    {
        int tot=1,lg2=0;
        while(tot<n) tot<<=1,lg2++;
        for(int i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        return tot;
    }

    void NTT(ll *a,int n,int f)
    {
        for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
        ll* ed=a+n;
        for(int i=2;i<=n;i<<=1)
            for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
                for(int k=0;k<(i>>1);k++)
                {
                    ll u=x[k],t=y[k]*G[f][MAXL/i*k]%P;
                    x[k]=Add(u,t);y[k]=Sub(u,t);
                }
        if(f) for(int i=0;i<n;i++) (a[i]*=inv[n])%=P;
    }

    void Inv(ll *a,ll *Res,int n)
    {
        if(n==1) return Res[0]=ksm(a[0],P-2),void();
        Inv(a,Res,(n+1)>>1);
        int tot=init(n<<1),lst=(n+1)>>1;
        static ll t1[MAXL],t2[MAXL];
        memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
        for(int i=0;i<n;i++) t1[i]=a[i];
        for(int i=0;i<lst;i++) t2[i]=Res[i];
        NTT(t1,tot,0);NTT(t2,tot,0);
        for(int i=0;i<tot;i++) t1[i]=Sub(2*t2[i],t2[i]*t2[i]%P*t1[i]%P);
        NTT(t1,tot,1);
        for(int i=0;i<n;i++) Res[i]=t1[i];
    }
}

struct Poly{
    
    vector<ll> v;

    Poly(){}
    Poly(int n){v.resize(n);}
    Poly(const initializer_list<ll> &T){v=T;}
    
    ll& operator [] (int x) {return v[x];}
    const ll& operator [] (int x) const {return v[x];}

    int size() const {return v.size();}
    void resize(int x){v.resize(x);}
    void reduce(){while(v.size()&&v.back()==0) v.pop_back();}
    void reverse(){std::reverse(v.begin(),v.end());}

    void print()const{for(size_t i=0;i<v.size();i++) printf("%lld%c",v[i],"\n "[i!=v.size()-1]);}
    
    friend Poly operator + (const Poly &lhs,const Poly &rhs)
    {
        if(lhs.size()>rhs.size())
        {
            Poly Ret(lhs.size());
            for(int i=0;i<rhs.size();i++)
                Ret[i]=Add(lhs[i],rhs[i]);
            for(int i=rhs.size();i<lhs.size();i++)
                Ret[i]=lhs[i];
            return Ret;
        }
        else
        {
            Poly Ret(rhs.size());
            for(int i=0;i<lhs.size();i++)
                Ret[i]=Add(lhs[i],rhs[i]);
            for(int i=lhs.size();i<rhs.size();i++)
                Ret[i]=rhs[i];
            return Ret;
        }
    }

    friend Poly operator - (const Poly &lhs,const Poly &rhs)
    {
        if(lhs.size()>rhs.size())
        {
            Poly Ret(lhs.size());
            for(int i=0;i<rhs.size();i++)
                Ret[i]=Sub(lhs[i],rhs[i]);
            for(int i=rhs.size();i<lhs.size();i++)
                Ret[i]=lhs[i];
            return Ret;
        }
        else
        {
            Poly Ret(rhs.size());
            for(int i=0;i<lhs.size();i++)
                Ret[i]=Sub(lhs[i],rhs[i]);
            for(int i=lhs.size();i<rhs.size();i++)
                Ret[i]=Sub(0,rhs[i]);
            return Ret;
        }
    }

    friend Poly Derivation(const Poly &a)
    {
        Poly Ret(a.size()-1);
        for(int i=0;i<a.size()-1;i++)
            Ret[i]=a[i+1]*(i+1)%P;
        return Ret;
    }

    friend Poly Intergral(const Poly &a)
    {
        Poly Ret(a.size()+1);
        for(int i=1;i<=a.size();i++)
            Ret[i]=a[i-1]*NTT_namespace::inv[i]%P;
        return Ret;
    }

    friend Poly operator * (const Poly &lhs,const Poly &rhs)
    {
        using namespace NTT_namespace;
        static ll t1[MAXL],t2[MAXL];
        int tot=init(lhs.size()+rhs.size()),siz=lhs.size()+rhs.size()-1;
        Poly Ret(siz);
        memset(t1,0,sizeof(ll)*tot);
        memset(t2,0,sizeof(ll)*tot);
        for(int i=0;i<lhs.size();i++) t1[i]=lhs[i];
        for(int i=0;i<rhs.size();i++) t2[i]=rhs[i];
        NTT(t1,tot,0);NTT(t2,tot,0);
        for(int i=0;i<tot;i++) (t1[i]*=t2[i])%=P;
        NTT(t1,tot,1);
        for(int i=0;i<siz;i++) Ret[i]=t1[i];
        return Ret;
    }

    friend Poly operator * (const Poly &lhs,const ll &rhs)
    {
        Poly Ret(lhs.size());
        for(int i=0;i<lhs.size();i++)
            Ret[i]=lhs[i]*rhs%P;
        return Ret;
    }

    friend Poly Inv(const Poly &a)
    {
        using namespace NTT_namespace;
        static ll t1[MAXL],t2[MAXL];
        int siz=a.size();
        for(int i=0;i<siz;i++) t1[i]=a[i];
        Inv(t1,t2,siz);
        Poly Ret(siz);
        for(int i=0;i<siz;i++) Ret[i]=t2[i];
        return Ret;
    }

    friend Poly operator / (const Poly &lhs,const Poly &rhs)
    {
        if(lhs.size()<rhs.size()) return Poly({0});
        int n=lhs.size(),m=rhs.size();
        Poly rf=lhs,rg=rhs;
        rf.reverse();rg.reverse();
        rf.resize(n-m+1);rg.resize(n-m+1);
        Poly Ret=rf*Inv(rg);
        Ret.resize(n-m+1);
        Ret.reverse();
        return Ret;
    }

    friend Poly operator % (const Poly &lhs,const Poly &rhs)
    {
        if(lhs.size()<rhs.size()) return lhs;
        Poly Ret=lhs-(lhs/rhs)*rhs;
        Ret.resize(rhs.size()-1);
        return Ret;
    }

    friend pair<Poly,Poly> Div(const Poly &lhs,const Poly &rhs)
    {
        if(lhs.size()<rhs.size()) return make_pair(Poly({0}),lhs);
        int n=lhs.size(),m=rhs.size();
        Poly rf=lhs,rg=rhs;
        rf.reverse();rg.reverse();
        rf.resize(n-m+1);rg.resize(n-m+1);
        Poly Ret1=rf*Inv(rg);
        Ret1.resize(n-m+1);
        Ret1.reverse();
        Poly Ret2=lhs-Ret1*rhs;
        Ret2.resize(m-1);
        return make_pair(Ret1,Ret2);
    }

    friend Poly Ln(const Poly &a)
    {
        Poly Ret=Intergral(Inv(a)*Derivation(a));
        Ret.resize(a.size());
        return Ret;
    }

    friend Poly Exp(const Poly &a)
    {
        if(a.size()==1) return Poly({1});
        Poly tmp=a;
        tmp.resize((a.size()+1)>>1);
        Poly Res=Exp(tmp);Res.resize(a.size());
        Poly Ret=Res*(Poly({1})-Ln(Res)+a);
        Ret.resize(a.size());
        return Ret;
    }

	friend Poly Pow(const Poly &lhs,ll k)  {return Exp(Ln(lhs)*k);}

    friend Poly Sqrt(const Poly &a)
    {
        if(a.size()==1) return Poly({Quadratic_residue::solve(a[0])});
        Poly tmp=a;
        tmp.resize((a.size()+1)>>1);
        Poly Res=Sqrt(tmp);
        tmp=Res*Res;
        Res.resize(a.size());
        Poly Ret=(tmp+a)*Inv(Res*2);
        Ret.resize(a.size());
        return Ret;
    }
};

const int MAXN=1E5+10;

namespace MultiPoint_Evaluation{
    Poly t[MAXN<<2];
    ll a[MAXN],Ans[MAXN];

    void Solve_p(int x,int l,int r)
    {
        if(l==r) return t[x]=Poly({Sub(0,a[l]),1}),void();
        int mid=(l+r)>>1;
        Solve_p(x<<1,l,mid);Solve_p(x<<1|1,mid+1,r);
        t[x]=t[x<<1]*t[x<<1|1];
    }

    void Solve(const Poly &f,int x,int l,int r)
    {
        if(l==r) return Ans[l]=f[0],void();
        int mid=(l+r)>>1;
        Solve(f%t[x<<1],x<<1,l,mid);
        Solve(f%t[x<<1|1],x<<1|1,mid+1,r);
    }
    
    vector<ll> MPE(const Poly &f,const vector<ll> &vX)
    {
        int m=vX.size();
        for(int i=0;i<m;i++) a[i+1]=vX[i];
        Solve_p(1,1,m);
        Solve(f%t[1],1,1,m);
        vector<ll> Ret;
        for(int i=1;i<=m;i++) Ret.push_back(Ans[i]);
        return Ret;
    }
}

namespace Fast_Interpolation{
	using namespace MultiPoint_Evaluation;

	ll X[MAXN],Y[MAXN];
	
	Poly Solve(int x,int l,int r)
	{
		if(l==r) return Poly({Y[l]*ksm(Ans[l],P-2)%P});
		int mid=(l+r)>>1;
		return Solve(x<<1,l,mid)*t[x<<1|1]+Solve(x<<1|1,mid+1,r)*t[x<<1];
	}
	
	Poly InterPolation(const vector<pair<ll,ll> > &V)
	{
		int n=V.size();
		for(int i=1;i<=n;i++)
			X[i]=a[i]=V[i-1].first,Y[i]=V[i-1].second;
		Solve_p(1,1,n);
		Poly Prod=Derivation(t[1]);
		MultiPoint_Evaluation::Solve(Prod,1,1,n);
		return Solve(1,1,n);
	}
}

int main()
{
    NTT_namespace::preworks();
}
