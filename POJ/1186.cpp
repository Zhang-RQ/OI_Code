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

int n,m,k[10],p[10];
ll Ans;

namespace Hash_table{
	const int P=5767169;
	const int MAXT=P+23333;
	int head[P];
	int nxt[MAXT],cnt;
	ll key[MAXT],val[MAXT];
	void change(ll S,ll V)
	{
		int idx=(S%P+P)%P;
		bool f=0;
		for(int i=head[idx];i;i=nxt[i])
			if(key[i]==S) {f=1;val[i]+=V;break;}
		if(!f)
		{
			++cnt;
			key[cnt]=S;val[cnt]=V;
			nxt[cnt]=head[idx];
			head[idx]=cnt;
		}
	}
	ll ask(ll S)
	{
		int idx=(S%P+P)%P;
		for(int i=head[idx];i;i=nxt[i])
			if(key[i]==S)
				return val[i];
		return 0;
	}
}


inline ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,a*=a) if(b&1) ret*=a;
	return ret;
}

int cnt=0;

void dfs(int now,int lim,ll res,bool tp)
{
	if(now>lim)
	{
		if(tp) Ans+=Hash_table::ask(-res);
		else Hash_table::change(res,1);
		return;
	}
	for(int i=1;i<=m;i++)
		dfs(now+1,lim,res+1ll*k[now]*ksm(i,p[now]),tp);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&k[i],&p[i]);
	int mid=n>>1;
	dfs(1,mid,0,0);dfs(mid+1,n,0,1);
	printf("%lld\n",Ans);
}