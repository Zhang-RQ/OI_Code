#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

struct edge_t{
	int v,a,b,nxt;
};

struct Graph{
	int head[MAXN],cnt_e;
	edge_t Edge[MAXN<<1];

	int& operator () (int x){return head[x];}
	edge_t& operator [] (int x){return Edge[x];}

	void add(int u,int v,int a,int b){Edge[++cnt_e]=(edge_t){v,a,b,head[u]};head[u]=cnt_e;}
}pT,T;

struct pnt{
	ll x,y;

	pnt operator + (const pnt &rhs) const {return (pnt){x+rhs.x,y+rhs.y};}
	pnt operator - (const pnt &rhs) const {return (pnt){x-rhs.x,y-rhs.y};}
	ll operator * (const pnt &rhs) const {return x*rhs.y-y*rhs.x;}
}stk[MAXN*44];

int n,m,Fa[MAXN],siz[MAXN],vis[MAXN],cnt,rt,mxrt;
vector<pnt> Global_Convex;

void Build_Convex(vector<pnt> &V)
{
	assert(V.size()<MAXN*44);
	sort(V.begin(),V.end(),[](const pnt &lhs,const pnt &rhs){return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y>rhs.y);});
	int top=0;
	for(auto p:V)
	{
		while(top>1&&(p-stk[top-1])*(stk[top]-stk[top-1])<=0)
			--top;
		stk[++top]=p;
	}
	V.clear();
	for(int i=1;i<=top;i++)
		V.push_back(stk[i]);
}

void Minkowski_Sum(const vector<pnt> &l,const vector<pnt> &r,vector<pnt> &res)
{
	assert(l.size()>0&&r.size()>0);
	res.push_back(l[0]+r[0]);
	int ptr1=1,ptr2=1;
	while(ptr1<l.size()&&ptr2<r.size())
	{
		if((l[ptr1]-l[ptr1-1])*(r[ptr2]-r[ptr2-1])>0)
			res.push_back(res.back()+r[ptr2]-r[ptr2-1]),ptr2++;
		else
			res.push_back(res.back()+l[ptr1]-l[ptr1-1]),ptr1++;
	}
	while(ptr1<l.size())
		res.push_back(res.back()+l[ptr1]-l[ptr1-1]),ptr1++;
	while(ptr2<r.size())
		res.push_back(res.back()+r[ptr2]-r[ptr2-1]),ptr2++;
	Build_Convex(res);
	//not necessary to build convex again
}

bool chk(int u,int v){return v==Fa[u]?vis[u]:vis[v];}

void get_rt(int x,int fa,int sz)
{
	siz[x]=1;
	for(int _=T(x);_;_=T[_].nxt)
	{
		int v=T[_].v;
		if(v==fa||chk(x,v))
			continue;
		get_rt(v,x,sz);
		siz[x]+=siz[v];
	}
	int mx=max(sz-siz[x],siz[x]);
	if(mx<mxrt&&Fa[x]&&!vis[x])
		mxrt=mx,rt=x;
}

void dfs_build(int x,int fa)
{
	int lst=x;
	for(int _=pT(x);_;_=pT[_].nxt)
	{
		int v=pT[_].v;
		if(v==fa)
			continue;
		dfs_build(v,x);
		++cnt;
		Fa[cnt]=lst;
		T.add(cnt,lst,0,0);
		T.add(lst,cnt,0,0);
		Fa[v]=cnt;
		T.add(cnt,v,pT[_].a,pT[_].b);
		T.add(v,cnt,pT[_].a,pT[_].b);
		lst=cnt;
	}
}

void dfs(int x,int fa,pnt cur,vector<pnt> &V)
{
	V.push_back(cur);
	for(int _=T(x);_;_=T[_].nxt)
	{
		int v=T[_].v;
		if(v==fa||chk(x,v))
			continue;
		dfs(v,x,cur+(pnt){T[_].a,T[_].b},V);
	}
}

void solve(int x,int sz)
{
	vis[x]=1;
	vector<pnt> V1,V2,V3;
	for(int _=T(x);_;_=T[_].nxt)
	{
		int v=T[_].v;
		if(v==Fa[x])
			dfs(v,x,(pnt){T[_].a,T[_].b},V2);
		if(chk(x,v))
			continue;
		dfs(v,x,(pnt){T[_].a,T[_].b},V1);
	}
	V1.push_back((pnt){0,0});
	Build_Convex(V1);Build_Convex(V2);
	Minkowski_Sum(V1,V2,V3);
	for(auto p:V3)
		Global_Convex.push_back(p);
	rt=-1,mxrt=1<<30;
	get_rt(x,0,siz[x]);
	if(rt!=-1)
		solve(rt,siz[x]);
	rt=-1,mxrt=1<<30;
	get_rt(Fa[x],0,siz[Fa[x]]);
	if(rt!=-1)
		solve(rt,siz[Fa[x]]);
}

ll get_best(int x)
{
	int L=0,R=Global_Convex.size()-1;
	while(R-L>3)
	{
		int Mid1=(L+L+R)/3,Mid2=(L+R+R)/3;
		if(1ll*x*Global_Convex[Mid1].x+Global_Convex[Mid1].y>1ll*x*Global_Convex[Mid2].x+Global_Convex[Mid2].y)
			R=Mid2;
		else
			L=Mid1;
	}
	ll Ans=0;
	for(int i=L;i<=R;i++)
		Ans=max(Ans,1ll*x*Global_Convex[i].x+Global_Convex[i].y);
	return Ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	if(n==1)
	{
		for(int i=0;i<m;i++)
			printf("0%c","\n "[i+1!=m]);
		return 0;
	}
	for(int i=1,u,v,a,b;i<n;i++)
		scanf("%d%d%d%d",&u,&v,&a,&b),
		pT.add(u,v,a,b),pT.add(v,u,a,b);
	cnt=n;
	dfs_build(1,0);
	rt=-1,mxrt=1<<30;
	get_rt(1,0,cnt);
	if(rt!=-1)
		solve(rt,cnt);
	Build_Convex(Global_Convex);
	for(int i=0;i<m;i++)
		printf("%lld%c",get_best(i),"\n "[i+1!=m]);
}
