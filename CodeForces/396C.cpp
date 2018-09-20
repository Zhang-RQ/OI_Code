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

const int MAXN=3E5+10;
const int P=1E9+7;

int t[3][MAXN<<1],pos1[MAXN],pos2[MAXN],cnt,dep[MAXN],n,q;
vector<int> g[MAXN];

void add(int tp,int x,int val)
{
	val=(val%P+P)%P;
	for(;x<=cnt;x+=x&(-x))
		(t[tp][x]+=val)%=P;
}

int ask(int tp,int x)
{
	int ret=0;
	for(;x;x-=x&(-x))
		(ret+=t[tp][x])%=P;
	return ret;
}

void change(int tp,int x,int val){add(tp,pos1[x],val);add(tp,pos2[x],-val);}

void dfs(int x,int fa)
{
	pos1[x]=++cnt;
	dep[x]=dep[fa]+1;
	for(int v:g[x])
		dfs(v,x);
	pos2[x]=++cnt;
}

int main()
{
	scanf("%d",&n);
	for(int i=2,p;i<=n;i++)
		scanf("%d",&p),g[p].push_back(i);
	dfs(1,0);
	scanf("%d",&q);
	for(int i=1,op,v,x,k;i<=q;i++)
	{
		scanf("%d",&op);
		if(op==1) scanf("%d%d%d",&v,&x,&k),change(0,v,x),change(1,v,k),change(2,v,1ll*dep[v]*k%P);
		else scanf("%d",&v),printf("%lld\n",((ask(0,pos1[v])-1ll*dep[v]*ask(1,pos1[v])%P+ask(2,pos1[v]))%P+P)%P);
	}
}