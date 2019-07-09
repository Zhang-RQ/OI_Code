#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2010;
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

char s[MAXN];
int f[MAXN][MAXN];
int n,m,trans[MAXN];
int nxt[MAXN],mx[MAXN];

int main()
{
	scanf("%d",&m);
	scanf("%s",s+1);
	n=strlen(s+1);
	mx[0]=s[1]-'a';
	trans[0]=1;
	for(int i=2,j=0;i<=n;i++)
	{
		while(j&&s[j+1]!=s[i])
			j=nxt[j];
		if(s[j+1]==s[i])
			++j;
		nxt[i]=j;
	}
	for(int i=1;i<=n;i++)
	{
		mx[i]=mx[nxt[i]];
		if(i<n)
			mx[i]=max(mx[i],s[i+1]-'a');
		if(mx[i]==s[i+1]-'a')
			trans[i]=i+1;
		else
		{
			int p=nxt[i];
			while(p&&s[p+1]!=mx[i]+'a') //N^2?
				p=nxt[p];
			trans[i]=s[p+1]==mx[i]+'a'?p+1:0;
		}
	}
	f[0][0]=1;
	for(int i=0;i<m;i++)
		for(int j=0;j<=n;j++)
			if(f[i][j])
			{
				Inc(f[i+1][trans[j]],f[i][j]);
				Inc(f[i+1][0],f[i][j]*(25ll-mx[j])%P);
			}
	ll Ans=0;
	for(int i=0;i<=n;i++)
	{
		int x=i;
		for(int j=1;j<=m;j++)
		{
			Inc(Ans,(25ll-mx[x])*f[m-j][i]%P);
			x=trans[x];
		}
		if(x==i)
			Inc(Ans,1);
	}
	printf("%lld\n",Sub(ksm(26,m),Ans));
}
