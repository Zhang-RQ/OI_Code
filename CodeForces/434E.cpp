#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

map<int,int> In,Out;
int n,k,X,P,a[MAXN],siz[MAXN],vis[MAXN],rt,mx_rt;
ll pw[MAXN],ipw[MAXN],in1[MAXN],out1[MAXN],tAns;
vector<int> T[MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll Sub(ll x,ll y) {x-=y;return x<=0?x+P:x;}

void get_rt(int x,int fa,int sz)
{
	int mx=0;
	siz[x]=1;
	for(int v:T[x])
		if(v!=fa&&!vis[v])
		{
			get_rt(v,x,sz);
			siz[x]+=siz[v];
			mx=max(mx,siz[v]);
		}
	mx=max(mx,sz-siz[x]);
	if(mx<mx_rt) rt=x,mx_rt=mx;
}

void dfs1(int x,int fa,ll val1,ll val2,int dep)
{
	val1=(val1*k%P+a[x])%P;
	val2=(val2+a[x]*pw[dep-2])%P;
	In[Sub(X,val1)*ipw[dep]%P]++;
	Out[val2]++;
	for(int v:T[x])
		if(v!=fa&&!vis[v])
			dfs1(v,x,val1,val2,dep+1);
}

void dfs2(int x,int fa,ll val1,ll val2,int dep)
{
	val1=(val1*k%P+a[x])%P;
	val2=(val2+a[x]*pw[dep-2])%P;
	in1[x]+=In[val2];
	out1[x]+=Out[Sub(X,val1)*ipw[dep]%P];
	for(int v:T[x])
		if(v!=fa&&!vis[v])
			dfs2(v,x,val1,val2,dep+1);
}

void solve(int x)
{
	vis[x]=1;
	In.clear();Out.clear();
	In[Sub(X,a[x])*ipw[1]%P]++;
	Out[0]++;
	for(int v:T[x])
		if(!vis[v])
			dfs2(v,x,a[x],0,2),
			dfs1(v,x,a[x],0,2);
	in1[x]+=In[0];
	out1[x]+=Out[Sub(X,a[x])*ipw[1]%P];
	reverse(T[x].begin(),T[x].end());
	In.clear();Out.clear();
	for(int v:T[x])
		if(!vis[v])
			dfs2(v,x,a[x],0,2),
			dfs1(v,x,a[x],0,2);
	for(int v:T[x])
		if(!vis[v])
		{
			mx_rt=1<<30;
			get_rt(v,x,siz[v]);
			solve(rt);
		}
}

int main()
{
	scanf("%d%d%d%d",&n,&P,&k,&X);
	pw[0]=ipw[0]=1;
	pw[1]=k;ipw[1]=ksm(k,P-2);
	for(int i=2;i<=n;i++)
		pw[i]=pw[i-1]*pw[1]%P,
		ipw[i]=ipw[i-1]*ipw[1]%P;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),a[i]%=P;
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),T[u].push_back(v),T[v].push_back(u);
	mx_rt=1<<30;
	get_rt(1,0,n);
	solve(rt);
	for(int i=1;i<=n;i++)
	{
		tAns+=in1[i]*(n-out1[i]);
		tAns+=(n-in1[i])*out1[i];
		tAns+=2*in1[i]*(n-in1[i]);
		tAns+=2*out1[i]*(n-out1[i]);
	}
	printf("%lld\n",1ll*n*n*n-tAns/2);
}
