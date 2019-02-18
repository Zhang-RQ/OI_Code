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

const int MAXN=1E6+10;

int n,m,rt[MAXN],dep[MAXN],cnt,lef[MAXN];
vector<pair<int,int> > lk[MAXN];
vector<int> g[MAXN],pre[MAXN],suf[MAXN];

struct node_t{
	pair<int,int> v;
	int l,r,h,add;
}t[MAXN];

void pushdown(int x)
{
	if(t[x].add)
	{
		t[t[x].l].v.first+=t[x].add;
		t[t[x].r].v.first+=t[x].add;
		t[t[x].l].add+=t[x].add;
		t[t[x].r].add+=t[x].add;
		t[x].add=0;
	}
}

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	pushdown(x);pushdown(y);
	if(t[x].v>t[y].v) swap(x,y);
	t[x].r=merge(t[x].r,y);
	if(t[t[x].l].h<t[t[x].r].h) swap(t[x].l,t[x].r);
	t[x].h=t[t[x].r].h+1;
	return x;
}

void dfs(int x)
{
	for(int v:g[x])
		dep[v]=dep[x]+1,dfs(v);
	pre[x].resize(g[x].size());
	suf[x].resize(g[x].size());
	for(int _=0;_<(int)g[x].size();_++)
	{
		int v=g[x][_];
		while(t[rt[v]].v.second>dep[x]+1) rt[v]=merge(t[rt[v]].l,t[rt[v]].r);
		pre[x][_]=(_?pre[x][_-1]:0)+t[rt[v]].v.first;
	}
	for(int _=g[x].size()-1;~_;--_)
	{
		int v=g[x][_];
		suf[x][_]=(_!=(int)g[x].size()-1?suf[x][_+1]:0)+t[rt[v]].v.first;
	}
	for(int _=0;_<(int)g[x].size();_++)
	{
		int v=g[x][_];
		t[rt[v]].add+=(_?pre[x][_-1]:0)+(_!=(int)g[x].size()-1?suf[x][_+1]:0);
		t[rt[v]].v.first+=(_?pre[x][_-1]:0)+(_!=(int)g[x].size()-1?suf[x][_+1]:0);
		rt[x]=merge(rt[x],rt[v]);
	}
	for(auto p:lk[x])
		t[++cnt].v=make_pair(p.first+(suf[x].size()?suf[x][0]:0),dep[p.second]),
		rt[x]=merge(rt[x],cnt);
	if(!rt[x]) throw -1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=2,fa;i<=n;i++) scanf("%d",&fa),g[fa].push_back(i);
	for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),lk[v].emplace_back(w,u);
	try{
		dfs(1);
	}catch(int error){
		puts("-1");
		return 0;
	}
	printf("%d\n",t[rt[1]].v.first);
}