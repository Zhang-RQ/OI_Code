#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2010;
const int MAXM=8E6+10;

struct edge_t{
	int v,f,nxt;
}Edge[MAXM];

int thead[MAXN],head[MAXN],cnt_e=1,lvl[MAXN],mp[MAXN][MAXN];
int S=0,T=MAXN-1,X[MAXN],Y[MAXN],n,tot,blx[MAXN][MAXN],bly[MAXN][MAXN];
int L[MAXN],R[MAXN],pos[MAXN],q[MAXN];
vector<int> Vx,Vy;
set<pair<int,int> > Sx[MAXN],Sy[MAXN];

void add(int u,int v,int f){Edge[++cnt_e]=(edge_t){v,f,head[u]};head[u]=cnt_e;}

void add2(int u,int v,int f){add(u,v,f);add(v,u,0);}

bool BFS()
{
	memset(lvl,0,sizeof lvl);
	lvl[S]=1;
	int hd=1,tl=0;
	q[++tl]=S;
	while(hd<=tl)
	{
		int x=q[hd++];
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(!Edge[i].f||lvl[v])
				continue;
			lvl[v]=lvl[x]+1;
			q[++tl]=v;
		}
	}
	return lvl[T]!=0;
}

int dfs(int x,int curf)
{
	if(x==T)
		return curf;
	for(int &i=thead[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(lvl[v]!=lvl[x]+1||!Edge[i].f)
			continue;
		int mnf=dfs(v,min(curf,Edge[i].f));
		if(!mnf)
			continue;
		Edge[i].f-=mnf;
		Edge[i^1].f+=mnf;
		return mnf;
	}
	return 0;
}

int Max_Flow()
{
	int Ans=0;
	while(BFS())
	{
		memcpy(thead,head,sizeof head);
		int flw;
		while((flw=dfs(S,1<<30)))
			Ans+=flw;
	}
	return Ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&X[i],&Y[i]),Vx.push_back(X[i]),Vy.push_back(Y[i]);
	sort(Vx.begin(),Vx.end());sort(Vy.begin(),Vy.end());
	Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	int limx=Vx.size(),limy=Vy.size();
	for(int i=1;i<=n;i++)
		X[i]=lower_bound(Vx.begin(),Vx.end(),X[i])-Vx.begin()+1,
		Y[i]=lower_bound(Vy.begin(),Vy.end(),Y[i])-Vy.begin()+1,
		mp[X[i]][Y[i]]=1;
	for(int x=1;x<=limx;x++)
	{
		int lsty=-1,firy=-1;
		for(int y=1;y<=limy;y++)
			if(mp[x][y])
			{
				if(~lsty)
				{
					++tot;
					L[tot]=lsty;R[tot]=y;pos[tot]=x;
					for(int j=lsty+1;j<=y-1;j++)
						blx[x][j]=tot;
					add2(S,tot,1);
				}
				else firy=y;
				lsty=y;
			}
		if(~firy)
			Sx[x].insert({firy,lsty});
	}
	int upx=tot;//[1..upx] x,[upx+1,tot] y
	for(int y=1;y<=limy;y++)
	{
		int lstx=-1,firx=-1;
		for(int x=1;x<=limx;x++)
			if(mp[x][y])
			{
				if(~lstx)
				{
					++tot;
					L[tot]=lstx;R[tot]=x;pos[tot]=y;
					for(int j=lstx+1;j<=x-1;j++)
						bly[j][y]=tot;
					add2(tot,T,1);
				}
				else firx=x;
				lstx=x;
			}
		if(~firx)
			Sy[y].insert({firx,lstx});
	}
	for(int x=1;x<=limx;x++)
		for(int y=1;y<=limy;y++)
			if(!mp[x][y]&&blx[x][y]&&bly[x][y])
				add2(blx[x][y],bly[x][y],1<<30);
	int Ans=Vx.size()+Vy.size(),V=Vx.size(),H=Vy.size();
	Ans+=Max_Flow();BFS();
	for(int i=1;i<=upx;i++)
		if(!lvl[i]) //not choose i
		{
			set<pair<int,int> >::iterator it=Sx[pos[i]].lower_bound({L[i],0});
			if(it==Sx[pos[i]].end()||it->first!=L[i])
				--it;
			int tL=it->first,tR=it->second;
			Sx[pos[i]].erase(it);
			Sx[pos[i]].insert({tL,L[i]});
			Sx[pos[i]].insert({R[i],tR});
			++V;
		}
	for(int i=upx+1;i<=tot;i++)
		if(lvl[i])
		{
			set<pair<int,int> >::iterator it=Sy[pos[i]].lower_bound({L[i],0});
			if(it==Sy[pos[i]].end()||it->first!=L[i])
				--it;
			int tL=it->first,tR=it->second;
			Sy[pos[i]].erase(it);
			Sy[pos[i]].insert({tL,L[i]});
			Sy[pos[i]].insert({R[i],tR});
			++H;
		}
	printf("%d\n",H);
	for(int i=1;i<=limy;i++)
		for(auto l:Sy[i])
			printf("%d %d %d %d\n",Vx[l.first-1],Vy[i-1],Vx[l.second-1],Vy[i-1]);
	printf("%d\n",V);
	for(int i=1;i<=limx;i++)
		for(auto l:Sx[i])
			printf("%d %d %d %d\n",Vx[i-1],Vy[l.first-1],Vx[i-1],Vy[l.second-1]);
}
