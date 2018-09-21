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

const int MAXN=5E5+10;

int n,t[MAXN],a[MAXN],v[MAXN],stk[MAXN],pre[MAXN],Ans[MAXN],q,top;
vector<int> ve[MAXN];
vector<pair<int,int> > g[MAXN];

void add(int x,int v)
{
	for(;x<=n;x+=x&(-x))
		t[x]+=v;
}

int ask(int x)
{
	if(!x) return 0;
	int ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),v[i]=a[i];
	sort(v+1,v+1+n);
	int cnt=unique(v+1,v+1+n)-v-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(v+1,v+1+cnt,a[i])-v;
	for(int i=1;i<=n;i++)
	{
		while(top&&a[stk[top]]>=a[i]) --top;
		pre[i]=stk[top];
		stk[++top]=i;
		ve[pre[i]].push_back(i);
	}
	for(int i=1,l,r;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		g[l].push_back({r,i});
	}
	for(int i=1;i<=n;i++)
	{
		for(int p:ve[i-1]) add(p,1);
		for(pair<int,int> Q:g[i])
			Ans[Q.second]=ask(Q.first)-ask(i-1);
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",Ans[i]);
}