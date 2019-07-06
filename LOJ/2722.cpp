#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

typedef pair<int,int> pii;
typedef pair<int,ll> pil;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
	{
		x=0;static char ch=get_char();
		while(!isdigit(ch)) ch=get_char();
		while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
	}

#if __cplusplus >= 201103L
	template<typename T,typename ...Args>
		inline void read(T& x,Args& ...args)
	{
		read(x);
		read(args...);
	}
#endif
}

using namespace FastIO;

const int MAXN=50010;
const ll INFLL=1ll<<60;

template<typename T>
	void chkmx(T &x,T y){if(x<y) x=y;}

int n,m;
int st[18][MAXN<<1],lca[18][MAXN<<1],dft,pos[MAXN],dep[MAXN],lg2[MAXN<<1];
ll dis[MAXN],Ans=-INFLL;
vector<pair<int,int> > T[MAXN];

void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	st[0][pos[x]=++dft]=dep[x];
	lca[0][dft]=x;
	for(auto e:T[x])
		if(e.first!=fa)
		{
			dis[e.first]=dis[x]+e.second;
			dfs(e.first,x);
			st[0][++dft]=dep[x];
			lca[0][dft]=x;
		}
	reverse(T[x].begin(),T[x].end());
}

int LCA(int x,int y)
{
	x=pos[x];y=pos[y];
	if(x>y)
		swap(x,y);
	int len=lg2[y-x+1];
	return st[len][x]<st[len][y-(1<<len)+1]?lca[len][x]:lca[len][y-(1<<len)+1];
}

ll Dis(int x,int y){return dis[x]+dis[y]-2*dis[LCA(x,y)];}

ll Dis_w(pil x,pil y)
{
	if(!x.first&&!y.first)
		return -(INFLL<<1);
	if(!x.first||!y.first)
		return -INFLL;
	return Dis(x.first,y.first)+x.second+y.second;
}

namespace S1{
	struct node_t{
		int l,r;
		ll w1,w2;

		node_t(){l=r=0;w1=w2=-INFLL;}
	}t[MAXN*50];

	int cnt,rt[MAXN];
	vector<pair<int,ll>> V[MAXN];

	void pushup(int x)
	{
		t[x].w1=t[x].w2=-INFLL;
		if(t[x].l)
			chkmx(t[x].w1,t[t[x].l].w1),
			chkmx(t[x].w2,t[t[x].l].w2);
		if(t[x].r)
			chkmx(t[x].w1,t[t[x].r].w1),
			chkmx(t[x].w2,t[t[x].r].w2);
	}

	void insert(int &x,int l,int r,int p,ll w1,ll w2,ll dlt)
	{
		if(!x)
			x=++cnt;
		if(l==r)
			return chkmx(t[x].w1,w1),chkmx(t[x].w2,w2),void();
		int mid=(l+r)>>1;
		if(p<=mid)
			chkmx(Ans,w1+t[t[x].r].w2+dlt),insert(t[x].l,l,mid,p,w1,w2,dlt);
		else
			chkmx(Ans,t[t[x].l].w1+w2+dlt),insert(t[x].r,mid+1,r,p,w1,w2,dlt);
		pushup(x);
	}

	void erase(int x,int l,int r,int p)
	{
		if(!x)
			return;
		if(l==r)
			return t[x].w1=t[x].w2=-INFLL,void();
		int mid=(l+r)>>1;
		if(p<=mid)
			erase(t[x].l,l,mid,p);
		else
			erase(t[x].r,mid+1,r,p);
		pushup(x);
	}

	int merge(int x,int y,ll dlt)
	{
		if(!x||!y)
			return x|y;
		chkmx(Ans,max(t[t[x].l].w1+t[t[y].r].w2,t[t[y].l].w1+t[t[x].r].w2)+dlt);
		t[x].l=merge(t[x].l,t[y].l,dlt);
		t[x].r=merge(t[x].r,t[y].r,dlt);
		chkmx(t[x].w1,t[y].w1);
		chkmx(t[x].w2,t[y].w2);
		return x;
	}

	void dfs(int x,int fa)
	{
		for(auto pr:V[x])
			insert(rt[x],0,n,dep[pr.first],pr.second,pr.second+dis[pr.first],-dis[x]);
		for(auto e:T[x])
			if(e.first!=fa)
			{
				dfs(e.first,x);
				erase(rt[e.first],0,n,dep[x]);
				rt[x]=merge(rt[x],rt[e.first],-dis[x]);
			}
	}

	void clear()
	{
		for(int x=1;x<=cnt;x++)
			t[x].l=t[x].r=0,
			t[x].w1=t[x].w2=-INFLL;
		cnt=0;
		for(int i=1;i<=n;i++)
			V[i].clear(),rt[i]=0;
	}
}

namespace S2{
	struct node_t{
		int l,r;
		pair<pil,pil> w;
	}t[MAXN*50];

