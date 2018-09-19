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
const int INF=1<<30;

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

bool vis[MAXN];
int n,L,R,Mid,q[MAXN],ttAns;
vector<pair<int,int> > g[MAXN];
int siz[MAXN],rt,mx_rt,d[MAXN],dn[MAXN],d1[MAXN],d1n[MAXN],dep[MAXN],num[MAXN],tot;
pair<int,int> Ans,tAns;

void get_rt(int x,int fa,int sz)
{
	int mx=0;siz[x]=1;
	for(pair<int,int> v:g[x])
		if(!vis[v.first]&&v.first!=fa)
			get_rt(v.first,x,sz),
			siz[x]+=siz[v.first],
			mx=max(mx,siz[v.first]);
	mx=max(mx,sz-siz[x]);
	if(mx<mx_rt) mx_rt=mx,rt=x;
}

void get_dep(int x,int fa)
{
	dep[x]=1;
	for(pair<int,int> v:g[x])
		if(v.first!=fa&&!vis[v.first])
			get_dep(v.first,x),
			dep[x]=max(dep[x],dep[v.first]+1);
}

void dfs1(int x,int fa,int dep,int val)
{
	if(val>d1[dep]) d1[dep]=val,d1n[dep]=x;
	for(pair<int,int> v:g[x])
		if(v.first!=fa&&!vis[v.first])
			dfs1(v.first,x,dep+1,val+(v.second>=Mid?1:-1));
}

void solve(int x)
{
	vis[x]=1;
	get_dep(x,0);
	sort(g[x].begin(),g[x].end(),[](const pair<int,int> &lhs,const pair<int,int> &rhs)->bool{return dep[lhs.first]<dep[rhs.first];});
	d[0]=0,dn[0]=x;
	int mx=0;
	for(pair<int,int> v:g[x])
	{
		if(vis[v.first]) continue;
		dfs1(v.first,x,1,v.second>=Mid?1:-1);
		int head=1,tail=0;
		for(int i=min(R,mx);i>=L;i--)
		{
			while(head<=tail&&d[q[tail]]<d[i]) tail--;
			q[++tail]=i;
		}
		for(int i=1;i<=dep[v.first];i++)
		{
			if(L-i>=0)
			{
				while(head<=tail&&d[q[tail]]<d[L-i]) tail--;
				q[++tail]=L-i;
			}
			while(head<=tail&&q[head]+i>R) head++;
			if(head<=tail&&d[q[head]]+d1[i]>ttAns) ttAns=d[q[head]]+d1[i],tAns=make_pair(d1n[i],dn[q[head]]);
		}
		for(int i=1;i<=dep[v.first];i++)
			if(d1[i]>d[i]) d[i]=d1[i],dn[i]=d1n[i];
		for(int i=1;d1[i]!=-INF;i++)	d1[i]=-INF;
	}
	for(int i=0;d[i]!=-INF;i++) d[i]=-INF;
	for(pair<int,int> v:g[x])
	{
		if(vis[v.first]) continue;
		mx_rt=1<<30;
		get_rt(v.first,x,siz[v.first]);
		solve(rt);
	}
}

bool check(int x)
{
	memset(vis,0,sizeof vis);
	Mid=x;
	ttAns=-(1<<30);
	mx_rt=1<<30;
	get_rt(1,0,n);
	solve(rt);
	return ttAns>=0;
}

int main()
{
	read(n,L,R);
	for(int i=0;i<=n;i++) d[i]=d1[i]=-INF;
	for(int i=1,u,v,w;i<n;i++)
	{
		read(u,v,w);
		g[u].push_back({v,w});
		g[v].push_back({u,w});
		num[++tot]=w;
	}
	sort(num+1,num+1+tot);
	tot=unique(num+1,num+1+tot)-num-1;
	int l=1,r=tot;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(num[mid])) Ans=tAns,l=mid+1;
		else r=mid-1;
	}
	printf("%d %d\n",Ans.first,Ans.second);
}