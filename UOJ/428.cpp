#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXL=262144;
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

int rev[MAXL],A[MAXL],B[MAXL],n,Asiz,Bsiz;
ll G[2][MAXL],fac[MAXL],ifac[MAXL];
ll f[MAXL],h[MAXL],t1[MAXL],t2[MAXL],t3[MAXL],t4[MAXL],t5[MAXL];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

int init(int n)
{
	int tot=1,lg2=0;
	while(tot<n)
		tot<<=1,lg2++;
	for(int i=0;i<tot;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
	return tot;
}

void NTT(ll *a,int n,int f)
{
	ll *ed=a+n;
	for(int i=0;i<n;i++)
		if(rev[i]<i)
			swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
		for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
			for(int k=0;k<(i>>1);k++)
			{
				ll u=x[k],t=y[k]*G[f][MAXL/i*k]%P;
				x[k]=Add(u,t);y[k]=Sub(u,t);
			}
	if(f)
		for(int i=0,inv=ksm(n,P-2);i<n;i++)
			a[i]=a[i]*inv%P;
}

void solve(int l,int r)
{
	if(l==r)
	{
		if(!l)
			return;
		Inc(f[l],B[l-1]);
		Dec(f[l],A[l-1]!=0);
		if(l!=1)
			Inc(h[l],f[l]);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	int tot=init(mid+r-2*l+3);//2 spare
	memset(t1,0,sizeof(ll)*tot);
	memset(t2,0,sizeof(ll)*tot);
	memset(t3,0,sizeof(ll)*tot);
	memset(t4,0,sizeof(ll)*tot);
	memset(t5,0,sizeof(ll)*tot);
	for(int i=l;i<=mid;i++)
		t1[i-l]=h[i]*ifac[i]%P;
	for(int i=2;i<=min(mid,r-l);i++)
		t2[i]=f[i]*ifac[i-1]%P;
	for(int i=0;i<=r-l;i++)
		t3[i]=A[i];
	NTT(t1,tot,0);NTT(t2,tot,0);NTT(t3,tot,0);
	for(int i=0;i<tot;i++)
		t3[i]=t3[i]*t1[i]%P,
		t2[i]=t2[i]*t1[i]%P;
	NTT(t3,tot,1);NTT(t2,tot,1);
	for(int i=mid+1;i<=r;i++)
		Inc(f[i],t3[i-l-1]*fac[i-1]%P),
		Inc(h[i],t2[i-l]*fac[i-1]%P);
	if(l>0)
	{
		for(int i=l;i<=mid;i++)
			t4[i-l]=(i<2)?0:f[i]*ifac[i-1]%P;
		for(int i=0;i<=r-l;i++)
			t5[i]=h[i]*ifac[i]%P;
		NTT(t4,tot,0);NTT(t5,tot,0);
		for(int i=0;i<tot;i++)
			t4[i]=t4[i]*t5[i]%P;
		NTT(t4,tot,1);
		for(int i=mid+1;i<=r;i++)
			Inc(h[i],t4[i-l]*fac[i-1]%P);
	}
	solve(mid+1,r);
}

int main()
{
	G[0][0]=G[1][0]=1;
	G[0][1]=ksm(g[0],(P-1)/MAXL);
	G[1][1]=ksm(g[1],(P-1)/MAXL);
	for(int i=2;i<MAXL;i++)
		G[0][i]=G[0][i-1]*G[0][1]%P,
		G[1][i]=G[1][i-1]*G[1][1]%P;
	scanf("%d%d%d",&n,&Asiz,&Bsiz);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[n]=ksm(fac[n],P-2);
	for(int i=n-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=1,x;i<=Asiz;i++)
	{
		scanf("%d",&x);
		A[x]=ifac[x];
	}
	for(int i=1,x;i<=Bsiz;i++)
	{
		scanf("%d",&x);
		B[x]=1;
	}
	h[0]=1;
	solve(0,n);
	printf("%lld\n",f[n]);
}
