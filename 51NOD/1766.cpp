#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

vector<pair<int,int> > T[MAXN];
int st[MAXN<<1][19],lca[MAXN][19],dfn[MAXN],lg2[MAXN],dft,dis[MAXN],n,m;
pair<int,int> t[MAXN<<2];

int LCA(int x,int y)
{
	x=dfn[x],y=dfn[y];
	if(x>y)
		swap(x,y);
	int len=lg2[y-x+1];
	return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
}

int Dis(int x,int y)
{
	return dis[x]+dis[y]-2*dis[LCA(x,y)];
}

void dfs(int x,int fa)
{
	st[dfn[x]=++dft][0]=st[dfn[fa]][0]+1;
	lca[dfn[x]][0]=x;
	for(auto e:T[x])
		if(e.first!=fa)
		{
			dis[e.first]=dis[x]+e.second;
			dfs(e.first,x);
			st[++dft][0]=st[dfn[x]][0];
			lca[dft][0]=x;
		}
}

pair<int,int> merge(const pair<int,int> &a,const pair<int,int> &b)
{
	pair<int,int> ret=a;
	if(Dis(b.first,b.second)>Dis(ret.first,ret.second))
		ret=b;
	if(Dis(a.first,b.first)>Dis(ret.first,ret.second))
		ret=make_pair(a.first,b.first);
	if(Dis(a.second,b.second)>Dis(ret.first,ret.second))
		ret=make_pair(a.second,b.second);
	if(Dis(a.first,b.second)>Dis(ret.first,ret.second))
		ret=make_pair(a.first,b.second);
	if(Dis(a.second,b.first)>Dis(ret.first,ret.second))
		ret=make_pair(a.second,b.first);
	return ret;
}

void build(int x,int l,int r)
{
	if(l==r)
		return t[x]=make_pair(l,l),void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x]=merge(t[x<<1],t[x<<1|1]);
}

pair<int,int> query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)
		return t[x];
	int mid=(l+r)>>1;
	if(qr<=mid)
		return query(x<<1,l,mid,ql,qr);
	else if(ql>mid)
		return query(x<<1|1,mid+1,r,ql,qr);
	else
		return merge(query(x<<1,l,mid,ql,qr),query(x<<1|1,mid+1,r,ql,qr));
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++)
		scanf("%d%d%d",&u,&v,&w),
		T[u].emplace_back(v,w),
		T[v].emplace_back(u,w);
	dfs(1,0);
	for(int i=2;i<=dft;i++)
		lg2[i]=lg2[i>>1]+1;
	for(int j=1;j<=lg2[dft];j++)
		for(int i=1;i<=dft;i++)
			if(st[i][j-1]<st[i+(1<<(j-1))][j-1])
				st[i][j]=st[i][j-1],
				lca[i][j]=lca[i][j-1];
			else
				st[i][j]=st[i+(1<<(j-1))][j-1],
				lca[i][j]=lca[i+(1<<(j-1))][j-1];
	build(1,1,n);
	scanf("%d",&m);
	for(int i=1,a,b,c,d;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		pair<int,int> x=query(1,1,n,a,b),y=query(1,1,n,c,d);
		printf("%d\n",max(max(Dis(x.first,y.second),Dis(x.second,y.first)),max(Dis(x.first,y.first),Dis(x.second,y.second))));
	}
}
