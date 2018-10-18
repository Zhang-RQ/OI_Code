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

const int MAXN=60;
const int MAXM=120;
const int p[]={0,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317};

struct __edge{
	int v,nxt;
}Edge[MAXM];

bool vis[MAXN];
int head[MAXN],m,n,cnt_e;
int siz[MAXN],rt,mx_rt;
ull Hsh[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

ull dfs(int x,int fa)
{
	ull ret=19260817;
	vector<ull> vec;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		vec.push_back(dfs(v,x));
	}
	sort(vec.begin(),vec.end());
	for(int i=0;i<vec.size();i++)
		ret+=vec[i]*p[i+1];
	return ret;
}

int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&n);cnt_e=0;memset(head,0,sizeof head);
		for(int j=1,x;j<=n;j++)
		{
			scanf("%d",&x);
			if(x) add(j,x),add(x,j);
		}
		vector<ull> vec;
		for(int j=1;j<=n;j++)
			vec.push_back(dfs(j,0));
		sort(vec.begin(),vec.end());
		for(int j=0;j<vec.size();j++)
			Hsh[i]+=vec[j]*p[j+1];
	}
	for(int i=1,j=1;i<=m;i++)
	{
		j=1;
		for(j=1;j<=i;j++)
			if(Hsh[i]==Hsh[j])
				break;
		printf("%d\n",j);
	}
}