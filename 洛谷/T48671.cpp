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

const int MAXN=2E5+10;
const int MAXQ=2E5+10;

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

struct Query{
	int u,v,id;
}Q[MAXQ],tl[MAXQ],tr[MAXQ];

int n,m,k,p,q,cnt;
vector<pair<int,int> > g[MAXN];
ll dis[MAXN],Dis[25][25],Ans[MAXQ];

void Floyd(int L,int R)
{
	memset(Dis,0x3f,sizeof Dis);
	int ofs=L-1,lim=R-L+1;
	for(int i=L;i<=R;i++)
		for(auto v:g[i])
			if(L<=v.first&&v.first<=R)
				Dis[i-ofs][v.first-ofs]=min(Dis[i-ofs][v.first-ofs],(ll)v.second);
	for(int i=1;i<=lim;i++)
		Dis[i][i]=0;
	for(int k=1;k<=lim;k++)
		for(int i=1;i<=lim;i++)
			for(int j=1;j<=lim;j++)
				Dis[i][j]=min(Dis[i][k]+Dis[k][j],Dis[i][j]);
}

void Dijkstra(int L,int R,int S,ll* d)
{
	priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;
	assert(L<=S&&S<=R);
	for(int i=L;i<=R;i++)
		d[i]=0x3f3f3f3f3f3f3f3f;
	d[S]=0;pq.push({d[S],S});
	while(!pq.empty())
	{
		auto x=pq.top();pq.pop();
		if(d[x.second]!=x.first) continue;
		for(auto v:g[x.second])
		{
			if(!(L<=v.first&&v.first<=R)) continue;
			if(d[v.first]>x.first+v.second)
			{
				d[v.first]=x.first+v.second;
				pq.push({d[v.first],v.first});
			}
		}
	}
}

void solve(int L,int R,int Ql,int Qr)
{
	if(Qr<Ql||R<L) return;
	if(R-L+1<=20)
	{
		Floyd(L,R);
		for(int i=Ql;i<=Qr;i++)
			Ans[Q[i].id]=min(Ans[Q[i].id],Dis[Q[i].u-L+1][Q[i].v-L+1]);
		return;
	}
	int mid=(L+R)>>1,k1=10,k2=10;
	for(int i=1;i<=20;i++)
	{
		Dijkstra(L,R,mid-k1+i,dis);
		for(int j=Ql;j<=Qr;j++)
			Ans[Q[j].id]=min(Ans[Q[j].id],dis[Q[j].u]+dis[Q[j].v]);
	}
	int totl=0,totr=0;
	for(int i=Ql;i<=Qr;i++)
	{
		if(Q[i].v<=mid-k1)
			tl[++totl]=Q[i];
		if(Q[i].u>=mid+k2-1)
			tr[++totr]=Q[i];
	}
	for(int i=1;i<=totl;i++)
		Q[Ql+i-1]=tl[i];
	for(int i=1;i<=totr;i++)
		Q[Qr-i+1]=tr[i];
	solve(L,mid-k1,Ql,Ql+totl-1);solve(mid+k2-1,R,Qr-totr+1,Qr);
}

int main()
{
	memset(Ans,0x3f,sizeof Ans);
	read(n,m,k,p,q);
	for(int i=1,x;i<=n;i++) read(x),cnt+=x;
	for(int i=1,u,v,w;i<=m;i++)
	{
		read(u,v,w);
		g[u].push_back({v,w});g[v].push_back({u,w});
	}
	for(int i=1,u,v;i<=q;i++)
	{
		read(u,v);
		if(u>v) swap(u,v);
		Q[i].u=u;Q[i].v=v;Q[i].id=i;
	}
	solve(1,cnt,1,q);
	for(int i=1;i<=q;i++)
		if(Ans[i]==Ans[0])
			puts("-1");
		else printf("%lld\n",Ans[i]);
}