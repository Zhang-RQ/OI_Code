#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int MAXL=262144;
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
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

int D,n,m,rev[MAXL];
ll wn[2][MAXL],f[MAXL],h[MAXL],t1[MAXL],t2[MAXL],fac[MAXL],ifac[MAXL];

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
		if(i>rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
		for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
			for(int k=0;k<(i>>1);k++)
			{
				ll u=x[k],t=y[k]*wn[f][MAXL/i*k]%P;
				x[k]=Add(u,t);y[k]=Sub(u,t);
			}
	if(f)
		for(int i=0,inv=ksm(n,P-2);i<n;i++)
			a[i]=a[i]*inv%P;
}

int main()
{
	wn[0][0]=wn[1][0]=1;
	wn[0][1]=ksm(g[0],(P-1)/MAXL);
	wn[1][1]=ksm(g[1],(P-1)/MAXL);
	for(int i=2;i<MAXL;i++)
		wn[0][i]=wn[0][i-1]*wn[0][1]%P,
		wn[1][i]=wn[1][i-1]*wn[1][1]%P;
	scanf("%d%d%d",&D,&n,&m);
	if(n<2*m)
		return puts("0"),0;
	if(n-2*m+1>=D)
		return printf("%lld\n",ksm(D,n)),0;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=D;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[D]=ksm(fac[D],P-2);
	for(int i=D-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=0;i<=D;i++)
		t1[i]=(i&1?P-1:1)*ksm((P+D-2*i)%P,n)%P*ifac[i]%P,
		t2[i]=ifac[i];
	int tot=init(2*D+5);
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++)
		f[i]=t1[i]*t2[i]%P;
	NTT(f,tot,1);
	for(int i=0;i<=D;i++)
		f[i]=f[i]*fac[D]%P*ifac[D-i]%P*ksm(2,P-1-i)%P;
	memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
	for(int i=0;i<=D;i++)
		t1[i]=f[D-i]*fac[D-i]%P,
		t2[i]=(i&1?P-1:1)*ifac[i]%P;
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++)
		t1[i]=t1[i]*t2[i]%P;
	NTT(t1,tot,1);
	for(int i=0;i<=D;i++)
		h[i]=t1[D-i]*ifac[i]%P;
	ll Ans=0;
	for(int i=0;i<=n-2*m;i++)
		Inc(Ans,h[i]);
	printf("%lld\n",Ans);
}
