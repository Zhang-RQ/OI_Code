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

const int MAXN=1E5+10;

int n,siz[MAXN],rt,mx_rt;
ll Ans;
bool vis[MAXN];
vector<int> g[MAXN];

struct Segment_Tree{

	int t[MAXN<<2];

	void change(int x,int l,int r,int pos,int val)
	{
		if(l==r) return t[x]+=val,void();
		int mid=(l+r)>>1;
		if(pos<=mid) change(x<<1,l,mid,pos,val);
		else change(x<<1|1,mid+1,r,pos,val);
		t[x]=t[x<<1]+t[x<<1|1];
	}

	int query(int x,int l,int r,int ql,int qr)
	{
		if(l>r) return 0;
		if(ql<=l&&r<=qr) return t[x];
		int mid=(l+r)>>1,ret=0;
		if(ql<=mid) ret+=query(x<<1,l,mid,ql,qr);
		if(qr>mid) ret+=query(x<<1|1,mid+1,r,ql,qr);
		return ret;
	}

}t1,t2;//t1 x,t2 mn

void get_rt(int x,int fa,int sz)
{
	int mx=siz[x]=1;
	for(int v:g[x])
		if(!vis[v]&&v!=fa)
			get_rt(v,x,sz),siz[x]+=siz[v],mx=max(mx,siz[v]);
	mx=max(mx,sz-siz[x]);
	if(mx<mx_rt)
		mx_rt=mx,rt=x;
}

void dfs1(int x,int fa,int mn,int mx,int f)
{
	if(x>mx) t1.change(1,1,n,x,f);
	if(mn>x) t2.change(1,1,n,mn,f);
	for(int v:g[x])
		if(!vis[v]&&v!=fa)
			dfs1(v,x,min(mn,x),max(mx,x),f);
}

void dfs2(int x,int fa,int mn,int mx)
{
	if(mx<=x) Ans+=t1.query(1,1,n,mx,x);
	if(mn>x) Ans+=t2.query(1,1,n,x,n);
	for(int v:g[x])
		if(!vis[v]&&v!=fa)
			dfs2(v,x,min(mn,x),max(mx,x));
}

void dfs3(int x,int fa,int mn,int mx,int rtv)
{
	if(x>rtv&&((mx<rtv)||(mn>x))) ++Ans; 
	if(x<rtv&&((mx<x)||(mn>rtv))) ++Ans;
	for(int v:g[x])
		if(!vis[v]&&v!=fa)
			dfs3(v,x,min(mn,x),max(mx,x),rtv);
}

void solve(int x)
{
	vis[x]=1;
	for(int v:g[x])
		if(!vis[v])
			for(int p:g[v])
				if(!vis[p]&&p!=x)
					dfs3(p,v,v,v,x);
	for(int v:g[x])
		if(!vis[v])
		{
			dfs2(v,x,x,x);
			dfs1(v,x,x,x,1);
		}
	for(int v:g[x])
		if(!vis[v])
			dfs1(v,x,x,x,-1);
	reverse(g[x].begin(),g[x].end());
	for(int v:g[x])
		if(!vis[v])
		{
			dfs2(v,x,x,x);
			dfs1(v,x,x,x,1);
		}
	for(int v:g[x])
		if(!vis[v])
			dfs1(v,x,x,x,-1);
	for(int v:g[x])
		if(!vis[v])
		{
			mx_rt=1<<30;
			get_rt(v,x,siz[v]);
			solve(rt);
		}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++) scanf("%d%d%*d",&u,&v),g[u].push_back(v),g[v].push_back(u);
	mx_rt=1<<30;
	get_rt(1,0,n);
	solve(rt);
	printf("%lld\n",1ll*n*(n-1)/2-Ans-n+1);
}