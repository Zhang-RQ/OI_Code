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

const int MAXN=4E5+10;
const int MAXL=8E5+10;
const int MAXM=2.5E6+10;
const ll INF=1ll<<60;

struct _edge{int v,w,nxt;};

struct Graph{
	_edge Edge[MAXL<<1];
	int head[MAXL],cnt_e;

	int& operator () (int i){return head[i];}
	_edge& operator [] (int i){return Edge[i];}

	void add(int u,int v,int w)
	{
		Edge[++cnt_e].w=w;
		Edge[cnt_e].v=v;
		Edge[cnt_e].nxt=head[u];
		head[u]=cnt_e;
	}
}T1,T2,T1t;

struct Tree{
    Graph* t;
    int pos[MAXL],st[MAXL<<1][22],lca[MAXL<<1][22],dft,dep[MAXL<<1],lg2[MAXL<<1];
    ll dis[MAXL];

    Tree(Graph* TP=nullptr) {t=TP;}

    void dfs(int x,int fa)
    {
        st[pos[x]=++dft][0]=dep[x];
        lca[dft][0]=x;
        for(int i=(*t)(x);i;i=(*t)[i].nxt)
        {
            int v=(*t)[i].v;
            if(v==fa) continue;
            dis[v]=dis[x]+(*t)[i].w;dep[v]=dep[x]+1;
            dfs(v,x);
            st[++dft][0]=dep[x];
            lca[dft][0]=x;
        }
    }

    void init()
    {
        dfs(1,0);
        for(int i=2;i<=dft;i++)
            lg2[i]=lg2[i>>1]+1;
        for(int j=1;j<=lg2[dft];j++)
            for(int i=1;i+(1<<j)-1<=dft;i++)
                if(st[i][j-1]<st[i+(1<<(j-1))][j-1])
                    st[i][j]=st[i][j-1],lca[i][j]=lca[i][j-1];
                else st[i][j]=st[i+(1<<(j-1))][j-1],lca[i][j]=lca[i+(1<<(j-1))][j-1];
    }

    int LCA(int x,int y)
    {
        x=pos[x],y=pos[y];
        if(x>y) swap(x,y);
        int len=lg2[y-x+1];
        return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
    }

    ll DIS(int x,int y)
    {
        return dis[x]+dis[y]-2*dis[LCA(x,y)];
    }
}t1(&T1t);

int n,tn,STK[MAXM],TOP;
int Fa[MAXL],siz[MAXL],vis[MAXL],rt,mx_rt,pnt[MAXL];//T1t pnt[x]=>dvt_pnt
int anc[MAXM],son[MAXM][2],cnt,son_pnt[MAXM],Rt[MAXL],ref[MAXM],Fad[MAXM],RT; //dvt
ll lmx[MAXM],rmx[MAXM];//dvt
ll Ans=-INF;

bool chk(int x,int v){return (Fa[x]==v&&vis[x])||(Fa[x]!=v&&vis[v]);}

void find_rt(int x,int fa,int sz)
{
	siz[x]=1;
	for(int i=T1t(x);i;i=T1t[i].nxt)
	{
		int v=T1t[i].v;
		if(v==fa||chk(x,v)) continue;
		find_rt(v,x,sz);
		siz[x]+=siz[v];
	}
	int mx=max(siz[x],sz-siz[x]);
	if(Fa[x]&&!vis[x]&&mx<mx_rt) mx_rt=mx,rt=x;
}

int new_node()
{
	int ret=0;
	if(!TOP) ret=++cnt;
	else ret=STK[TOP--];
	lmx[ret]=rmx[ret]=-INF;
	son[ret][0]=son[ret][1]=anc[ret]=ref[ret]=0;
	return ret;
}

int construct(int x)
{
	vis[x]=1;
	int nd=new_node();
	son_pnt[nd]=x;
	pnt[x]=pnt[Fa[x]]=nd;
	mx_rt=1<<30;rt=0;

	for(int i=T1t(x);i;i=T1t[i].nxt)
		if(T1t[i].v==Fa[x]) {Fad[nd]=T1t[i].w;break;}

	find_rt(Fa[x],x,siz[Fa[x]]);
	if(rt) son[nd][0]=construct(rt),anc[son[nd][0]]=nd;
	
	mx_rt=1<<30;rt=0;
	find_rt(x,0,siz[x]);
	if(rt) son[nd][1]=construct(rt),anc[son[nd][1]]=nd;

	return nd;
}

int merge(int x,int y,ll dlt)
{
	if(!x||!y) return x|y;
	Ans=max(Ans,((lmx[x]+rmx[y]+Fad[ref[x]])>>1)-dlt);
	Ans=max(Ans,((rmx[x]+lmx[y]+Fad[ref[x]])>>1)-dlt);
	lmx[x]=max(lmx[x],lmx[y]);
	son[x][0]=merge(son[x][0],son[y][0],dlt);
	rmx[x]=max(rmx[x],rmx[y]);
	son[x][1]=merge(son[x][1],son[y][1],dlt);
	STK[++TOP]=y;
	return x;
}

int insert(int p)
{
	int t=new_node(),y=pnt[p];ref[t]=y;
	if(son_pnt[y]==p) rmx[t]=t1.dis[p];
	else lmx[t]=t1.dis[p];
	while(anc[y])
	{
		int x=new_node(),ty=y;y=anc[y];ref[x]=y;
		if(son[y][1]==ty) son[x][1]=t,rmx[x]=t1.DIS(son_pnt[y],p)+t1.dis[p];
		else son[x][0]=t,lmx[x]=t1.DIS(Fa[son_pnt[y]],p)+t1.dis[p];
		t=x;
	}
	return t;
}

void dfs_b(int x,int fa)
{
	int lst=x;
	for(int i=T1(x);i;i=T1[i].nxt)
	{
		int v=T1[i].v;
		if(v==fa) continue;
		int tv=++n;Fa[tv]=lst;Fa[v]=tv;
		T1t.add(lst,tv,0);T1t.add(tv,lst,0);
		T1t.add(tv,v,T1[i].w);T1t.add(v,tv,T1[i].w);
		lst=tv;
	}
	for(int i=T1(x);i;i=T1[i].nxt)
		if(T1[i].v!=fa) dfs_b(T1[i].v,x);
}

void dfs(int x,int fa,ll Dep)
{
	Ans=max(Ans,t1.dis[x]-Dep);
	for(int i=T2(x);i;i=T2[i].nxt)
	{
		int v=T2[i].v;
		if(v==fa) continue;
		dfs(v,x,Dep+T2[i].w);
	}
	Rt[x]=insert(x);
	for(int i=T2(x);i;i=T2[i].nxt)
	{
		int v=T2[i].v;
		if(v==fa) continue;
		Rt[x]=merge(Rt[x],Rt[v],Dep);
	}
}

int main()
{	
	scanf("%d",&n);tn=n;
	for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),T1.add(u,v,w),T1.add(v,u,w);
	for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),T2.add(u,v,w),T2.add(v,u,w);
	dfs_b(1,0);t1.init();
	mx_rt=1<<30;rt=0;
	find_rt(1,0,n);
	RT=construct(rt);
	dfs(1,0,0);
	printf("%lld\n",Ans);
}