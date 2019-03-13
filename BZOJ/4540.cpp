#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3E6+10;
const int Mod=1E9+7;

int n,q,a[MAXN],st[MAXN][20],stk[MAXN],top,lg2[MAXN];
ll fl[MAXN],gl[MAXN],fr[MAXN],gr[MAXN];

int A, B, C, P;
long long lastAns;

inline int rnd() {
    return A = (A * B + (C ^ (int)(lastAns & 0x7fffffffLL)) % P) % P;
}

int Query(int l,int r)
{
	int len=lg2[r-l+1];
	return a[st[l][len]]<a[st[r-(1<<len)+1][len]]?st[l][len]:st[r-(1<<len)+1][len];
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++)
		lg2[i]=lg2[i>>1]+1;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),st[i][0]=i;
	for(int j=1;j<=19;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			if(a[st[i][j-1]]<a[st[i+(1<<(j-1))][j-1]])
				st[i][j]=st[i][j-1];
			else
				st[i][j]=st[i+(1<<(j-1))][j-1];
	for(int i=1;i<=n;i++)
	{
		while(top&&a[stk[top]]>=a[i]) --top;
		fl[i]=fl[stk[top]]+1ll*(i-stk[top])*a[i];
		gl[i]=gl[i-1]+fl[i];
		stk[++top]=i;
	}
	stk[top=1]=n+1;
	for(int i=n;i>=1;i--)
	{
		while(top&&a[stk[top]]>=a[i]) --top;
		fr[i]=fr[stk[top]]+1ll*(stk[top]-i)*a[i];
		gr[i]=gr[i+1]+fr[i];
		stk[++top]=i;
	}
	scanf("%d%d%d%d",&A,&B,&C,&P);
	ll Ans=0;
	for(int i=1,l,r;i<=q;i++)
	{
		l = rnd() % n + 1, r = rnd() % n + 1;
		if (l > r) std::swap(l, r);
		int p=Query(l,r);
		lastAns=1ll*a[p]*(r-p+1)*(p-l+1)+gl[r]-gl[p]+gr[l]-gr[p]-fr[p]*(p-l)-fl[p]*(r-p);
		(Ans+=lastAns%Mod+Mod)%=Mod;
	}
	printf("%lld\n",Ans);
}
