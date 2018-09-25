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

const int MAXN=3E5+10;

#define int ll

vector<int> v;
vector<pair<ll,int>> Pnt;
ll cst[MAXN][20],lft[MAXN];
vector<pair<int,int> > g[MAXN];
int n,jmp[MAXN][20],pos[MAXN],dft,lc[MAXN],dep[MAXN];
int am[MAXN],am1[MAXN],m,cur,top[MAXN],val[MAXN];
bool tag[MAXN],vis[MAXN],chk[MAXN];

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

void init()
{
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1],
			cst[i][j]=cst[i][j-1]+cst[jmp[i][j-1]][j-1];
}

void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	pos[x]=++dft;jmp[x][0]=fa;
	for(auto v:g[x])
	{
		if(v.first!=fa)
			cst[v.first][0]=v.second,
			dfs1(v.first,x);
		if(x==1) cst[v.first][0]=1ll<<60;
	}
}

void dfs2(int x,int fa,int cnt)
{
	cnt+=tag[x];
	for(auto v:g[x])
	{
		if(x==1) cur=v.first;
		if(v.first!=fa)
			dfs2(v.first,x,cnt);
	} 
	if(g[x].size()==1&&!cnt&&!vis[cur]) v.push_back(cur),vis[cur]=1;
}

int Jmp(int x,ll v,int p)
{
	for(int j=19;~j;j--)
	{
		if(cst[x][j]<=v)
			v-=cst[x][j],
			x=jmp[x][j];
	}
	if(v>=val[x]&&jmp[x][0]==1) v-=val[x],top[p]=x,x=1;
	lft[p]=v;
	return x;
}

bool check(ll Mid)
{
	Pnt.clear();memset(tag,0,sizeof tag);memset(vis,0,sizeof vis);v.clear();memset(chk,0,sizeof chk);
	for(int i=1;i<=m;i++)
	{
		int x=Jmp(am[i],Mid,i);
		if(x==1) Pnt.push_back({lft[i],top[i]});
		else tag[x]=1;
	}
	dfs2(1,0,0);
	sort(Pnt.begin(),Pnt.end());
	sort(v.begin(),v.end(),[](int l,int r)->bool{return val[l]<val[r];});
	int i,j;
	for(i=0,j=0;i<Pnt.size()&&j<v.size();)
	{
		if(chk[v[j]]) ++j;
		else
		{
			if(Pnt[i].first>=val[v[j]]) ++i,++j;
			else chk[Pnt[i].second]=1,++i;
		}
	}
	while(j<v.size()&&chk[v[j]]) ++j;
	return j>(signed)v.size()-1;
}

signed main()
{
	read(n);
	for(int i=1,u,v,w;i<n;i++)
		read(u),read(v),read(w),g[u].push_back({v,w}),g[v].push_back({u,w});
	for(auto v:g[1]) val[v.first]=v.second;
	dfs1(1,0);init();
	read(m);
	for(int i=1;i<=m;i++) read(am[i]);
	ll L=0,R=1E18,Ans=-1;
	while(L<=R)
	{
		ll mid=(L+R)>>1;
		if(check(mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%lld\n",Ans);
}