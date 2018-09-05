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

int n,q,pos[MAXN],siz[MAXN],dft,cnt,rt[MAXN],dep[MAXN],rev[MAXN];
vector<int> g[MAXN];

struct __node{
	int l,r,v;
	ll s;
}t[MAXN<<8];

void dfs(int x,int fa)
{
	pos[x]=++dft;siz[x]=1;
	dep[x]=dep[fa]+1;
	rev[pos[x]]=x;
	for(int v:g[x])
		if(v!=fa)
			dfs(v,x),siz[x]+=siz[v];
}

void insert(int &x,int l,int r,int pos,int val,int _x)
{
	x=++cnt;
	t[x]=t[_x];
	t[x].v++;t[x].s+=val;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) insert(t[x].l,l,mid,pos,val,t[_x].l);
	else insert(t[x].r,mid+1,r,pos,val,t[_x].r);
}

ll query_s(int x,int l,int r,int ql,int qr,int _x)
{
	if(ql<=l&&r<=qr) return t[x].s-t[_x].s;
	int mid=(l+r)>>1;ll ret=0;
	if(ql<=mid) ret+=query_s(t[x].l,l,mid,ql,qr,t[_x].l);
	if(qr>mid)  ret+=query_s(t[x].r,mid+1,r,ql,qr,t[_x].r);
	return ret;
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);ll Ans=0;
	for(int i=1;i<=n;i++) insert(rt[i],1,n,dep[rev[i]],siz[rev[i]]-1,rt[i-1]);
	for(int i=1,p,k;i<=q;i++)
	{
		Ans=0;
		scanf("%d%d",&p,&k);
		Ans+=1ll*(siz[p]-1)*min(dep[p]-1,k);
		Ans+=query_s(rt[pos[p]+siz[p]-1],1,n,max(1,min(dep[p]+1,n)),max(1,min(dep[p]+k,n)),rt[pos[p]-1]);
		printf("%lld\n",Ans);
	}
}