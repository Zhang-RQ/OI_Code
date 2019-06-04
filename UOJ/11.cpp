#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int INF=1<<30;

int f[3][MAXN],g[MAXN],frm[3][MAXN];
int n,m,flg[MAXN],gs[MAXN],dlt[MAXN],jmp[18][MAXN],dep[MAXN],stf[MAXN],stg[MAXN];
vector<pair<int,int> > T[MAXN];

void dfs1(int x,int fa)
{
	jmp[0][x]=fa;dep[x]=dep[fa]+1;
	f[0][x]=f[1][x]=f[2][x]=-INF;
	if(flg[x])
		f[0][x]=0,stf[x]=x,frm[0][x]=x;
	for(auto e:T[x])
		if(e.first!=fa)
		{
			dfs1(e.first,x);
			int nf=f[0][e.first]+e.second,nf2=f[1][e.first]+e.second;
			if(nf>f[0][x])
				f[2][x]=f[1][x],frm[2][x]=frm[1][x],f[1][x]=f[0][x],frm[1][x]=frm[0][x],
				f[0][x]=nf,frm[0][x]=e.first,stf[x]=nf==nf2?e.first:stf[e.first];
			else if(nf>f[1][x])
				f[2][x]=f[1][x],frm[2][x]=frm[1][x],
				f[1][x]=nf,frm[1][x]=e.first;
			else if(nf>f[2][x])
				f[2][x]=nf,frm[2][x]=e.first;
		}
	if(f[0][x]==f[1][x])
		stf[x]=x;
}

void dfs2(int x,int fa,int fav)
{
	g[x]=-INF;
	if(flg[x])
		g[x]=0,stg[x]=x;
	if(fa)
	{
		int f0,f1,fm0;
		if(frm[0][fa]==x)
		{
			f0=f[1][fa];
			fm0=frm[1][fa];
			f1=f[2][fa];
		}
		else if(frm[1][fa]==x)
		{
			f0=f[0][fa];
			fm0=frm[0][fa];
			f1=f[2][fa];
		}
		else
		{
			f0=f[0][fa];
			fm0=frm[0][fa];
			f1=f[1][fa];
		}
		if(f0==g[fa])
			stg[x]=fa,g[x]=f0+fav;
		else if(f0<g[fa])
		{
			stg[x]=stg[fa];
			g[x]=g[fa]+fav;
		}
		else //f0>g[fa]
		{
			g[x]=f0+fav;
			stg[x]=f0==f1?fa:(fm0==fa?fa:stf[fm0]);
		}
	}
	for(auto e:T[x])
		if(e.first!=fa)
			dfs2(e.first,x,e.second);
}

void dfs3(int x,int fa)
{
	for(auto e:T[x])
		if(e.first!=fa)
			dfs3(e.first,x),
			dlt[x]+=dlt[e.first];
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(int j=17;~j;j--)
		if(dep[jmp[j][x]]>=dep[y])
			x=jmp[j][x];
	if(x==y)
		return x;
	for(int j=17;~j;j--)
		if(jmp[j][x]!=jmp[j][y])
			x=jmp[j][x],y=jmp[j][y];
	return jmp[0][x];
}

void Path_add(int u,int v)
{
	int z=LCA(u,v);
	dlt[u]++;dlt[v]++;
	dlt[z]--;dlt[jmp[0][z]]--;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=m;i++)
		scanf("%d",&x),flg[x]=1;
	for(int i=1,u,v,w;i<n;i++)
		scanf("%d%d%d",&u,&v,&w),
		T[u].emplace_back(v,w),
		T[v].emplace_back(u,w);
	dfs1(1,0);dfs2(1,0,0);
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
			jmp[j][i]=jmp[j-1][jmp[j-1][i]];
	for(int x=1;x<=n;x++)
	{
		if(!flg[x])
			continue;
		if(g[x]==f[0][x])
			continue;
		if(g[x]>f[0][x])
			Path_add(stg[x],x);
		if(g[x]<f[0][x]&&f[0][x]!=f[1][x])
			Path_add(stf[x],x);
	}
	dfs3(1,0);
	int Ans=0,cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(flg[i])
			continue;
		if(dlt[i]>Ans)
			Ans=dlt[i],cnt=1;
		else if(Ans==dlt[i])
			++cnt;
	}
	printf("%d %d\n",Ans,cnt);
}
