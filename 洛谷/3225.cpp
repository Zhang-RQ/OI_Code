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

const int MAXN=1010;

bool iscut[MAXN];
int n,stk[MAXN],top,tot,Cs;
int dfn[MAXN],low[MAXN],dft;
vector<int> G[MAXN],p[MAXN];

void tarjan(int x,int fa)
{
	int son=0;
	stk[++top]=x;
	dfn[x]=low[x]=++dft;
	for(int v:G[x])
		if(v!=fa)
		{
			if(dfn[v]) low[x]=min(low[x],dfn[v]);
			else
			{
				tarjan(v,x);++son;
				low[x]=min(low[x],low[v]);
				if(low[v]>=dfn[x])
				{
					iscut[x]=1;
					++tot;
					do{
						p[tot].push_back(stk[top]);
						--top;
					}while(stk[top+1]!=v);
					p[tot].push_back(x);
				}
			}
		}
	if(!fa) iscut[x]&=son>1;
}

bool solve()
{
	scanf("%d",&n);
	if(!n) return false;
	int mx=0;
	ll Ans1=0,Ans2=1;
	for(int i=1,u,v;i<=n;i++) scanf("%d%d",&u,&v),mx=max(mx,max(u,v)),G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<=mx;i++)
		if(!dfn[i]) tarjan(i,0);
	for(int i=1;i<=tot;i++)
	{
		int cnt=0;
		for(int x:p[i]) cnt+=iscut[x];
		if(cnt==0) Ans1+=2,Ans2*=(p[i].size()-1)*p[i].size()/2;
		else if(cnt==1) Ans1+=1,Ans2*=p[i].size()-1;
	}
	printf("Case %d: %lld %lld\n",++Cs,Ans1,Ans2);
	for(int i=1;i<=mx;i++) G[i].clear(),p[i].clear(),dfn[i]=iscut[i]=0;
	tot=dft=0;
	return true;
}

int main()
{
	while(solve());
}