	vector<pair<int,pil>> V[MAXN];

	pair<pil,pil> merge(pair<pil,pil> x,pair<pil,pil> y,ll dlt)
	{
		chkmx(Ans,(Dis_w(x.first,y.first)+dlt)>>1);
		chkmx(Ans,(Dis_w(x.first,y.second)+dlt)>>1);
		chkmx(Ans,(Dis_w(x.second,y.first)+dlt)>>1);
		chkmx(Ans,(Dis_w(x.second,y.second)+dlt)>>1);
		auto ret=Dis_w(x.first,x.second)<Dis_w(y.first,y.second)?y:x;
		ll res=Dis_w(ret.first,ret.second),tmp;
		if(res<(tmp=Dis_w(x.first,y.first)))
			ret=make_pair(x.first,y.first),res=tmp;
		if(res<(tmp=Dis_w(x.first,y.second)))
			ret=make_pair(x.first,y.second),res=tmp;
		if(res<(tmp=Dis_w(x.second,y.first)))
			ret=make_pair(x.second,y.first),res=tmp;
		if(res<(tmp=Dis_w(x.second,y.second)))
			ret=make_pair(x.second,y.second),res=tmp;
		return ret;
	}
	
	int rt[MAXN],cnt;

	void insert(int &x,int l,int r,int p,pil w,ll dlt)
	{
		if(!x)
			x=++cnt;
		if(l==r)
			return t[x].w=merge(t[x].w,make_pair(w,w),dlt),void();
		int mid=(l+r)>>1;
		if(p<=mid)
			insert(t[x].l,l,mid,p,w,dlt);
		else
			insert(t[x].r,mid+1,r,p,w,dlt);
	}

	void erase(int x,int l,int r,int p)
	{
		if(!x)
			return;
		if(l==r)
			return t[x].w={{0,0},{0,0}},void();
		int mid=(l+r)>>1;
		if(p<=mid)
			erase(t[x].l,l,mid,p);
		else
			erase(t[x].r,mid+1,r,p);
	}

	int merge(int x,int y,int l,int r,ll dlt,int pos)
	{
		if(!x||!y)
			return x|y;
		if(l==r&&l!=pos)
			t[x].w=merge(t[x].w,t[y].w,dlt);
		int mid=(l+r)>>1;
		t[x].l=merge(t[x].l,t[y].l,l,mid,dlt,pos);
		t[x].r=merge(t[x].r,t[y].r,mid+1,r,dlt,pos);
		return x;
	}

	void dfs(int x,int fa)
	{
		for(auto pr:V[x])
			insert(rt[x],1,n,pr.first,pr.second,-2*dis[x]);
		for(auto e:T[x])
			if(e.first!=fa)
				dfs(e.first,x),
				rt[x]=merge(rt[x],rt[e.first],1,n,-2*dis[x],x);
		erase(rt[x],1,n,x);
	}

	void clear()
	{
		for(int i=1;i<=cnt;i++)
			t[i].l=t[i].r=0,
			t[i].w={{0,0},{0,0}};
		for(int i=1;i<=n;i++)
			rt[i]=0,V[i].clear();
		cnt=0;
	}
}

void solve()
{
	read(n);
	for(int i=1,u,v,w;i<n;i++)
		read(u,v,w),
		T[u].emplace_back(v,w),
		T[v].emplace_back(u,w);
	dfs(1,0);
	for(int i=2;i<=dft;i++)
		lg2[i]=lg2[i>>1]+1;
	for(int j=1;j<=lg2[dft];j++)
		for(int i=1;i+(1<<j)-1<=dft;i++)
			if(st[j-1][i]<st[j-1][i+(1<<(j-1))])
				st[j][i]=st[j-1][i],lca[j][i]=lca[j-1][i];
			else
				st[j][i]=st[j-1][i+(1<<(j-1))],lca[j][i]=lca[j-1][i+(1<<(j-1))];
	read(m);ll w,_w;
	for(int i=1,u,v;i<=m;i++)
	{
		read(u,v,_w);
		if(u==v)
			continue;
		int L=LCA(u,v);
		w=dis[u]+dis[v]-2*dis[L]-_w;
		if(u!=L)
			S1::V[u].emplace_back(L,w),
			S2::V[u].emplace_back(L,make_pair(v,w+dis[u]-_w));
		if(v!=L)
			S1::V[v].emplace_back(L,w),
			S2::V[v].emplace_back(L,make_pair(u,w+dis[v]-_w));
	}
	S1::dfs(1,0);S2::dfs(1,0);
	if(Ans<=-1E17)
		puts("F");
	else
		printf("%lld\n",Ans);
	for(int i=1;i<=n;i++)
		T[i].clear();
	dft=0;Ans=-INFLL;
	S1::clear();S2::clear();
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
