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
#include<ctime>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const double alpha=0.80;
const int o=4E6+10;
const int P=1E9;

int n,rebuid_count;
ll Ans;

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

namespace Treap2{
	int unused[o], top, pool;
	struct node
	{
	    int lc, rc, val, s, pos;
	}a[o];

	inline void reset(int &x, int v)
	{
	    a[x].lc = a[x].rc = 0;
	    a[x].val = v;
	    a[x].s = 1;
	    a[x].pos = rand();
	}

	inline void update(int &x)
	{
	    a[x].s = a[a[x].lc].s + a[a[x].rc].s + 1;
	}

	inline int new_node()
	{
	    int res;
	    if (top > 0)
	    {
	        res = unused[top]; //将用过的并且删过的点的编号放入 unused
	        top--;     //新建节点的时候可以再使用这些编号，可以省空间
	    }
	    else res = ++pool;
	    return res;
	}

	inline void del_node(int &u)
	{
	    if (!u) return;
	    unused[++top]=u;
	    a[u].val = a[u].s = a[u].pos = 0;
	    if (a[u].lc) del_node(a[u].lc);
	    if (a[u].rc) del_node(a[u].rc);
	    u = 0;
	}

	inline void zig(int &u)
	{
	    int v = a[u].lc;
	    a[u].lc = a[v].rc;
	    a[v].rc = u;
	    a[v].s = a[u].s;
	    update(u);
	    u = v;
	}

	inline void zag(int &u)
	{
	    int v = a[u].rc;
	    a[u].rc = a[v].lc;
	    a[v].lc = u;
	    a[v].s = a[u].s;
	    update(u);
	    u = v;
	}

	inline void insert(int &u,int v)
	{
	    if (!u)
	    {
	        u = new_node();
	        reset(u, v);
	        return;
	    }
	    a[u].s++;
	    if (v <= a[u].val)
	    {
	        insert(a[u].lc, v);
	        if (a[a[u].lc].pos < a[u].pos) zig(u);
	    }
	    else
	    {
	        insert(a[u].rc, v);
	        if (a[a[u].rc].pos < a[u].pos) zag(u);
	    }
	}
	inline int qrank(int u, int v)
	{
	    if (!u) return 0;
	    if (v < a[u].val) return qrank(a[u].lc, v);
	    else return a[a[u].lc].s + 1 + qrank(a[u].rc, v);
	}
}

namespace Treap{
	int son[MAXN<<6][2],siz[MAXN<<6],fix[MAXN<<6],val[MAXN<<6],cnt;
	int stk[MAXN],top;

	inline void clear(int &rt){if(rt) stk[++top]=rt,rt=0;}

	inline int nd()
	{
		int x;
		if(top)
		{
			x=stk[top];--top;
			if(son[x][0]) stk[++top]=son[x][0];
			if(son[x][1]) stk[++top]=son[x][1];
		}
		else x=++cnt;
		son[x][0]=son[x][1]=siz[x]=0;fix[x]=rand();
		return x;
	}

	inline void pushup(int x){siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;}

	int merge(int x,int y) // x < y (val)
	{
		if(!x||!y) return x|y;
		if(fix[x]<fix[y])
		{
			son[x][1]=merge(son[x][1],y),pushup(x);
			return x;
		}
		else 
		{
			son[y][0]=merge(x,son[y][0]),pushup(y);
			return y;
		}
	}

	void split2(int x,int v,int &a,int &b)
	{
		if(!x) return a=b=0,void();
		if(val[x]<=v) a=x,split2(son[x][1],v,son[x][1],b);
		else b=x,split2(son[x][0],v,a,son[x][0]);
		pushup(x);
	}

	inline void insert(int &rt,int v)
	{
		int pr,lt;
		split2(rt,v,pr,lt);
		int x=nd();siz[x]=1;val[x]=v;
		rt=merge(merge(pr,x),lt);
	}

	inline int query_less(int x,int v)
	{
		if(!x) return 0;
		if(val[x]<=v) return siz[son[x][0]]+1+query_less(son[x][1],v);
		else return query_less(son[x][0],v);
	}
}

namespace Tree{
	int Jmp[MAXN][18],r[MAXN],Dis[MAXN],dep[MAXN];
	vector<pair<int,int> > G[MAXN]; //原图

	inline int LCA(int x,int y)
	{
		if(dep[x]<dep[y]) swap(x,y);
		for(int i=17;~i;i--)
			if(dep[Jmp[x][i]]>=dep[y])
				x=Jmp[x][i];
		if(x==y) return x;
		for(int i=17;~i;i--)
			if(Jmp[x][i]!=Jmp[y][i])
				x=Jmp[x][i],y=Jmp[y][i];
		return Jmp[x][0];
	}

	inline int dis(int x,int y) {return Dis[x]+Dis[y]-2*Dis[LCA(x,y)];}

