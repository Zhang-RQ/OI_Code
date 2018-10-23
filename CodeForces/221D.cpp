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

const int MAXN=1E5+10;

int n,m,pre[MAXN][18],a[MAXN];
int t[MAXN],Ans[MAXN];
map<int,int> mp;
vector<pair<int,int> > v[MAXN];

void C(int x,int v)
{
	for(;x<=n;x+=x&(-x))
		t[x]+=v;
}

int Q(int x)
{
	int ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

int Query(int p,int stp)
{
	for(int i=17;~i;i--)
		if(stp>=(1<<i))
			p=pre[p][i],stp-=1<<i;
	return p;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		pre[i][0]=mp[a[i]];
		mp[a[i]]=i;
	}
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
			pre[i][j]=pre[pre[i][j-1]][j-1];
	for(int i=1,l,r;i<=m;i++)
		scanf("%d%d",&l,&r),v[r].push_back(make_pair(l,i));
	for(int i=1;i<=n;i++)
	{
		int L=Query(i,a[i]+1),Mid=Query(i,a[i]),R=Query(i,a[i]-1);
		if(L<Mid) C(L+1,-1),C(Mid+1,1);
		if(Mid<R) C(Mid+1,1),C(R+1,-1);
		for(auto p:v[i])
			Ans[p.second]=Q(p.first);
	}
	for(int i=1;i<=m;i++) printf("%d\n",Ans[i]);
}