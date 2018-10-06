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

int n,m;
int fa[MAXN],dep[MAXN],d[MAXN],lstans,cnt,ta[MAXN];

int find(int x){return fa[x]==x?x:find(fa[x]);}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i,dep[i]=1;
	for(int i=1,opt,u,v;i<=m;i++)
	{
		scanf("%d%d%d",&opt,&u,&v);
		u^=lstans;v^=lstans;
		if(opt==0)
		{
			u=find(u);v=find(v);++cnt;
			if(u!=v)
			{
				if(dep[u]<dep[v]) swap(u,v);
				fa[v]=u;d[v]=cnt;
				if(dep[u]==dep[v]) dep[u]++;
			}
		}
		else
		{
			if(find(u)!=find(v)) printf("%d\n",lstans=0);
			else
			{
				int l=find(u),Ans=0,x=u,y=v;
				while(x!=l) ta[x]=i,x=fa[x];
				while(y!=l&&ta[y]!=i) y=fa[y];
				if(ta[y]!=i) y=l;
				while(u!=y) Ans=max(Ans,d[u]),u=fa[u];
				while(v!=y) Ans=max(Ans,d[v]),v=fa[v];
				printf("%d\n",lstans=Ans);
			}
		}
	}
}