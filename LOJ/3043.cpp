#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int P=998244353;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n,m;
ll f[MAXN<<3],g[MAXN<<3],Mf[MAXN<<3],Mg[MAXN<<3],sf[MAXN<<3],pw=1;

void pushup(int x){sf[x]=Add(f[x],Add(sf[x<<1],sf[x<<1|1]));}

void apply_f(int x,ll v)
{
	f[x]=f[x]*v%P;
	sf[x]=sf[x]*v%P;
	Mf[x]=Mf[x]*v%P;
}

void apply_g(int x,ll v)
{
	g[x]=g[x]*v%P;
	Mg[x]=Mg[x]*v%P;
}

void pushdown(int x)
{
	if(Mf[x]!=1)
		apply_f(x<<1,Mf[x]),apply_f(x<<1|1,Mf[x]),Mf[x]=1;
	if(Mg[x]!=1)
		apply_g(x<<1,Mg[x]),apply_g(x<<1|1,Mg[x]),Mg[x]=1;
}

void build(int x,int l,int r)
{
	g[x]=Mf[x]=Mg[x]=1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}

void Modify(int x,int l,int r,int ql,int qr)
{
	pushdown(x);
	if(qr<l||ql>r)
	{
		Inc(f[x],Sub(pw,g[x]));
		g[x]=g[x]*2%P;
		apply_f(x<<1,2);
		apply_f(x<<1|1,2);
		apply_g(x<<1,2);
		apply_g(x<<1|1,2);
		pushup(x);
		return;
	}
	if(ql<=l&&r<=qr)
	{
		Inc(f[x],pw);
		apply_f(x<<1,2);
		apply_f(x<<1|1,2);
		pushup(x);
		return;
	}
	Inc(g[x],pw);
	int mid=(l+r)>>1;
	Modify(x<<1,l,mid,ql,qr);
	Modify(x<<1|1,mid+1,r,ql,qr);
	pushup(x);
}

int main()
{
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i=1,op,l,r;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==1) scanf("%d%d",&l,&r),Modify(1,1,n,l,r),pw=(pw*2)%P;
		else printf("%lld\n",sf[1]);
	}
}
