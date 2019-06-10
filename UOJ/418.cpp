#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

struct node{
	int l,r;
	ll mx,sum;
}t[MAXN*50];

struct dat{
	int id;
	ll x,y;//dlt,history dlt

	bool operator < (const dat &rhs) const
	{
		if((x<0)^(rhs.x<0))
			return x<rhs.x;
		if(x<0)
			return y==rhs.y?id<rhs.id:y<rhs.y;
		else
			return y-x==rhs.y-rhs.x?id<rhs.id:y-x>rhs.y-rhs.x;
	}

	friend dat merge(const dat &lhs,const dat &rhs)
	{
		return (dat){rhs.id,lhs.x+rhs.x,max(lhs.y,lhs.x+rhs.y)};
	}
}A[MAXN];

set<dat> S;
int n,w[MAXN],pos[MAXN],fa[MAXN],tot,cnt,rt[MAXN],f[MAXN],head[MAXN],nxt[MAXN];
ll Sum[MAXN],Ans[MAXN];
vector<int> T[MAXN];

int find(int x){return x==f[x]?x:f[x]=find(f[x]);}

void pushup(int x)
{
	t[x].sum=t[t[x].l].sum+t[t[x].r].sum;
	t[x].mx=max(t[t[x].l].mx,t[t[x].l].sum+t[t[x].r].mx);
}

void change(int &x,int l,int r,int pos,ll val)
{
	if(!x)
		x=++cnt;
	if(l==r)
		return t[x].sum=t[x].mx=val,void();
	int mid=(l+r)>>1;
	if(pos<=mid)
		change(t[x].l,l,mid,pos,val);
	else
		change(t[x].r,mid+1,r,pos,val);
	pushup(x);
}

int merge(int x,int y,int l,int r)
{
	if(!x||!y)
		return x|y;
	if(l==r)
		return t[x].sum=t[x].sum+t[y].sum,t[x].mx=t[x].sum,x;
	int mid=(l+r)>>1;
	t[x].l=merge(t[x].l,t[y].l,l,mid);
	t[x].r=merge(t[x].r,t[y].r,mid+1,r);
	pushup(x);
	return x;
}

void dfs(int x)
{
	for(int v:T[x])
		dfs(v),
		rt[x]=merge(rt[x],rt[v],1,n<<1);
	change(rt[x],1,n<<1,(pos[x]<<1)-1,w[x]);
	change(rt[x],1,n<<1,pos[x]<<1,-Sum[x]);
	Ans[x]=t[rt[x]].mx;
}

int main()
{
	scanf("%*d");
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
		scanf("%d",&fa[i]),T[fa[i]].push_back(i);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]),Sum[fa[i]]+=w[i];
	for(int i=1;i<=n;i++)
		S.insert(A[i]=(dat){i,w[i]-Sum[i],w[i]}),f[i]=i,head[i]=i;
	while(!S.empty())
	{
		dat t=*S.rbegin();S.erase(t);
		int x=t.id,y=find(fa[t.id]);
		nxt[head[y]]=x;head[y]=head[x];f[x]=y;
		if(S.count(A[y]))
		{
			S.erase(A[y]);
			A[y]=merge(A[x],A[y]);
			S.insert(A[y]);
		}
	}
	for(int i=1,cur=n;i;i=nxt[i])
		pos[i]=cur--;
	dfs(1);
	for(int i=1;i<=n;i++)
		printf("%lld%c",Ans[i],"\n "[i!=n]);
}
