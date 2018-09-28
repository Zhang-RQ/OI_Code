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
const int Mxblk=350;

struct Query{
	Query(int _x=0,int _f=0,int _id=0){x=_x;f=_f;id=_id;}
	int x,f,id;
};

int n,q,lim=340,st[MAXN],ed[MAXN];
ll Ans[MAXN],f[MAXN],sum[MAXN];
char s[MAXN],str[MAXN];
vector<Query> v[MAXN],V[MAXN];

namespace AC_Automaton{
	int son[MAXN][26],fail[MAXN],rt,edpos[MAXN],cnt,siz[MAXN],pos[MAXN],dft,cnts[MAXN],tps[MAXN],top;
	vector<int> fv[MAXN];

	void insert(int nm)
	{
		int x=rt;
		for(int i=1;s[i];i++)
		{
			if(!son[x][s[i]-'a']) son[x][s[i]-'a']=++cnt;
			x=son[x][s[i]-'a'];
		}
		edpos[nm]=x;
	}

	void build_fail()
	{
		queue<int> q;
		for(int i=0;i<26;i++)
			if(son[rt][i])
				q.push(son[rt][i]),fv[rt].push_back(son[rt][i]),++cnts[rt];
		while(!q.empty())
		{
			int x=q.front();q.pop();
			for(int i=0;i<26;i++)
				if(son[x][i])
				{
					int y=fail[x];
					while(y&&!son[y][i]) y=fail[y];
					if(son[y][i]) fail[son[x][i]]=son[y][i];
					else fail[son[x][i]]=rt;
					++cnts[fail[son[x][i]]];
					fv[fail[son[x][i]]].push_back(son[x][i]);
					q.push(son[x][i]);
				}
		}
	}

	void dfs_fail(int x)
	{
		pos[x]=++dft;siz[x]=1;
		for(int v:fv[x])
			dfs_fail(v),siz[x]+=siz[v];
	}

	void topo()
	{
		queue<int> q;
		for(int i=1;i<=cnt;i++)
			if(!cnts[i])
				q.push(i);
		while(!q.empty())
		{
			int x=q.front();q.pop();
			tps[++top]=x;
			if(!(--cnts[fail[x]]))
				q.push(fail[x]);
		}
	}
}

namespace Block{
	int tag[Mxblk],bl[MAXN],L[Mxblk],R[Mxblk],a[MAXN];
	void init(int n)
	{
		int blksiz=sqrt(n);
		for(int i=1;i<=n;i++)
		{
			bl[i]=(i-1)/blksiz+1;
			if(!L[bl[i]]) L[bl[i]]=i;
			R[bl[i]]=i;
		}
	}
	void plus(int l,int r,int v)
	{
		int Bl=bl[l],Br=bl[r];
		if(Bl==Br)
			for(int i=l;i<=r;i++)
				a[i]+=v;
		else
		{
			for(int i=l;i<=R[Bl];i++)
				a[i]+=v;
			for(int i=L[Br];i<=r;i++)
				a[i]+=v;
			for(int i=Bl+1;i<=Br-1;i++)
				tag[i]+=v;
		}
	}
	int query(int pos){return a[pos]+tag[bl[pos]];}
}

void solve_short()
{
	for(int i=1;i<=n;i++)
	{
		Block::plus(AC_Automaton::pos[AC_Automaton::edpos[i]],AC_Automaton::pos[AC_Automaton::edpos[i]]+AC_Automaton::siz[AC_Automaton::edpos[i]]-1,1);
		for(auto p:V[i])
		{
			for(int j=st[p.x],x=0;j<=ed[p.x];j++)
			{
				x=AC_Automaton::son[x][str[j]-'a'];
				Ans[p.id]+=p.f*Block::query(AC_Automaton::pos[x]);
			}
		}
	}
}

void solve_long()
{
	for(int i=1;i<=n;i++)
		if((ed[i]-st[i]+1)>lim)
		{
			memset(f,0,sizeof f);memset(sum,0,sizeof sum);
			for(int j=st[i],x=0;j<=ed[i];j++)
			{
				x=AC_Automaton::son[x][str[j]-'a'];
				f[x]++;
			}
			for(int j=1;j<=AC_Automaton::cnt;j++)
					f[AC_Automaton::fail[AC_Automaton::tps[j]]]+=f[AC_Automaton::tps[j]];
			for(int j=1;j<=n;j++)
				sum[j]=f[AC_Automaton::edpos[j]];
			for(int j=1;j<=n;j++)
				sum[j]+=sum[j-1];
			for(auto p:v[i])
				Ans[p.id]+=p.f*sum[p.x];
		}
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1),AC_Automaton::insert(i);
		st[i]=ed[i-1]+1;ed[i]=st[i]-1;
		for(int j=1;s[j];j++)
			str[++ed[i]]=s[j];
	}
	AC_Automaton::build_fail();AC_Automaton::dfs_fail(0);AC_Automaton::topo();
	Block::init(AC_Automaton::cnt+1);
	for(int i=1,l,r,k;i<=q;i++)
	{
		scanf("%d%d%d",&l,&r,&k);
		if((ed[k]-st[k]+1)>lim)
		{
			if(l!=1) v[k].push_back(Query(l-1,-1,i));
			v[k].push_back(Query(r,1,i));
		}
		else
		{
			if(l!=1) V[l-1].push_back(Query(k,-1,i));
			V[r].push_back(Query(k,1,i));
		}
	}
	solve_long();solve_short();
	for(int i=1;i<=q;i++) printf("%lld\n",Ans[i]);
}