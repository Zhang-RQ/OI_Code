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

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

char s[MAXL];
int n,cnt[MAXL],rev[MAXL];
ll fac[MAXL],ifac[MAXL],f[MAXL],wn[2][MAXL],t1[MAXL],t2[MAXL];

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

void solve(int L,int R)
{
	if(L==R)
	{
		if(L)
			f[L]=cnt[L-1]&1?P-f[L]:f[L];
		return;
	}
	int Mid=(L+R)>>1;
	solve(L,Mid);
	int tot=init(R+Mid-2*L+4);
	memset(t1,0,sizeof(ll)*tot);
	memset(t2,0,sizeof(ll)*tot);
	for(int i=L;i<=Mid;i++)
		t1[i-L]=s[i]=='>'?(cnt[i]&1?P-f[i]:f[i]):0;
	for(int i=1;i<=R-L;i++)
		t2[i]=ifac[i];
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++)
		t1[i]=t1[i]*t2[i]%P;
	NTT(t1,tot,1);
	for(int i=Mid+1;i<=R;i++)
		Inc(f[i],t1[i-L]);
	solve(Mid+1,R);
}

int main()
{
	wn[0][0]=wn[1][0]=1;
	wn[0][1]=ksm(g[0],(P-1)/MAXL);
	wn[1][1]=ksm(g[1],(P-1)/MAXL);
	for(int i=2;i<MAXL;i++)
		wn[0][i]=wn[0][i-1]*wn[0][1]%P,
		wn[1][i]=wn[1][i-1]*wn[1][1]%P;
	scanf("%s",s+1);s[0]='>';
	int n=strlen(s+1)+1;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[n]=ksm(fac[n],P-2);
	for(int i=n-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=1;i<=n;i++)
		cnt[i]=cnt[i-1]+(s[i]=='>');
	f[0]=1;solve(0,n);
	printf("%lld\n",f[n]*fac[n]%P);
}
