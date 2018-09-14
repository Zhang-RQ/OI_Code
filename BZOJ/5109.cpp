#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<bitset>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=5E4+10;
const int P1=998244353;
const int P2=1E9+7;

struct dat{
	ll v1,v2;
	dat(){}
	dat(ll _,ll __){v1=_;v2=__;}
	bool operator <(const dat &rhs) const {return v1<rhs.v1||(v1==rhs.v1&&v2<rhs.v2);}
	bool operator ==(const dat &rhs) const {return v1==rhs.v1&&v2==rhs.v2;}
	dat operator + (const dat &rhs) const {return dat((v1+rhs.v1)%P1,(v2+rhs.v2)%P2);}
	dat operator * (const dat &rhs) const {return dat(v1*rhs.v1%P1,v2*rhs.v2%P2);}
	dat operator - (const dat &rhs) const {return dat((v1-rhs.v1+P1)%P1,(v2-rhs.v2+P2)%P2);}
	void operator += (const dat &rhs){*this=*this+rhs;}
}fs[MAXN],ft[MAXN],f[MAXN];

bitset<MAXN> rea1[MAXN],rea2[MAXN],ful,tmp;
map<dat,bitset<MAXN> > mp;
queue<int> q;
int n,m,S,T,d[MAXN],Q[MAXN],tot;
ll disS[MAXN],disT[MAXN],Ans;
bool vis[MAXN];
vector<pair<int,int> > G[MAXN];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;

inline bool OnDir(int u,int v,int w){return disT[v]+disS[u]+w==disT[S];}

void Dijkstra(int s,ll* dis)
{
	memset(dis,0x3f,sizeof disS);
	dis[s]=0;pq.push(make_pair(0,s));
	while(!pq.empty())
	{
		pair<ll,int> x=pq.top();pq.pop();
		if(x.first!=dis[x.second]) continue;
		for(auto v:G[x.second])
		{
			if(dis[v.first]>dis[x.second]+v.second)
			{
				dis[v.first]=dis[x.second]+v.second;
				pq.push(make_pair(dis[v.first],v.first));
			}
		}
	}
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&S,&T);
	for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),G[u].push_back(make_pair(v,w)),G[v].push_back(make_pair(u,w));
	Dijkstra(S,disS);Dijkstra(T,disT);
	if(disS[T]==disS[0]) return printf("%lld\n",1ll*n*(n-1)/2),0;
	for(int i=1;i<=n;i++) 
		for(auto v:G[i])
			if(OnDir(i,v.first,v.second))
				++d[v.first];
	for(int i=1;i<=n;i++) if(!d[i]) q.push(i);
	fs[S]=dat(1,1);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		Q[++tot]=x;vis[x]=1;
		for(auto v:G[x])
			if(OnDir(x,v.first,v.second))
			{
				if(!(--d[v.first])) q.push(v.first);
				fs[v.first]+=fs[x];
			}
	}
	for(int i=1;i<=n;i++) 
	{
		rea1[i][i]=rea2[i][i]=1;
		ful[i]=1;
	}
	ft[T]=dat(1,1);
	for(int i=n;i>=1;i--)
		for(auto v:G[Q[i]])
			if(OnDir(v.first,Q[i],v.second))
				ft[v.first]+=ft[Q[i]],rea2[v.first]|=rea2[Q[i]];
	for(int i=1;i<=n;i++)
		for(auto v:G[Q[i]])
			if(OnDir(Q[i],v.first,v.second))
				rea1[v.first]|=rea1[Q[i]];
	for(int i=1;i<=n;i++)
		f[i]=fs[i]*ft[i];
	for(int i=1;i<=n;i++)
		mp[f[i]][i]=1;
	for(int i=1;i<=n;i++)
		Ans+=(mp[f[T]-f[i]]&((rea1[i]|rea2[i])^ful)).count();
	printf("%lld\n",Ans>>1);
}