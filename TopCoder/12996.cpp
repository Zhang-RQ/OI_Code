#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

class TaroCheckers{
	static const int MAXN=55;
	static const int MAXM=205;
	static const int P=1E9+7;

	void inc(int &x,int y){x+=y;if(x>=P) x-=P;}
	
	int f[2][MAXN][MAXN],cntl[MAXM],cntr[MAXM];

	ll fac[MAXM],ifac[MAXM];
	
	ll ksm(ll a,ll b)
	{
		ll ret=1;
		for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
		return ret;
	}

	ll A(int n,int m){return n>=m?fac[n]*ifac[n-m]%P:0;}

public:
	
	int getNumber(vector<int> L,vector<int> R,int m)
	{
		memset(f,0,sizeof f);memset(cntl,0,sizeof cntl);memset(cntr,0,sizeof cntr);
		int n=L.size();
		fac[0]=ifac[0]=1;
		for(int i=1;i<=m;i++) fac[i]=fac[i-1]*i%P;
		ifac[m]=ksm(fac[m],P-2);
		for(int i=m-1;i;i--) ifac[i]=ifac[i+1]*(i+1)%P; 
		f[0][0][0]=1;
		for(int i=0;i<n;i++) cntl[L[i]]++;
		for(int i=0;i<n;i++) cntr[m-R[i]+1]++;
		int tot=0;
		for(int i=0,nw;i<m;i++)
		{
			nw=i&1;memset(f[!nw],0,sizeof f[!nw]);
			int cnt1=cntl[i+1],cnt2=cntr[i+1];
			for(int j=0;j<=n;j++)
				for(int k=0;k<=n;k++)
					if(f[nw][j][k])
					{
						if(j+1>=cnt1) inc(f[!nw][j+1-cnt1][k+cnt2],f[nw][j][k]*A(j+1,cnt1)%P);
						if(j>=cnt1) inc(f[!nw][j-cnt1][k+cnt2],f[nw][j][k]*A(j,cnt1)%P*(tot-cnt2+1)%P);
						if(j>=cnt1&&k+cnt2-1>=0) inc(f[!nw][j-cnt1][k+cnt2-1],f[nw][j][k]*A(j,cnt1)%P*(k+cnt2)%P);
					}
			tot+=cnt1-cnt2;
		}
		return f[m&1][0][0];
	}
};
