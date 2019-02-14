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

const int MAXN=2510;

bool vis[MAXN];
int n,a[MAXN][MAXN],d[MAXN],frm[MAXN];
vector<pair<int,int> > g[MAXN];

void dfs(int x,int fa,int val,int rt)
{
	if(a[rt][x]!=val) throw -1;
	for(auto e:g[x])
		if(e.first!=fa)
			dfs(e.first,x,max(val,e.second),rt);
}

void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			if(a[i][j]!=a[j][i])
				throw -1;
	for(int i=1;i<=n;i++)
		if(a[i][i])
			throw -1;
	memset(d,0x3f,sizeof d);
	d[1]=0;
	for(int i=1;i<=n;i++)
	{
		int pos=0;
		for(int j=1;j<=n;j++)
			if(!vis[j]&&d[pos]>d[j]) pos=j;
		if(i!=1) g[pos].emplace_back(frm[pos],a[frm[pos]][pos]),g[frm[pos]].emplace_back(pos,a[frm[pos]][pos]);
		vis[pos]=1;
		for(int j=1;j<=n;j++)
			if(!vis[j]&&d[j]>a[pos][j])
				frm[j]=pos,d[j]=a[pos][j]; 
	}
	for(int i=1;i<=n;i++)
		dfs(i,0,0,i);
}

int main()
{
	try{
		solve();
	}catch(int e){
		puts("NOT MAGIC");
		return 0;
	}
	puts("MAGIC");
}