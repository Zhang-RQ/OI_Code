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

    friend Poly Sqrt(const Poly &a)
    {
        if(a.size()==1) return a;
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

const int MAXN=3E5+10;

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

using namespace MultiPoint_Evaluation;

int n,A,B,siz[MAXN],stk[MAXN],top,inC[MAXN],pre[MAXN];
ll tp=1;
vector<int> T[MAXN];

void dfs1(int x,int fa)
{
	stk[++top]=x;
	if(x==B) throw -1;
	for(int v:T[x])
		if(v!=fa)
			dfs1(v,x);
	--top;
}

void dfs2(int x,int fa)
{
	siz[x]=1;
	for(int v:T[x])
		if(v!=fa&&!inC[v])
			dfs2(v,x),siz[x]+=siz[v];
	if(fa) (tp*=siz[x])%=P;
}

int main()
{
    NTT_namespace::preworks();
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),T[u].push_back(v),T[v].push_back(u);
	if(A==B)
	{
		dfs2(A,0);
		ll tAns=1;
		for(int i=1;i<n;i++) (tAns*=i)%=P;
		(tAns*=ksm(tp,P-2))%=P;
		printf("%lld\n",tAns);
		return 0;
	}
	try {dfs1(A,0);}
	catch(int e){}
	for(int i=1;i<=top;i++) inC[stk[i]]=1;
	for(int i=1;i<=top;i++) dfs2(stk[i],0);
	for(int i=1;i<=top;i++) pre[i+1]=pre[i]+siz[stk[i]];
	int m=top+1;
	for(int i=1;i<=m;i++) a[i]=pre[i];
	Solve_p(1,1,m);
	Poly Prod=Derivation(t[1]);
	Solve(Prod,1,1,m);
	ll tAns=0;
	for(int i=1;i<=m;i++)
		(m-i)&1?Dec(tAns,ksm(Ans[i],P-2)):Inc(tAns,ksm(Ans[i],P-2));
	for(int i=3;i<=n;i++) tAns=tAns*i%P;//divide by 2
	tAns=tAns*ksm(tp,P-2)%P;
	printf("%lld\n",tAns);
}
