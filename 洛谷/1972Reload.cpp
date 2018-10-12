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

int n,m,t[MAXN];
int pre[MAXN],Ans[MAXN];
map<int,int> mp;

struct Query{
	int l,r,id;
	bool operator < (const Query &rhs) const {return r<rhs.r;}
}Q[MAXN];

void add(int x,int v)
{
	for(;x<=n;x+=x&(-x))
		t[x]+=v;
}

int ask(int x)
{
	int ret=0;
	for(;x;x-=x&(-x))
		ret+=t[x];
	return ret;
}

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		pre[i]=mp[x];mp[x]=i;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
	sort(Q+1,Q+1+m);
	for(int i=1,j=0;i<=m;i++)
	{
		while(j<Q[i].r)
			++j,add(pre[j]+1,1),add(j+1,-1);
		Ans[Q[i].id]=ask(Q[i].l);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",Ans[i]);
}