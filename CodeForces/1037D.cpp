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

const int MAXN=2E5+10;

bool vis[MAXN];
int n,bfn[MAXN],bfn2[MAXN],tot,rt;
vector<int> g[MAXN];

void bfs(int S)
{
	queue<int> q;
	q.push(S);vis[S]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		bfn2[x]=++tot;
		sort(g[x].begin(),g[x].end(),[](int a,int b)->bool{return bfn[a]<bfn[b];});
		for(int v:g[x])
			if(!vis[v])
				q.push(v),vis[v]=1;
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(i==1) rt=x;
		bfn[x]=i;
	}
	bfs(1);
	for(int i=1;i<=n;i++)
		if(bfn[i]!=bfn2[i])
			return puts("No"),0;
	puts("Yes");
}