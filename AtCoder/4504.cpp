#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int n,Ans[MAXN],Mx[MAXN];
vector<int> T[MAXN];
map<int,int> M[MAXN];

int f(int x,int fa,int w)
{
	if(M[x].count(w))
		return M[x][w];
	int ret=0;
	for(int v:T[x])
		if(v!=fa&&v<=w)
			ret+=f(v,x,w)+1;
	return M[x][w]=ret;
}

void dfs(int x,int fa)
{
	Mx[x]=max(Mx[fa],fa);
	if(x>Mx[fa])
		Ans[x]=Ans[fa]+f(x,fa,Mx[x])+1;
	else
		Ans[x]=Ans[fa]-f(x,fa,Mx[fa])+f(x,fa,Mx[x]);
	if(x==1)
		Ans[x]=0;
	for(int v:T[x])
		if(v!=fa)
			dfs(v,x);
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		T[u].push_back(v),
		T[v].push_back(u);
	dfs(1,0);
	for(int i=2;i<=n;i++)
		printf("%d%c",Ans[i],"\n "[i!=n]);
}
