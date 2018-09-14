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

const int MAXN=4E4+10;

int pri[MAXN],cnt,k,m,tot;
bool vis[MAXN];
vector<int> Ans;

void sieve()
{
	for(int i=2;i<MAXN;i++)
	{
		if(!vis[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<MAXN;j++)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]==0) break;
		}
	}
}

bool isp(int x)
{
	if(x<MAXN) return !vis[x];
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return 0;
	return 1;
}

void dfs(int x,ll now,ll rst)
{
	if(rst==1) return Ans.push_back(now);
	if(rst-1>pri[cnt]&&isp(rst-1)) Ans.push_back(now*(rst-1));
	if(rst<pri[x]) return;
	ll sum=1,p=1;
	for(int y=x;1ll*pri[y]<=rst&&y<cnt;y++)
		for(sum=1+pri[y],p=pri[y];sum<=rst;p*=pri[y],sum+=p)
			if(!(rst%sum))
				dfs(y+1,now*p,rst/sum);
}

bool solve()
{
	if(scanf("%d",&m)==EOF) return 0;
	Ans.clear();
	dfs(1,1,m);sort(Ans.begin(),Ans.end());
	printf("%d\n",Ans.size());
	for(int i=0;i<Ans.size();i++)
		printf("%d%c",Ans[i],i==Ans.size()-1?'\n':' ');
	return 1;
}

int main()
{
	sieve();
	while(solve());
}