#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1E9+7;
const int MAXN=1E5+10;

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

char str[MAXN];
int t,m,totq,Mx[MAXN];
ll fac[MAXN],ifac[MAXN],f[MAXN],pw[MAXN],Ans[MAXN];
vector<pair<int,int> > v[MAXN];

ll C(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

int main()
{
	fac[0]=ifac[0]=pw[0]=1;
	for(int i=1;i<MAXN;i++) pw[i]=pw[i-1]*25%P;
	for(int i=1;i<MAXN;i++) fac[i]=fac[i-1]*i%P;
	ifac[MAXN-1]=ksm(fac[MAXN-1],P-2);
	for(int i=MAXN-2;i;i--) ifac[i]=ifac[i+1]*(i+1)%P;
	scanf("%d",&t);
	scanf("%s",str+1);
	m=strlen(str+1);
	for(int i=1,opt,n;i<=t;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
			scanf("%s",str+1),m=strlen(str+1);
		else
			scanf("%d",&n),v[m].emplace_back(n,++totq),Mx[m]=max(Mx[m],n);
	}
	ll inv26=ksm(26,P-2);
	for(int i=1;i<MAXN;i++)
		if(v[i].size())
		{
			f[i]=1;
			for(int j=i+1;j<=Mx[i];j++)
				f[j]=pw[j-i]*C(j-1,i-1)%P;
			ll o=ksm(inv26,i);
			f[i-1]=0;
			for(int j=i;j<=Mx[i];j++)
				f[j]=Add(f[j]*o%P,f[j-1]),o=o*inv26%P;
			for(auto x:v[i])
				if(x.first>=i)
					Ans[x.second]=f[x.first]*ksm(26,x.first)%P;
		}
	for(int i=1;i<=totq;i++)
		printf("%lld\n",Ans[i]);
}
