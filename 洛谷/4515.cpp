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

int x[MAXN],y[MAXN],r[MAXN],n;
ll Ans=0;

void dfs(int now,int mn,int mx,int my,int tot)
{
	if(now>n) return Ans+=tot?1ll*(tot&1?1:-1)*(1<<(tot-1))*max((mn-mx-my),0)*(mn-mx-my):0,void();
	dfs(now+1,min(mn,x[now]+y[now]+r[now]),max(mx,x[now]),max(my,y[now]),tot+1);
	dfs(now+1,mn,mx,my,tot);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&x[i],&y[i],&r[i]);
	dfs(1,1<<30,0,0,0);
	printf("%.1lf\n",Ans/2.0);
}