	inline void insert(int x,int fa,int v,int rv)
	{
		Jmp[x][0]=fa;dep[x]=dep[fa]+1;Dis[x]=Dis[fa]+v;r[x]=rv;
		G[x].push_back({fa,v});G[fa].push_back({x,v});
		for(int i=1;i<=17;i++)
			Jmp[x][i]=Jmp[Jmp[x][i-1]][i-1];
	}
}

namespace Divide_Conquer{
	using Tree::G;using Tree::dis;using Tree::r;
	int rt[2][MAXN],fa[MAXN];
	vector<int> son[MAXN];//点分树
	int Siz[MAXN],RT,mx_rt;
	bool avai[MAXN];
	
	void dfs_f(int x)
	{
		avai[x]=1;
		for(int v:son[x])
			dfs_f(v);
		son[x].clear();fa[x]=0;
		// Treap::clear(rt[0][x]);Treap::clear(rt[1][x]);
		Treap2::del_node(rt[0][x]);Treap2::del_node(rt[1][x]);
	}

	void get_rt(int x,int fa,int sz)
	{
		Siz[x]=1;int mx=0;
		for(auto v:G[x])
			if(v.first!=fa&&avai[v.first])
				get_rt(v.first,x,sz),Siz[x]+=Siz[v.first],
				mx=max(mx,Siz[v.first]);
		mx=max(mx,sz-Siz[x]);
		if(mx<mx_rt) RT=x,mx_rt=mx;
	}

	void dfs(int x,int fa,int dep,int Rt,bool tp,int RRt)
	{
		// if(!tp) Treap::insert(rt[tp][Rt],dep-r[x]);
		// else Treap::insert(rt[tp][Rt],dis(RRt,x)-r[x]);

		if(!tp) Treap2::insert(rt[tp][Rt],dep-r[x]);
		else Treap2::insert(rt[tp][Rt],dis(RRt,x)-r[x]);
		for(auto v:G[x])
			if(avai[v.first]&&v.first!=fa)
				dfs(v.first,x,dep+v.second,Rt,tp,RRt);
	}

	void solve(int x)
	{
		avai[x]=0;
		dfs(x,0,0,x,0,0);
		if(fa[x]) dfs(x,0,0,x,1,fa[x]);
		for(auto v:G[x])
			if(avai[v.first])
			{
				mx_rt=1<<30;
				get_rt(v.first,x,Siz[v.first]);
				fa[RT]=x;son[x].push_back(RT);
				solve(RT);
			}
	}

	inline void rebuild(int x)
	{
		++rebuid_count;
		// int rfa=fa[x],tot=Treap::siz[rt[0][x]];
		int rfa=fa[x],tot=Treap2::a[rt[0][x]].s;
		dfs_f(x);mx_rt=1<<30;
		get_rt(x,0,tot);
		for(int& v:son[rfa])
			if(v==x)
				v=RT;
		fa[RT]=rfa;solve(RT);
	}

	inline int append(int x,int Fa,int v,int rv)
	{
		int ret=0;
		Tree::insert(x,Fa,v,rv);
		fa[x]=Fa;son[Fa].push_back(x);
		for(int p=x;p;p=fa[p])
		{
			// ret+=Treap::query_less(rt[0][p],rv-dis(p,x)),Treap::insert(rt[0][p],dis(p,x)-rv);
			// if(fa[p]) ret-=Treap::query_less(rt[1][p],rv-dis(fa[p],x)),Treap::insert(rt[1][p],dis(fa[p],x)-rv);
			
			ret+=Treap2::qrank(rt[0][p],rv-dis(p,x)),Treap2::insert(rt[0][p],dis(p,x)-rv);
			if(fa[p]) ret-=Treap2::qrank(rt[1][p],rv-dis(fa[p],x)),Treap2::insert(rt[1][p],dis(fa[p],x)-rv);
		}
		int Pnt=0;
		for(int p=x;fa[p];p=fa[p])
		{
			if(1.0*Treap2::a[rt[0][p]].s>Treap2::a[rt[0][fa[p]]].s*alpha&&Treap2::a[rt[0][fa[p]]].s>30)
				Pnt=fa[p];
			// if(1.0*Treap::siz[rt[0][p]]>Treap::siz[rt[0][fa[p]]]*alpha&&Treap::siz[rt[0][fa[p]]]>30)
			// 	Pnt=fa[p];
		}
		if(Pnt) rebuild(Pnt);
		return ret;
	}

	inline void append_first(int x,int rv)
	{
		Treap2::insert(rt[0][x],-rv);
		Tree::dep[x]=1;r[x]=rv;
	}
}


signed main()
{
	// int t=clock();
	srand((ull)new char);
	int fafa;read(fafa);read(n);
	int a1,r1,c1;
	read(a1,c1,r1);
	Divide_Conquer::append_first(1,r1);
	printf("0\n");
	for(int i=2,a,r,c;i<=n;i++)
	{
		read(a,c,r);
		a=a^(Ans%P);
		Ans+=Divide_Conquer::append(i,a,c,r);
		printf("%lld\n",Ans);
	}
	// fprintf(stderr,"time=%lf rebuild_times=%d\n",1.0*(clock()-t)/CLOCKS_PER_SEC,rebuid_count);
}