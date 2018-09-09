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

int num[20],tot;
ll f[19][4],L,R;

ll dfs(int x,int cnt,bool lim)
{
	if(x==0) return cnt<=3;
	if(cnt>3) return 0;
	if((!lim)&&(~f[x][cnt])) return f[x][cnt];
	ll ret=0;int lm=lim?num[x]:9;
	for(int i=0;i<=lm;i++)
		ret+=dfs(x-1,cnt+(i!=0),lim&&i==lm);
	if(!lim) f[x][cnt]=ret;
	return ret;
}

ll Solve(ll X)
{
	tot=0;
	while(X) num[++tot]=X%10,X/=10;
	return dfs(tot,0,1);
}

void solve()
{
	scanf("%lld%lld",&L,&R);
	printf("%lld\n",Solve(R)-Solve(L-1));
}

int main()
{
	int T;
	memset(f,-1,sizeof f);
	for(scanf("%d",&T);T--;solve());
}