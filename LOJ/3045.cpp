#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int OFS=5E4+5;
const int P=998244353;

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

int n,m,p[MAXN],sump,s[MAXN],cntf,cntg;
ll f[MAXN],g[MAXN],tmp[MAXN],ft[MAXN],fv[MAXN],gt[MAXN],gv[MAXN];
ll pre[MAXN],suf[MAXN],pred[MAXN],sufd[MAXN];

ll calc(ll *t,ll *v,int d)
{
	pre[0]=1;suf[d+1]=1;
	for(int i=1;i<=d;i++)
		pre[i]=pre[i-1]*Sub(1,v[i])%P;
	for(int i=d;i;i--)
		suf[i]=suf[i+1]*Sub(1,v[i])%P;
	ll Ans=0;
	for(int i=1;i<=d;i++)
		Inc(Ans,t[i]*pre[i-1]%P*suf[i+1]%P);
	return Ans;
}

ll calcd(ll *t,ll *v,int d)
{
	pre[0]=1;suf[d+1]=1;
	pred[0]=1;sufd[d+1]=0;
	for(int i=1;i<=d;i++)
	{
		pre[i]=pre[i-1]*Sub(1,v[i])%P;
		pred[i]=Sub(pred[i-1]*Sub(1,v[i])%P,v[i]*pre[i-1]%P);
	}
	for(int i=d;i;i--)
	{
		suf[i]=suf[i+1]*Sub(1,v[i])%P;
		sufd[i]=Sub(sufd[i+1]*Sub(1,v[i])%P,v[i]*suf[i+1]%P);
	}
	ll Ans=0;
	for(int i=1;i<=d;i++)
		Inc(Ans,t[i]*Add(pre[i-1]*sufd[i+1]%P,pred[i-1]*suf[i+1]%P)%P);
	return Ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&s[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]),
		sump+=p[i];
	ll is=ksm(sump,P-2);
	f[OFS]=g[OFS]=1;
	for(int i=1;i<=n;i++)
	{
		int coef=s[i]?P-1:1;
		memset(tmp,0,sizeof tmp);
		for(int j=-sump;j+p[i]<=sump;j++)
			Inc(tmp[OFS+j+p[i]],f[OFS+j]);
		for(int j=-sump+p[i];j<=sump;j++)
			Inc(tmp[OFS+j-p[i]],coef*f[OFS+j]%P);
		memcpy(f,tmp,sizeof tmp);
		memset(tmp,0,sizeof tmp);
		for(int j=-sump;j+p[i]<=sump;j++)
			Inc(tmp[OFS+j+p[i]],g[OFS+j]);
		for(int j=-sump+p[i];j<=sump;j++)
			Inc(tmp[OFS+j-p[i]],g[OFS+j]);
		memcpy(g,tmp,sizeof tmp);
	}
	for(int i=-sump;i<=sump;i++)
		if(f[OFS+i]||g[OFS+i]) //notice
			ft[++cntf]=f[OFS+i],fv[cntf]=(i*is%P+P)%P;
	for(int i=-sump;i<=sump;i++)
		if(g[OFS+i]||g[OFS+i]) //notice
			gt[++cntg]=g[OFS+i],gv[cntg]=(i*is%P+P)%P;
	ll F=calc(ft,fv,cntf),dF=calcd(ft,fv,cntf),G=calc(gt,gv,cntg),dG=calcd(gt,gv,cntg);
	printf("%lld\n",Sub(dF*G%P,F*dG%P)*ksm(G*G%P,P-2)%P);
}
