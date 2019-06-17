#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MAXM=3010;
const int P=1E9+7;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

int S[MAXM][MAXM],n,k,a[MAXN],b[MAXN],vis[MAXM][MAXM];
ll fac[MAXN],ifac[MAXN];

ll C(int n,int m)
{
	if(n<m||n<0||m<0)
		return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

int Ask(int x1,int y1,int x2,int y2)
{
	if(x1>x2||y1>y2)
		return 0;
	x1=min(x1,3005);x2=min(x2,3005);
	y1=min(y1,3005);y2=min(y2,3005);
	x1=max(x1,1);x2=max(x2,1);
	y1=max(y1,1);y2=max(y2,1);
	return S[x2][y2]-S[x1-1][y2]-S[x2][y1-1]+S[x1-1][y1-1];
}

bool Chk(int lim)
{
	for(int i=1;i<=3001-lim;i++)
		for(int j=1;j<=3001-lim;j++)
			if(Ask(i,j,i+lim,j+lim)>=k)
				return true;
	return false;
}
	
ll Calc(int lim)
{
	ll Ret=0;
	for(int i=1;i<=3001;i++)
		for(int j=1;j<=3001;j++)
		{
			int S1=Ask(i,j,i+lim,j+lim),S2=Ask(i,j,i,j+lim),S3=Ask(i,j,i+lim,j);
			if(!S1||!S2)
				continue;
			(Ret+=(C(S1,k)-C(S1-S2,k)-C(S1-S3,k)+C(S1-S2-S3+Ask(i,j,i,j),k))%P)%=P;
		}
	return Ret;
}

int main()
{
	scanf("%d%d",&n,&k);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[n]=ksm(fac[n],P-2);
	for(int i=n-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]),a[i]++,b[i]++,S[a[i]][b[i]]++;
	for(int i=1;i<=3005;i++)
		for(int j=1;j<=3005;j++)
			S[i][j]+=S[i-1][j]+S[i][j-1]-S[i-1][j-1];
	int L=0,R=3000,Ans=3000;
	while(L<=R)
	{
		int Mid=(L+R)>>1;
		if(Chk(Mid))
			Ans=Mid,R=Mid-1;
		else
			L=Mid+1;
	}
	printf("%d\n%lld\n",Ans,Calc(Ans));
}
