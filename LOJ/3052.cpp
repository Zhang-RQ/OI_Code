#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int n,M[MAXN],tmp[MAXN];
vector<int> T[MAXN];
multiset<int> S[MAXN];

void dfs(int x)
{
	for(int v:T[x])
	{
		dfs(v);
		if(S[x].size()<S[v].size())
			swap(S[x],S[v]);
		int tot=0;
		while(S[v].size())
			tmp[++tot]=max(*S[v].rbegin(),*S[x].rbegin()),
			S[x].erase(--S[x].end()),S[v].erase(--S[v].end());
		while(tot)
			S[x].insert(tmp[tot--]);
	}
	S[x].insert(M[x]);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&M[i]);
	for(int i=2,f;i<=n;i++)
		scanf("%d",&f),T[f].push_back(i);
	dfs(1);
	ll Ans=0;
	for(int v:S[1])
		Ans+=v;
	printf("%lld\n",Ans);
}
