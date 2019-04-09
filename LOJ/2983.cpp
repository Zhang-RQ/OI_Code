#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int P=998244353;
const int g[]={3,(P+1)/3};
const int MAXL=524288;

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
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

int n,y,op;

namespace sol0{
	set<pair<int,int> > S;

	void solve()
	{
		int cnt=0;
		for(int i=1,u,v;i<n;i++)
		{
			scanf("%d%d",&u,&v);
			if(u>v) swap(u,v);
			S.insert({u,v});
		}
		for(int i=1,u,v;i<n;i++)
		{
			scanf("%d%d",&u,&v);
			if(u>v) swap(u,v);
			if(S.count({u,v}))
				cnt++;
		}
		printf("%lld\n",ksm(y,n-cnt));
	}
}

namespace sol1{
	int invn,invy;
	vector<int> T[MAXN];
	ll f[MAXN][2];

	void dfs(int x,int fa)
	{
		f[x][0]=f[x][1]=1;
		for(int v:T[x])
			if(v!=fa)
			{
				dfs(v,x);
				ll t0=0,t1=0;
				//choose edge x->v
				Inc(t0,f[x][0]*f[v][0]%P*(invy-1)%P*invn%P);
				Inc(t1,(f[x][1]*f[v][0]%P+f[x][0]*f[v][1]%P)*(invy-1)%P*invn%P);
				//not choose edge x->v
				Inc(t0,f[x][0]*f[v][1]%P);
				Inc(t1,f[x][1]*f[v][1]%P);
				f[x][0]=t0;f[x][1]=t1;
			}
	}

	void solve()
	{
		if(y==1) return printf("%lld\n",ksm(n,n-2)),void();
		invn=ksm(n,P-2);invy=ksm(y,P-2);
		for(int i=1,u,v;i<n;i++)
			scanf("%d%d",&u,&v),
			T[u].push_back(v),T[v].push_back(u);
		dfs(1,0);
		printf("%lld\n",f[1][1]*ksm(n,n-2)%P*ksm(y,n)%P);
		
	}
}

namespace sol2{
	int rev[MAXL];
	ll G[2][MAXL],inv[MAXL],fac[MAXL],ifac[MAXL],F[MAXL],nF[MAXL];

	void preworks()
	{
		G[0][0]=G[1][0]=1;
		G[0][1]=ksm(g[0],(P-1)/MAXL);
		G[1][1]=ksm(g[1],(P-1)/MAXL);
		for(int i=2;i<MAXL;i++)
			G[0][i]=G[0][i-1]*G[0][1]%P,
			G[1][i]=G[1][i-1]*G[1][1]%P;
		inv[1]=1;
		for(int i=2;i<MAXL;i++)
			inv[i]=Sub(P,(P/i)*inv[P%i]%P);
	}
	
	int init(int n)
	{
		int tot=1,lg2=0;
		while(tot<n) tot<<=1,lg2++;
		for(int i=0;i<tot;i++)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
		return tot;
	}

	void NTT(ll *a,int n,int f)
	{
		ll *ed=a+n;
		for(int i=0;i<n;i++)
			if(i>rev[i])
				swap(a[i],a[rev[i]]);
		for(int i=2;i<=n;i<<=1)
			for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
				for(int k=0;k<(i>>1);k++)
				{
					ll u=x[k],t=y[k]*G[f][MAXL/i*k]%P;
					x[k]=Add(u,t);y[k]=Sub(u,t);
				}
		if(f)
			for(int i=0;i<n;i++)
				a[i]=a[i]*inv[n]%P;
	}

	void Mul(ll *a,ll *b,ll *Res,int l1,int l2)
	{
		static ll t1[MAXL],t2[MAXL];
		int tot=init(l1+l2);
		memset(t1,0,sizeof(ll)*tot);
		memset(t2,0,sizeof(ll)*tot);
		for(int i=0;i<l1;i++)
			t1[i]=a[i];
		for(int i=0;i<l2;i++)
			t2[i]=b[i];
		NTT(t1,tot,0);NTT(t2,tot,0);
		for(int i=0;i<tot;i++)
			t1[i]=t1[i]*t2[i]%P;
		NTT(t1,tot,1);
		for(int i=0;i<l1+l2;i++)
			Res[i]=t1[i];
	}

