#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=262144;
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
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll ksm(ll a,ll b,ll Mod)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=Mod) if(b&1) (ret*=a)%=Mod;
	return ret;
}

int rev[MAXN],n,p,m,lim;
ll G[2][MAXN],Res[51][1010],cur[51][1010];

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
	ll inv=ksm(n,P-2);
	if(f) for(int i=0;i<n;i++) a[i]=a[i]*inv%P;
}

int init(int n)
{
	int tot=1,lg2=0;
	while(tot<n) tot<<=1,lg2++;
	for(int i=0;i<tot;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
	return tot;
}

void Mul(ll *x,ll *y,ll *Res,int n)
{
	static ll t1[MAXN],t2[MAXN];
	int tot=init(2*n);
	memset(t1,0,sizeof(ll)*tot);
	memset(t2,0,sizeof(ll)*tot);
	for(int i=0;i<n;i++)
		t1[i]=x[i],t2[i]=y[i];
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++)
		t1[i]=t1[i]*t2[i]%P;
	NTT(t1,tot,1);
	for(int i=0;i<tot;i++)
		Res[i]=t1[i];
}

void Apply(ll A[51][1010],ll B[51][1010],ll Res[51][1010],int len2)
{
	static ll t[51][1010],a[MAXN],b[MAXN],c[MAXN];
	memset(t,0,sizeof t);
	for(int i=0;i<=m;i++)
		for(int j=0;j<=p;j++)
			Inc(t[j*ksm(10,len2,p)%p][i],A[j][i]);
	for(int i=0;i<=m;i++)
		for(int j=0;j<p;j++)
			a[i*lim+j]=t[j][i],
			b[i*lim+j]=B[j][i];
	int tot=(m+1)*lim;
	Mul(a,b,c,tot);
	memset(Res,0,sizeof(ll)*51510);
	for(int i=0;i<=tot;i++)
		if(i/lim<=m)
			Inc(Res[(i%lim)%p][i/lim],c[i]);
}

ll T[MAXN],A[MAXN],B[MAXN];

int main()
{
	G[0][0]=G[1][0]=1;
	G[0][1]=ksm(g[0],(P-1)/MAXL); 
	G[1][1]=ksm(g[1],(P-1)/MAXL);
	for(int i=2;i<MAXL;i++)
		G[0][i]=G[0][i-1]*G[0][1]%P,
		G[1][i]=G[1][i-1]*G[1][1]%P;
	scanf("%d%d%d",&n,&p,&m);
	lim=p*2;
	int len=-1,curlen=1;
	for(int i=0;i<=min(9,m);i++)
		cur[i%p][i]++;
	while(n)
	{
		if(n&1)
		{
			if(len==-1)
				memcpy(Res,cur,sizeof cur),len=curlen;
			else
				Apply(cur,Res,Res,len),len+=curlen;
		}
		Apply(cur,cur,cur,curlen);
		curlen<<=1;n>>=1;
	}
	printf("%lld ",Res[0][0]);
	for(int i=1;i<=m;i++)
		Inc(Res[0][i],Res[0][i-1]),printf("%lld%c",Res[0][i],"\n "[i!=m]);
}
