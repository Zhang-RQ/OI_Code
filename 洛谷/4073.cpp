#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

#define double long double

const int MAXN=2E5+10;
const double EPS=1E-8;
const int msk=(1<<30)-2;
const double INF=1E9;

struct g_edge_t{
	int v,w;double k;	
}gEdge[MAXN<<1];

struct edge_t{
	int u,v,w;

	bool operator < (const edge_t &rhs) const {return w<rhs.w;}
}Edge[MAXN<<1];

double global_x;

struct Line{
	double k,b;
	int id;

	bool operator < (const Line &rhs) const
	{
		double y1=k*global_x+b,y2=rhs.k*global_x+rhs.b;
		if(abs(y1-y2)>EPS)
			return y1<y2;
		else if(rhs.id==-1)
			return false;
		else if(abs(k-rhs.k)>EPS)
			return k<rhs.k;
		else if(abs(b-rhs.b)>EPS)
			return b<rhs.b;
		return id<rhs.id;
	}
};

set<Line> S;

struct opt{
	int tp,id;//tp=0 point insert,tp=1 point erase,tp=2 ask
	double x,y;

	bool operator < (const opt &rhs) const {return x<rhs.x||(x==rhs.x&&tp<rhs.tp);}
}op[MAXN<<1];

set<int> Si;
int n,m,q,X[MAXN],Y[MAXN],cnt_e=1,Rank[MAXN],V[MAXN],vis[MAXN],Inf_id,tot,cnt_e2,fa[MAXN],jmp[MAXN][18],mx[MAXN][18],dep[MAXN];//Rank in Out
int cntop,id[MAXN],downp[MAXN];
double Qx[MAXN<<1],Qy[MAXN<<1];
vector<int> Out[MAXN],pnt[MAXN];
vector<pair<int,int> > T[MAXN];

void add(int u,int v,int w)
{
	double k=atan2(Y[v]-Y[u],X[v]-X[u]);
	if(k<0) k+=100;
	gEdge[++cnt_e]=(g_edge_t){v,w,k};
	Out[u].push_back(cnt_e);
}

int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int x,int fa)
{
	jmp[x][0]=fa;
	dep[x]=dep[fa]+1;
	for(auto e:T[x])
		if(e.first!=fa)
			dfs(e.first,x),
			mx[e.first][0]=e.second;
}

int Ask(int u,int v)
{
	int Ret=0;
	if(dep[u]<dep[v])
		swap(u,v);
	for(int j=17;~j;j--)
		if(dep[jmp[u][j]]>=dep[v])
			Ret=max(Ret,mx[u][j]),
			u=jmp[u][j];
	if(u==v)
		return Ret;
	for(int j=17;~j;j--)
		if(jmp[u][j]!=jmp[v][j])
			Ret=max(Ret,max(mx[u][j],mx[v][j])),
			u=jmp[u][j],v=jmp[v][j];
	Ret=max(Ret,max(mx[u][0],mx[v][0]));
	return Ret;
}

set<Line>::iterator Find_From_Down(double y)
{
	return S.lower_bound((Line){0,y,-1});
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&X[i],&Y[i]),Si.insert(X[i]);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=n;i++)
		sort(Out[i].begin(),Out[i].end(),[](int x,int y){return gEdge[x].k<gEdge[y].k;});
	for(int i=1;i<=n;i++)
		for(size_t j=0;j<Out[i].size();j++)
			Rank[Out[i][j]]=j;
	for(int i=1;i<=n;i++)
		for(int e:Out[i])
			if(!vis[e])
			{
				int u=i,ee=e,cur=++tot;
				ll S=0;
				do{
					pnt[cur].push_back(u);
					int v=gEdge[ee].v,nxt=Out[v][(Rank[ee^1]+1)%Out[v].size()];
					if(V[ee^1])
						Edge[++cnt_e2]=(edge_t){cur,V[ee^1],gEdge[ee].w};
					V[ee]=cur;vis[ee]=1;
					if(X[v]>X[u])
						downp[ee&msk]=cur;
					S+=1ll*Y[v]*X[u]-1ll*Y[u]*X[v];
					u=v;ee=nxt;
				}while(e!=ee);
				if(S>0)
					Inf_id=cur;
			}
	for(int i=1;i<=tot;i++)
		fa[i]=i;
	sort(Edge+1,Edge+1+cnt_e2);
	//printf("tot=%d cnt_e2=%d\n",tot,cnt_e2);
	for(int i=1;i<=cnt_e2;i++)
	{
		if(Edge[i].u==Inf_id||Edge[i].v==Inf_id)
			continue;
		int u=Edge[i].u,v=Edge[i].v,x=find(u),y=find(v);
		if(x!=y)
		{
			T[u].emplace_back(v,Edge[i].w);
			T[v].emplace_back(u,Edge[i].w);
			fa[x]=y;
		}
	}
	if(Inf_id==1)
		dfs(2,0);
	else
		dfs(1,0);
	for(int j=1;j<=17;j++)
		for(int i=1;i<=tot;i++)
		{
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
			mx[i][j]=max(mx[i][j-1],mx[jmp[i][j-1]][j-1]);
		}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
		scanf("%Lf%Lf%Lf%Lf",&Qx[(i<<1)-1],&Qy[(i<<1)-1],&Qx[i<<1],&Qy[i<<1]);
	for(int i=1;i<=2*q;i++)
		op[++cntop]=(opt){2,i,Qx[i],Qy[i]};
	for(int i=1;i<=n;i++)
		op[++cntop]=(opt){0,i,(double)X[i]+0.1,(double)Y[i]},op[++cntop]=(opt){1,i,(double)X[i]-0.1,(double)Y[i]};
	sort(op+1,op+1+cntop);
	S.insert((Line){0,-1E9,0});
	S.insert((Line){0,1E9,0});
	for(int i=1;i<=cntop;i++)
	{
		global_x=op[i].x;
		if(op[i].tp==0)
		{
			int u=op[i].id;
			for(int e:Out[u])
			{
				int v=gEdge[e].v;
				if(X[u]==X[v])
					continue;
				double k=1.0*(Y[v]-Y[u])/(X[v]-X[u]),b=Y[u]-k*X[u];
				if(X[u]<X[v])
					S.insert((Line){k,b,e&msk});
			}
		}
		else if(op[i].tp==1)
		{
			
			int u=op[i].id;
			for(int e:Out[u])
			{
				int v=gEdge[e].v;
				if(X[u]==X[v])
					continue;
				double k=1.0*(Y[v]-Y[u])/(X[v]-X[u]),b=Y[u]-k*X[u];
				if(X[u]>X[v])
				{
					set<Line>::iterator it=S.lower_bound((Line){k,b,e&msk});
					assert((e&msk)==it->id);
					S.erase(it);
				}
			}
		}
		else
		{
			auto it=Find_From_Down(op[i].y);
			id[op[i].id]=downp[it->id];
			if(id[op[i].id]==Inf_id)
				id[op[i].id]=0;
		}
	}
	for(int i=1;i<=q;i++)
	{
		if(!id[(i<<1)-1]||!id[i<<1])
			puts("-1");
		else  printf("%d\n",Ask(id[(i<<1)-1],id[i<<1]));
	}
}
