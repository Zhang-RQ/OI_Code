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

const int MAXN=1E4+10;
const int MAXM=1E5+10;

int n,m,fa[MAXN],t[MAXN],mn=1<<30;
ll Ans;

struct E{int u,v,w;}Edge[MAXM];

bool operator < (const E &lhs,const E &rhs){return lhs.w<rhs.w;}

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&t[i]),fa[i]=i,mn=min(mn,t[i]);
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		Edge[i].u=x;Edge[i].v=y;
		Edge[i].w=2*z+t[x]+t[y];
	}
	sort(Edge+1,Edge+1+m);
	for(int i=1;i<=m;i++)
	{
		if(find(Edge[i].u)==find(Edge[i].v)) continue;
		fa[find(Edge[i].u)]=find(Edge[i].v);
		Ans+=Edge[i].w;
	}
	printf("%lld\n",Ans+mn);
}