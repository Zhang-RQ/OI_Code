#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=5E5+10;

int n,st[MAXN<<1][20],lca[MAXN<<1][20],lg2[MAXN<<1],pos[MAXN],dft,dep[MAXN],fa[MAXN];
ll g[MAXN];
vector<int> T[MAXN],pnt[MAXN];

struct Stack{
	int pnt[MAXN],dep[MAXN],pos[MAXN];
	int siz;

	void push(int x,int y,int z){pnt[++siz]=x;dep[siz]=y;pos[siz]=z;}
	void pop(){--siz;}
	ll calc(){return dep[siz]*(pos[siz]-pos[siz-1]);}
	int top(){return pnt[siz];}
	int topd(){return dep[siz];}
	void clear(){siz=0;}
}S;

void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	st[pos[x]=++dft][0]=dep[x];
	lca[dft][0]=x;::fa[x]=fa;
	pnt[dep[x]].push_back(x);
	for(int v:T[x])
		if(v!=fa)
		{
			dfs(v,x);
			st[++dft][0]=dep[x];
			lca[dft][0]=x;
		}
}

int LCA(int x,int y)
{
	x=pos[x];y=pos[y];
	if(x>y)
		swap(x,y);
	int len=lg2[y-x+1];
	return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
}

void init()
{
	for(int i=2;i<=dft;i++)
		lg2[i]=lg2[i>>1]+1;
	for(int j=1;j<=lg2[dft];j++)
		for(int i=1;i+(1<<j)-1<=dft;i++)
			if(st[i][j-1]<st[i+(1<<(j-1))][j-1])
				lca[i][j]=lca[i][j-1],st[i][j]=st[i][j-1];
			else
				lca[i][j]=lca[i+(1<<(j-1))][j-1],st[i][j]=st[i+(1<<(j-1))][j-1];
}

int main()
{
	scanf("%d",&n);
	int rt=0;
	for(int i=1,fa;i<=n;i++)
	{
		scanf("%d",&fa);
		if(!fa)
			rt=i;
		else
			T[fa].push_back(i);
	}
	dfs(rt,0);init();
	for(int i=2;i<=n;i++)
		if(pnt[i].size())
		{
			for(auto p:pnt[i])
				g[p]=g[fa[p]]+i-1;
			S.clear();ll tAns=0;
			for(int _=0;_<pnt[i].size();_++)
			{
				int p=pnt[i][_];
				if(!_)
					S.push(p,0,0);
				else
				{
					while(1)
					{
						int l=LCA(S.top(),p);
						if(S.topd()<=dep[l]) {S.push(p,dep[l],_);break;}
						tAns-=S.calc();S.pop();
					}
					tAns+=S.calc();
				}
				g[p]+=tAns;
			}
			reverse(pnt[i].begin(),pnt[i].end());
			S.clear();tAns=0;
			for(int _=0;_<pnt[i].size();_++)
			{
				int p=pnt[i][_];
				if(!_)
					S.push(p,0,0);
				else
				{
					while(1)
					{
						int l=LCA(S.top(),p);
						if(S.topd()<=dep[l]) {S.push(p,dep[l],_);break;}
						tAns-=S.calc();S.pop();
					}
					tAns+=S.calc();
				}
				g[p]+=tAns;
			}
		}
	for(int i=1;i<=n;i++)
		printf("%lld%c",g[i],"\n "[i!=n]);
}
