#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

int n;
vector<int> T[MAXN];

int dfs(int x,int fa)
{
	int ret=0,f=0;
	for(int v:T[x])
		if(v!=fa)
		{
			int t=dfs(v,x);
			if(!t)
			{
				if(!f) f=1;
				else ++ret;
			}
			else ret+=t;
		}
	return ret;
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		++u,++v,T[u].push_back(v),T[v].push_back(u);
	int rt=0;
	for(int i=1;i<=n;i++)
		if(T[i].size()>=3)
			rt=i;
	if(!rt)
		return puts("1"),0;
	printf("%d\n",dfs(rt,0));
}
