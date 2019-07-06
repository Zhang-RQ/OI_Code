#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

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

const int MAXN=2E5+10;
const int mv[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
const int MAXK=5E6+10;
const int MAXM=5E7+10;

struct Hash_Map{
	static const int HS_P=5000011;
	static const int MAX_ND=5E6+10;
	
	int head[HS_P],TS[HS_P],clk,cnt;
	int nxt[MAX_ND],val[MAX_ND];
	ll st[MAX_ND];

	void clear(){++clk;cnt=0;}

	int& operator [] (ll s)
	{
		int idx=s%HS_P;
		for(int x=TS[idx]==clk?head[idx]:0;x;x=nxt[x])
			if(st[x]==s)
				return val[x];
		++cnt;
		nxt[cnt]=TS[idx]==clk?head[idx]:0;
		head[idx]=cnt;
		st[cnt]=s;TS[idx]=clk;val[cnt]=0;
		return val[cnt];
	}

	int count(ll s)
	{
		int idx=s%HS_P;
		for(int x=TS[idx]==clk?head[idx]:0;x;x=nxt[x])
			if(st[x]==s)
				return 1;
		return 0;
	}
}M,Ban,VIS;

struct edge_t{
	int v,nxt;
}Edge[MAXM];

int n,m,c,X[MAXN],Y[MAXN],tot,head[MAXK],cnt_e;
int dfn[MAXK],low[MAXK],dft,cutcnt,col[MAXK],nowc,globalc,flag;
vector<pair<int,int> > V;

ll ID(int x,int y){return 1ll*x*m+y;}

void add(int u,int v)
{
	Edge[++cnt_e]=(edge_t){v,head[u]};
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	int tson=0,f=0;col[x]=nowc;
	dfn[x]=low[x]=++dft;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(!dfn[v])
		{
			dfs(v,x);++tson;
			low[x]=min(low[x],low[v]);
			if(low[v]>=dfn[x])
				f=1;
		}
		else
			low[x]=min(low[x],dfn[v]);
	}
	if(!fa&&tson==1)
		f=0;
	if(f)
	{
		int rx=V[x-1].first,ry=V[x-1].second;
		for(int dx=-1;dx<=1;dx++)
			for(int dy=-1;dy<=1;dy++)
				if(Ban.count(ID(rx+dx,ry+dy)))
				{
					++cutcnt;
					break;	
				}
	}
}

void dfs_8(int x,int y)
{
	VIS[ID(x,y)]=1;
	for(int dx=-1;dx<=1;dx++)
		for(int dy=-1;dy<=1;dy++)
		{
			int tx=x+dx,ty=y+dy;
			if(!((1<=tx&&tx<=n)&&(1<=ty&&ty<=m)))
				continue;
			if(Ban.count(ID(tx,ty)))
			{
				if(VIS.count(ID(tx,ty)))
				   continue;
				dfs_8(tx,ty);
			}
			else
			{
				if(!~globalc)
					globalc=col[M[ID(tx,ty)]];
				if(col[M[ID(tx,ty)]]!=globalc)
					flag=1;
			}
		}
}

void solve()
{
	nowc=cutcnt=dft=tot=flag=0;
	M.clear();Ban.clear();V.clear();
	VIS.clear();
	read(n,m,c);
	for(int i=1;i<=c;i++)
	{
		read(X[i],Y[i]);
		Ban[ID(X[i],Y[i])]=1;
		for(int dx=-2;dx<=2;dx++)
			for(int dy=-2;dy<=2;dy++)
			{
				if(dx==0&&dy==0)
					continue;
				int tx=X[i]+dx,ty=Y[i]+dy;
				if((1<=tx&&tx<=n)&&(1<=ty&&ty<=m))
				{
					int &id=M[ID(tx,ty)];
					if(!id)
					{
						id=++tot;
						V.emplace_back(tx,ty);
					}
				}
			}
	}
	if(c==0)
	{
		if(n==1&&m==1)
			return puts("-1"),void();
		if(m==1)
			swap(n,m);
		if(n==1)
		{
			if(m>=3)
				return puts("1"),void();
			else
				return puts("-1"),void();
		}
		return puts("2"),void();
	}
	memset(head,0,sizeof(int)*(tot+10));
	memset(dfn,0,sizeof(int)*(tot+10));
	memset(col,0,sizeof(int)*(tot+10));
	cnt_e=0;
	for(auto pr:V)
		if(!Ban.count(ID(pr.first,pr.second)))
		{
			int pid=M[ID(pr.first,pr.second)];
			for(int i=0;i<4;i++)
			{
				int tx=mv[i][0]+pr.first,ty=mv[i][1]+pr.second;
				if(Ban.count(ID(tx,ty)))
					continue;
				if((1<=tx&&tx<=n)&&(1<=ty&&ty<=m))
				{
					int tid=M[ID(tx,ty)];
					if(tid)
						add(pid,tid),add(tid,pid);
				}
			}
		}
	for(auto pr:V)
		if(!Ban.count(ID(pr.first,pr.second)))
		{
			int pid=M[ID(pr.first,pr.second)];
			if(!dfn[pid])
				++nowc,dfs(pid,0);
		}
	for(int i=1;i<=c;i++)
		if(!VIS.count(ID(X[i],Y[i])))
		{
			globalc=-1;
			dfs_8(X[i],Y[i]);
		}
	if(flag)
		return puts("0"),void();
	if(1ll*n*m-c<=2)
		return puts("-1"),void();
	if(cutcnt)
		return puts("1"),void();
	if(n==1||m==1)
		return puts("1"),void();
	puts("2");
}

int main()
{
	int T;
	for(read(T);T--;solve());
}
