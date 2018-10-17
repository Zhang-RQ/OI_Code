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

const int MAXN=1E5+10;

int n,m,a[MAXN];
vector<int> g[MAXN],f[MAXN],glo;
bool vis[MAXN];
ll Ans;

void dfs(int x,int fa,vector<int> &ve)
{
	ve.push_back(a[x]);
	vis[x]=1;
	for(int v:g[x])
		if(v!=fa)
			dfs(v,x,ve);
}

int main()
{
	scanf("%d%d",&n,&m);
	if(m==n-1) return puts("0"),0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),++u,++v,g[u].push_back(v),g[v].push_back(u);
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			++cnt;
			dfs(i,0,f[i]);
			sort(f[i].begin(),f[i].end());
			Ans+=f[i][0];
			for(int j=1;j<f[i].size();j++)
				glo.push_back(f[i][j]);
		}
	if(((cnt-1)<<1)>n) return puts("Impossible"),0;
	sort(glo.begin(),glo.end());
	for(int i=0;i<cnt-2;i++)
		Ans+=glo[i];
	printf("%lld\n",Ans);
}