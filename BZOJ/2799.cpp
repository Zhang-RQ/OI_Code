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
const int MAXM=2E6+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

bool vis[MAXN];
int head[MAXN],cnt_e,n,v[MAXN],lim[MAXN],tot,rt;
pair<int,int> Res[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int mx)
{
	if(v[x]) mx=v[x];
	else Res[++tot]=make_pair(mx,x);
	for(int i=head[x];i;i=Edge[i].nxt)
		dfs(Edge[i].v,lim[mx-1]);
}

int main()
{
	scanf("%d",&n);
	for(int i=1,p;i<=n;i++)
	{
		scanf("%d%d",&p,&v[i]);
		vis[v[i]]=1;
		if(p==i) rt=i;
		else add(p,i);
	}
	for(int i=1;i<=n;i++)
		if(vis[i]) lim[i]=lim[i-1];
		else lim[i]=i;
	v[rt]=n;dfs(rt,0);
	sort(Res+1,Res+1+tot);
	for(int i=1,ptr=0,cnt1=0,cnt2=0;i<=n;i++)
		if(!vis[i])
		{
			while(ptr<tot&&Res[ptr+1].first<=i) ++ptr,++cnt2;
			++cnt1;
			if(cnt1==cnt2)
			{
				if(cnt1==1) v[Res[ptr].second]=i;
				cnt1=cnt2=0;
			}
		}
	for(int i=1;i<=n;i++)
		printf("%d\n",v[i]);
}