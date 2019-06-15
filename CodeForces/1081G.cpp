#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int P;

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

int n,k,inv2,inv4;
ll Ans,sum[MAXN<<1];
map<int,int> M;

ll calc(int len1,int len2)
{
	ll ret=1ll*len1*len2%P*inv2%P;
	for(int i=1;i<=len1;i++)
		Dec(ret,1ll*Sub(sum[i+len2],sum[i])%P);
	return ret;
}

void solve(int l,int r,int d)
{
	if(l==r||d==k)
	{
		int len=r-l+1;M[len]++;
		Inc(Ans,1ll*len*(len-1)%P*inv4%P);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid,d+1);solve(mid+1,r,d+1);
}

int main()
{
	scanf("%d%d%d",&n,&k,&P);
	inv2=ksm(2,P-2);inv4=ksm(4,P-2);
	for(int i=1;i<=2*n;i++)
		sum[i]=(sum[i-1]+ksm(i,P-2))%P;
	solve(1,n,1);
	for(auto p1:M)
	{
		Inc(Ans,1ll*p1.second*(p1.second-1)%P*inv2%P*calc(p1.first,p1.first)%P);
		for(auto p2:M)
			if(p1.first<p2.first)
				Inc(Ans,1ll*p1.second*p2.second%P*calc(p1.first,p2.first)%P);
	}	
	printf("%lld\n",Ans);
}
