#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3E5+10;

int jmp[19][MAXN],dep[MAXN],siz[MAXN],n,q;
ll f[19][MAXN],ssiz[MAXN];
vector<int> T[MAXN];

ll C2(int n)
{
	return 1ll*n*(n-1)/2;
}

void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	jmp[0][x]=fa;
	siz[x]=1;
	ssiz[x]=0;
	for(int v:T[x])
		if(v!=fa)
			dfs(v,x),
			siz[x]+=siz[v],
			ssiz[x]+=C2(siz[v]);
}

int LCA(int x,int y)
{
	if(dep[x]>dep[y])
		swap(x,y);
	for(int j=18;~j;j--)
		if(dep[jmp[j][y]]>=dep[x])
			y=jmp[j][y];
	if(x==y)
		return x;
	for(int j=18;~j;j--)
		if(jmp[j][x]!=jmp[j][y])
			x=jmp[j][x],y=jmp[j][y];
	return jmp[0][x];
}

int NXT(int x,int y)
{
	for(int j=18;~j;j--)
		if(dep[jmp[j][x]]>dep[y])
			x=jmp[j][x];
	return x;
}

ll Query(int x,int y)
{
	ll ret=0;
	for(int j=18;~j;j--)
		if(dep[jmp[j][x]]>dep[y])
			ret+=f[j][x],x=jmp[j][x];
	return ret;
}

void solve()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		T[i].clear();
		for(int j=0;j<=18;j++)
			f[j][i]=jmp[j][i]=0;
	}
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		T[u].push_back(v),
		T[v].push_back(u);
	dfs(1,0);
	for(int x=2;x<=n;x++)
		f[0][x]=1ll*C2(siz[jmp[0][x]]-siz[x])-ssiz[jmp[0][x]]+C2(siz[x]);
	for(int j=1;j<=18;j++)
		for(int i=1;i<=n;i++)
			jmp[j][i]=jmp[j-1][jmp[j-1][i]],
			f[j][i]=f[j-1][i]+f[j-1][jmp[j-1][i]];
	for(int i=1,u,v;i<=q;i++)
	{
		scanf("%d%d",&u,&v);
		if(u==v)
		{
			printf("%lld\n",C2(n)-ssiz[u]-C2(n-siz[u])+1);
			continue;
		}
		int l=LCA(u,v);
		if(l==v)
			swap(u,v);
		if(l==u)
		{
			int nxt=NXT(v,l);
			ll Ans=Query(v,l)+C2(n-siz[nxt]);
			Ans=Ans-ssiz[l]+C2(siz[nxt])-C2(n-siz[l]);
			Ans=Ans+C2(siz[v])-ssiz[v];
			printf("%lld\n",Ans+dep[u]+dep[v]-2*dep[l]+1);
		}
		else
		{
			int nxtu=NXT(u,l),nxtv=NXT(v,l);
			ll Ans=Query(u,l)+Query(v,l);
			Ans=Ans+C2(n-siz[nxtu]-siz[nxtv]);
			Ans=Ans-ssiz[l]+C2(siz[nxtu])+C2(siz[nxtv])-C2(n-siz[l]);
			Ans=Ans+C2(siz[u])+C2(siz[v])-ssiz[u]-ssiz[v];
			printf("%lld\n",Ans+dep[u]+dep[v]-2*dep[l]+1);
		}
	}
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
