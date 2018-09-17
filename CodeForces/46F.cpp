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

const int MAXN=1E3+10;
const int base=23336;

struct DSU{

	int fa[MAXN<<1];

	vector<int> v[MAXN],g[MAXN];

	void init(int n){for(int i=1;i<=n;i++) fa[i]=i;}

	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

	inline bool check(int x,int y){return find(x)==find(y);}

	inline void merge(int x,int y)
	{
		x=find(x);y=find(y);
		if(x==y) return;
		fa[x]=y;
	}	
}d[2];

bool vis[MAXN];
char str[MAXN];
int n,m,k,u[MAXN],v[MAXN],bl[2][MAXN];
map<ull,int> mp;

ull hsh(char *s)
{
	ull ret=0;
	for(int i=1;s[i];i++) ret=ret*base+s[i];
	return ret;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++) scanf("%d%d",&u[i],&v[i]);
	for(int s=0;s<=1;s++)
	{
		d[s].init(n+m);
		for(int i=1,num,id;i<=k;i++)
		{
			scanf("%s",str+1);
			ull Hash=hsh(str);
			if(mp.find(Hash)==mp.end()) id=mp[Hash]=i;
			else id=mp[Hash];
			scanf("%d%d",&bl[s][id],&num);
			for(int j=1,x;j<=num;j++)
			{
				scanf("%d",&x);
				d[s].merge(x+n,bl[s][id]);
			}
		}
		for(int i=1;i<=m;i++)
			for(int j=1;j<=m;j++)
				if(d[s].check(j+n,u[j])||d[s].check(j+n,v[j]))
					d[s].merge(u[j],v[j]);
	}
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++)
			if(d[0].check(bl[0][i],j)^d[1].check(bl[1][i],j))
				return puts("NO"),0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(d[0].check(j+n,i)^d[1].check(j+n,i))
				return puts("NO"),0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(d[0].check(i,j)^d[1].check(i,j))
				return puts("NO"),0;
	puts("YES");
}