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

const int MAXN=1E6+10;

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

namespace Segment_Tree{
	ll Sump[MAXN<<2],Sumc[MAXN<<2];

	void pushup(int x)
	{
		Sump[x]=Sump[x<<1]+Sump[x<<1|1];
		Sumc[x]=Sumc[x<<1]+Sumc[x<<1|1];
	}

	void change(int x,int l,int r,int p,ll c)
	{
		if(l==r) return Sumc[x]+=c,Sump[x]+=1ll*l*c,void();
		int mid=(l+r)>>1;
		if(p<=mid) change(x<<1,l,mid,p,c);
		else change(x<<1|1,mid+1,r,p,c);
		pushup(x);
	}

	ll Query(int x,int l,int r,ll k)
	{
		if(k>=Sumc[x]) return Sump[x];
		if(l==r) return 1ll*l*k;
		ll lsiz=Sumc[x<<1];int mid=(l+r)>>1;
		if(lsiz>=k) return Query(x<<1,l,mid,k);
		else return Sump[x<<1]+Query(x<<1|1,mid+1,r,k-lsiz);
	}
}

ll Ans;
int n,m,k;
vector<pair<int,int> > v[MAXN<<2];

void insert(int x,int l,int r,int cl,int cr,pair<int,int> p)
{
	if(cl<=l&&r<=cr) return v[x].push_back(p),void();
	int mid=(l+r)>>1;
	if(cl<=mid) insert(x<<1,l,mid,cl,cr,p);
	if(cr>mid)  insert(x<<1|1,mid+1,r,cl,cr,p);
}

void dfs(int x,int l,int r)
{
	for(auto p:v[x]) Segment_Tree::change(1,1,1000000,p.first,p.second);
	if(l==r)
	{
		Ans+=Segment_Tree::Query(1,1,1000000,k);
		for(auto p:v[x]) Segment_Tree::change(1,1,1000000,p.first,-p.second);
		return;
	}
	int mid=(l+r)>>1;
	dfs(x<<1,l,mid);dfs(x<<1|1,mid+1,r);
	for(auto p:v[x]) Segment_Tree::change(1,1,1000000,p.first,-p.second);
}

signed main()
{
	read(n,k,m);
	for(int i=1,l,r,p,c;i<=m;i++)
	{
		read(l,r,c,p);
		insert(1,1,n,l,r,{p,c});
	}
	dfs(1,1,n);
	printf("%lld\n",Ans);
}