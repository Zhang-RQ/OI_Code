#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E6+10;
const int P=1E9+7;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll fac[MAXN],ifac[MAXN],pw[MAXN];

void init(int m)
{
	fac[0]=ifac[0]=pw[0]=1;
	for(int i=1;i<=m;i++) fac[i]=fac[i-1]*i%P,pw[i]=(pw[i-1]<<1)%P;
	ifac[m]=ksm(fac[m],P-2);
	for(int i=m-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
}

ll C(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

ll solve(int M,int r,int g,int b)
{
	ll Ans=0;
	for(int X=r-1;X<=r;X++)
	{
		if(X<=0) continue;
		for(int e=0;e<=X;e++)
		{
			if((X-e+g-b)&1) continue;
			int oy=(X-e+g-b)>>1,oz=X-e-oy;
			if(oy<0||oz<0) continue;
			int rst=M-r-X-e;
			if(rst<0||rst&1) continue;
			rst>>=1;
			Ans+=pw[e]*C(X,e)%P*C(X-e,oy)%P*C(rst+X-1,X-1)%P;
		}	
	}
	return Ans%P;
}

class LittleElephantAndBoard{
	public:
		int get_Number(int M,int R,int G,int B)
		{
			init(M);
			int r=(B+G-R)/2,g=(B+R-G)/2,b=(R+G-B)/2;
			ll Ans=0;
			Ans+=solve(M,r,g,b)<<1;
			Ans+=solve(M,g,b,r)<<1;
			Ans+=solve(M,b,r,g)<<1;
			Ans%=P;
			return Ans;
		}
};

