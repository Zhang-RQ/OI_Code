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

const int MAXN=20010;
const int MAXM=1E5+10;

struct edge{
	int u,v,w;
	bool ban;
}E[MAXM];

vector<edge> Ans;

bool cmp1(const edge &lhs,const edge &rhs) {return lhs.w>rhs.w;}
bool cmp2(const edge &lhs,const edge &rhs) {return lhs.w<rhs.w;}

int n,m,k,fa[MAXN],cnt;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

bool check()
{
	int Rt=find(1);
	for(int i=1;i<=n;i++)
		if(find(i)!=Rt)
			return false;
	return true;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	for(int i=1;i<=n;i++) fa[i]=i;
	sort(E+1,E+1+m,cmp1);
	for(int i=1;i<=m;i++)
	{
		int U=find(E[i].u),V=find(E[i].v);
		if(U!=V)
		{
			fa[U]=V;
			cnt+=!E[i].w;
			if(!E[i].w) E[i].ban=1,Ans.push_back(E[i]);
		}
	}
	if(cnt>k||!check()) return puts("no solution"),0;
	sort(E+1,E+1+m,cmp2);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=0;i<Ans.size();i++)
	{
		int U=find(Ans[i].u),V=find(Ans[i].v);
		fa[U]=V;
	}
	for(int i=1;i<=m;i++)
	{
		if(E[i].ban) continue;
		if(cnt==k&&E[i].w==0) continue;
		int U=find(E[i].u),V=find(E[i].v);
		if(U!=V)
		{
			fa[U]=V;
			cnt+=!E[i].w;
			Ans.push_back(E[i]);
		}
	}
	if(!check()||cnt<k) return puts("no solution"),0;
	for(int i=0;i<Ans.size();i++)
		printf("%d %d %d\n",Ans[i].u,Ans[i].v,Ans[i].w);
}