	void Inv(ll *a,ll *Res,int n)
	{
		if(n==1)
			return Res[0]=ksm(a[0],P-2),void();
		Inv(a,Res,(n+1)>>1);
		static ll t1[MAXL],t2[MAXL];
		int lim=(n+1)>>1,tot=init(2*n);
		memset(t1,0,sizeof(ll)*tot);
		memset(t2,0,sizeof(ll)*tot);
		for(int i=0;i<lim;i++)
			t1[i]=Res[i];
		for(int i=0;i<n;i++)
			t2[i]=a[i];
		NTT(t1,tot,0);NTT(t2,tot,0);
		for(int i=0;i<tot;i++)
			t1[i]=Sub(Add(t1[i],t1[i]),t1[i]*t1[i]%P*t2[i]%P);
		NTT(t1,tot,1);
		for(int i=0;i<n;i++)
			Res[i]=t1[i];
	}

	void Derivation(ll *a,int n)
	{
		for(int i=0;i<n-1;i++)
			a[i]=a[i+1]*(i+1)%P;
		a[n-1]=0;
	}

	void Integral(ll *a,int n)
	{
		for(int i=n;i;i--)
			a[i]=a[i-1]*inv[i]%P;
		a[0]=0;
	}

	void Ln(ll *a,ll *Res,int n)
	{
		static ll t1[MAXL],t2[MAXL];
		for(int i=0;i<n;i++)
			t1[i]=a[i];
		Derivation(t1,n);
		Inv(a,t2,n);
		Mul(t1,t2,t1,n,n);
		Integral(t1,n);
		for(int i=0;i<n;i++)
			Res[i]=t1[i];
	}

	void Exp(ll *a,ll *Res,int n)
	{
		if(n==1)
			return Res[0]=1,void();
		Exp(a,Res,(n+1)>>1);
		static ll t1[MAXL],t2[MAXL],t3[MAXL];
		int tot=init(2*n),lim=(n+1)>>1;
		for(int i=0;i<lim;i++)
			t1[i]=Res[i];
		Ln(t1,t2,n);
		for(int i=0;i<n;i++)
			t3[i]=a[i];
		NTT(t1,tot,0);NTT(t2,tot,0);NTT(t3,tot,0);
		for(int i=0;i<tot;i++)
			t1[i]=t1[i]*Sub(Add(1,t3[i]),t2[i])%P;
		NTT(t1,tot,1);
		for(int i=0;i<n;i++)
			Res[i]=t1[i];
	}

	void solve()
	{
		if(y==1)
			return printf("%lld\n",ksm(n,2*(n-2))),void();
		preworks();
		int ny=ksm(y,P-2)-1,iny=ksm(ny,P-2);
		fac[0]=ifac[0]=1;
		for(int i=1;i<=n;i++)
			fac[i]=fac[i-1]*i%P;
		ifac[n]=ksm(fac[n],P-2);
		for(int i=n-1;i;i--)
			ifac[i]=ifac[i+1]*(i+1)%P;
		for(int i=1;i<=n;i++)
			F[i]=1ll*n*n%P*iny%P*ksm(i,i)%P*ifac[i]%P;
		Exp(F,nF,n+1);
		printf("%lld\n",fac[n]*ksm(ny,n)%P*ksm(n,P-5)%P*nF[n]%P*ksm(y,n)%P);
	}
}

ll a[MAXL],b[MAXL],c[MAXL];

int main()
{
	scanf("%d%d%d",&n,&y,&op);
	if(op==0) sol0::solve();
	else if(op==1) sol1::solve();
	else if (op==2) sol2::solve();
}
