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

const int MAXN=15;

int n,h[MAXN],a,b,Ans=1<<30;

void dfs(int x,int tot)
{
	if(tot>Ans) return;
	if(x>=n)
	{
		bool f=1;
		for(int i=1;i<=n;i++) f&=h[i]<0;
		if(f) Ans=min(Ans,tot);
		return;
	}
	for(int i=0;1;i++)
	{
		h[x]-=a*i;
		h[x-1]-=b*i;
		h[x+1]-=b*i;
		if(tot+i>Ans) 
		{
			h[x]+=a*i;
			h[x-1]+=b*i;
			h[x+1]+=b*i;
			break;
		}
		if(h[x-1]<0) dfs(x+1,tot+i);
		h[x]+=a*i;
		h[x-1]+=b*i;
		h[x+1]+=b*i;
	}
}

int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++) scanf("%d",&h[i]);
	dfs(2,0);
	printf("%d\n",Ans);
}