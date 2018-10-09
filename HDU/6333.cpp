#include<cstdio>
#include<algorithm>
#include<cassert>

using namespace std;

typedef long long ll;

const int P=1E9+7;
const int G_MAXN=1E5+10;
const int inv2=5E8+4;

int blksiz=330;

struct Query{
	int n,m,id;
	bool operator < (const Query &rhs) const {return n/blksiz<rhs.n/blksiz||(n/blksiz==rhs.n/blksiz&&m<rhs.m);}
}Q[G_MAXN];

int cur_n,cur_m,q;
ll tAns=1,fac[G_MAXN],ifac[G_MAXN],Ans[G_MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void init_fac()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<G_MAXN;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[G_MAXN-1]=ksm(fac[G_MAXN-1],P-2);
	for(int i=G_MAXN-2;i>=1;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
}

ll C(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

inline void inc_n()
{
	tAns=(tAns*2-C(cur_n,cur_m)+P)%P;
	++cur_n;
}

inline void dec_n()
{
	tAns=(tAns+C(cur_n-1,cur_m)+P)%P*inv2%P;
	--cur_n;
}

inline void inc_m(){tAns=(tAns+C(cur_n,++cur_m))%P;}

inline void dec_m(){tAns=(tAns-C(cur_n,cur_m--)+P)%P;}

int main()
{
	init_fac();
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
		scanf("%d%d",&Q[i].n,&Q[i].m),Q[i].id=i;
	sort(Q+1,Q+1+q);
	for(int i=1;i<=q;i++)
	{
		while(cur_n>Q[i].n) dec_n();
		while(cur_n<Q[i].n) inc_n();
		while(cur_m>Q[i].m) dec_m();
		while(cur_m<Q[i].m) inc_m();
		Ans[Q[i].id]=tAns;
	}
	for(int i=1;i<=q;i++) printf("%lld\n",Ans[i]);
}