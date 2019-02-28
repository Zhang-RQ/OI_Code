#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=262144<<1;
const int P=998244353;
const int g[]={3,(P+1)/3};

int rev[MAXN],n;
ll tp[MAXN],itp[MAXN],tp2[MAXN],itp2[MAXN];
ll _G_[2][MAXN],G[MAXN],G0[MAXN],G1[MAXN],G2[MAXN],X1[MAXN],X3[MAXN],X4[MAXN],F0[MAXN],F1[MAXN],F2[MAXN];

ll Add(ll a,ll b){a+=b;return a>=P?a-P:a;}

ll Sub(ll a,ll b){a-=b;return a<0?a+P:a;}

void Inc(ll &a,ll b){a+=b;if(a>=P) a-=P;}

void Dec(ll &a,ll b){a-=b;if(a<0) a+=P;}

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

int init(int n)
{
	int tot=1,lg2=0;
	while(tot<=n) tot<<=1,lg2++;
	for(int i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
	return tot;
}

void NTT(ll *a,int n,int f)
{
	ll *ed=a+n;
	for(int i=0;i<n;i++)
		if(i>rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
		for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
			for(int k=0;k<(i>>1);k++)
			{
				ll u=x[k],t=y[k]*_G_[f][1ll*k*MAXN/i]%P;
				x[k]=Add(u,t);y[k]=Sub(u,t);
			}
	if(f) for(int i=0,inv=ksm(n,P-2);i<n;i++) a[i]=a[i]*inv%P;
}

void Inv(ll *a,ll *Res,int n)
{
    if(n==1) return Res[0]=ksm(a[0],P-2),void();
    Inv(a,Res,(n+1)>>1);
    int tot=init(n<<1),lst=(n+1)>>1;
    static ll t1[MAXN],t2[MAXN];
    memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
    for(int i=0;i<n;i++) t1[i]=a[i];
    for(int i=0;i<lst;i++) t2[i]=Res[i];
    NTT(t1,tot,0);NTT(t2,tot,0);
    for(int i=0;i<tot;i++) t1[i]=Sub(2*t2[i],t2[i]*t2[i]%P*t1[i]%P);
    NTT(t1,tot,1);
    for(int i=0;i<n;i++) Res[i]=t1[i];
}

int main()
{
	_G_[0][0]=_G_[1][0]=1;
	_G_[0][1]=ksm(g[0],(P-1)/MAXN);_G_[1][1]=ksm(g[1],(P-1)/MAXN);
	for(int i=2;i<MAXN;i++) _G_[0][i]=_G_[0][i-1]*_G_[0][1]%P,_G_[1][i]=_G_[1][i-1]*_G_[1][1]%P;
	scanf("%d",&n);G[0]=1;
	int tot=init(4*n);//notice
	for(int i=2;i<=n;i++) G[i]=Add(G[i-2],i>3?G[i-4]:0);
	for(int i=0;i<=n;i++) G0[i]=G[i]*i%P*i%P,G1[i]=G[i]*(i+1)%P*(i+1)%P,G2[i]=G[i]*(i+2)%P*(i+2)%P;
	X1[1]=1;X3[3]=1;X4[4]=1;
	NTT(G0,tot,0);NTT(G1,tot,0);NTT(G2,tot,0);NTT(X1,tot,0);NTT(X3,tot,0);NTT(X4,tot,0);
	for(int i=0;i<tot;i++) tp[i]=Sub(Add(X4[i]*G2[i]%P*G0[i]%P,1),Add(X1[i]*G0[i]%P,Add(X3[i]*G2[i]%P,X4[i]*G1[i]%P*G1[i]%P)));
	for(int i=0;i<tot;i++) tp2[i]=Sub(1,X3[i]*G2[i]%P);
	NTT(tp2,tot,1);Inv(tp2,itp2,n);
	init(4*n);NTT(itp2,tot,0);
	NTT(tp,tot,1);Inv(tp,itp,n);
	init(4*n);NTT(itp,tot,0);
	for(int i=0;i<tot;i++) F0[i]=Add(G0[i]*Sub(1,X3[i]*G2[i]%P)%P,X3[i]*G1[i]%P*G1[i]%P)*itp[i]%P;
	for(int i=0;i<tot;i++) F1[i]=Add(G1[i]*Sub(1,X1[i]*G0[i]%P)%P,X1[i]*G1[i]%P*G0[i]%P)*itp[i]%P;
	for(int i=0;i<tot;i++) F2[i]=Add(G2[i],X1[i]*F1[i]%P*G1[i]%P)*itp2[i]%P;
	NTT(F0,tot,1);NTT(F1,tot,1);NTT(F2,tot,1);
	ll Ans=Add(G[n-1],G[n-3])*(n-1)%P*(n-1)%P*n%P;
	for(int i=2;i<=n-2;i++)
	{
		Inc(Ans,G[i-1]*(i-1)%P*(i-1)%P*F0[n-i-1]%P*i%P);
		Inc(Ans,G[i-2]*(i-1)%P*(i-1)%P*F1[n-i-2]%P*i%P*2%P);
		if(i>=3&&i<=n-3) Inc(Ans,G[i-3]*(i-1)%P*(i-1)%P*F2[n-i-3]%P*i%P);
	}
	printf("%lld\n",Ans);
}
