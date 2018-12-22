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

const int MAXN=3E5+10;

int n;
int f[MAXN],Mid;
vector<int> g[MAXN];

void dfs(int x,int fa)
{
	f[x]=0;
	for(int v:g[x])
		if(v!=fa)
			dfs(v,x),f[x]+=f[v]+1;
	f[x]=max(f[x]-Mid,0);
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	int L=0,R=n,Ans=0;
	while(L<=R)
	{
		Mid=(L+R)>>1;
		dfs(1,0);
		if(f[1]==0) Ans=Mid,R=Mid-1;
		else L=Mid+1;
	}
	cout<<Ans<<endl;
}