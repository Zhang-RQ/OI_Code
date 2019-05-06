#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int MAXN=1010;
const int MAXM=2510;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n,c,k,sum[MAXN],C0,C1,D0,D1,b[MAXN],s[MAXN],lim[MAXN],limc[MAXN];
ll g[MAXM],h[MAXM],f[2][2][MAXM][315],tmp[MAXM][315];
vector<int> v[MAXN];

void solve()
{
	memset(g,0,sizeof g);
	memset(h,0,sizeof h);
	memset(f,0,sizeof f);
	memset(lim,-1,sizeof lim);
	memset(limc,0,sizeof limc);
	memset(sum,0,sizeof sum);
	scanf("%d%d",&n,&c);
	scanf("%d%d%d%d",&C0,&C1,&D0,&D1);
	for(int i=1;i<=n;i++)
		v[i].clear();
	for(int i=1;i<=n;i++)
		scanf("%d%d",&b[i],&s[i]),
		v[b[i]].push_back(i),
		sum[b[i]]+=s[i];
	scanf("%d",&k);
	for(int i=1,id;i<=k;i++)
	{
		scanf("%d",&id);
		scanf("%d",&lim[id]);
		limc[b[id]]=1;
	}
	g[0]=h[0]=1;
	int cur=0,lst=0;
	for(int i=1;i<=n;i++)
		if(!~lim[i])
		{
			cur+=s[i];
			cur=min(cur,D0);
			for(int j=cur;j>=s[i];j--)
				if(cur-j<=D1)
					Inc(g[j],g[j-s[i]]);
		}
	cur=0;
	for(int i=1;i<=c;i++)
		if(!limc[i]&&sum[i])
		{
			cur+=sum[i];
			cur=min(cur,C0);
			for(int j=cur;j>=sum[i];j--)
				if(cur-j<=C1)
					Inc(h[j],h[j-sum[i]]);
		}
	f[0][0][0][0]=1;
	for(int i=1;i<=c;i++)
		if(limc[i])
		{
			for(int j=0;j<=C0;j++)
				for(int k=0;k<=min(D0,300);k++)
					tmp[j][k]=Add(f[lst][0][j][k],f[lst][1][j][k]);
			for(int j=0;j<=C0;j++)
				for(int k=0;k<=min(D0,300);k++)
					f[lst][0][j][k]=f[lst][1][j][k]=tmp[j][k];
			for(int ci:v[i])
				if(~lim[ci])
				{
					memset(f[!lst],0,sizeof f[!lst]);
					for(int j=0;j<=C0;j++)
						for(int k=0;k<=min(D0,300);k++)
						{
							if(lim[ci]!=0) Inc(f[!lst][0][j][k+s[ci]],f[lst][0][j][k]);
							if(lim[ci]!=1) Inc(f[!lst][0][j][k],f[lst][0][j][k]);
							if(lim[ci]!=2) Inc(f[!lst][1][j][k+s[ci]],f[lst][1][j][k]);
							if(lim[ci]!=3) Inc(f[!lst][1][j][k],f[lst][1][j][k]);
						}
					lst^=1;
				}
			memcpy(tmp,f[lst][0],sizeof tmp);
			memset(f[lst][0],0,sizeof f[lst][0]);
			for(int j=0;j+sum[i]<=C0;j++)
				for(int k=0;k<=min(D0,300);k++)
					Inc(f[lst][0][j+sum[i]][k],tmp[j][k]);
		}
	int S=0;
	for(int i=1;i<=n;i++)
		S+=s[i];
	ll Ans=0;
	for(int i=1;i<=2500;i++)
		Inc(g[i],g[i-1]);
	for(int i=1;i<=2500;i++)
		Inc(h[i],h[i-1]);
	for(int i=0;i<=C0;i++)
		for(int j=0;j<=min(D0,300);j++)
		{
			ll dlt=Add(f[lst][0][i][j],f[lst][1][i][j]),dg=0,dh=0;
			int L0=max(0,S-C1-i),R0=C0-i,L1=max(0,S-D1-j),R1=D0-j;
			if(L0>R0||L1>R1) continue;
			dg=g[R1];dh=h[R0];
			if(L1) Dec(dg,g[L1-1]);
			if(L0) Dec(dh,h[L0-1]);
			Inc(Ans,dlt*dh%P*dg%P);
		}
	printf("%lld\n",Ans);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
