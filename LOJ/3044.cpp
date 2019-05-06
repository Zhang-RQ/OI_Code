#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int P=998244353;
const int INF=1<<30;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

int n,L,R,siz[MAXN],w[MAXN],son[MAXN],cnt,stk[MAXN*25],top,pos[MAXN],tot,rt[MAXN];
ll siz2[MAXN],val[MAXN],val2[MAXN],Ans[MAXN],tx[MAXN],ty[MAXN];
vector<int> T[MAXN];

struct node_t{
	int l,r,siz;
	ll tg,s;

	node_t(){tg=1;l=r=s=0;}
}t[MAXN*25];

int newnode()
{
	if(top)
		return t[stk[top]]=node_t(),stk[top--];
	return ++cnt;
}

void pushup(int x)
{
	t[x].s=Add(t[t[x].l].s,t[t[x].r].s);
	t[x].siz=t[t[x].l].siz+t[t[x].r].siz;
}

void apply_tag(int x,ll v)
{
	(t[x].s*=v)%=P;
	(t[x].tg*=v)%=P;
}

void pushdown(int x)
{
	if(t[x].tg!=1)
	{
		if(t[x].l)
			apply_tag(t[x].l,t[x].tg);
		if(t[x].r)
			apply_tag(t[x].r,t[x].tg);
		t[x].tg=1;
	}
}

void Insert(int &x,int l,int r,int p,ll dlt)
{
	if(!x)
		x=newnode();
	if(l==r)
		return Inc(t[x].s,dlt),t[x].siz=t[x].s>0,void();
	int mid=(l+r)>>1;pushdown(x);
	if(p<=mid) Insert(t[x].l,l,mid,p,dlt);
	else Insert(t[x].r,mid+1,r,p,dlt);
	pushup(x);
}

void Mul(int x,int l,int r,int cl,int cr,ll dlt)
{
	if(!x)
		return;
	if(cl<=l&&r<=cr)
		return apply_tag(x,dlt);
	int mid=(l+r)>>1;pushdown(x);
	if(cl<=mid)
		Mul(t[x].l,l,mid,cl,cr,dlt);
	if(cr>mid)
		Mul(t[x].r,mid+1,r,cl,cr,dlt);
	pushup(x);
}

void dfs(int x,int l,int r)
{
	if(!x)
		return;
	if(l==r)
		return ++tot,pos[tot]=l,val[tot]=t[x].s,void();
	int mid=(l+r)>>1;pushdown(x);
	dfs(t[x].l,l,mid);
	dfs(t[x].r,mid+1,r);
	stk[++top]=x;
}

ll Query(int x,int l,int r,int ql,int qr)
{
	if(ql>qr)
		return 0;
	if(ql<=l&&r<=qr)
		return t[x].s;
	int mid=(l+r)>>1;pushdown(x);
	if(qr<=mid)
		return Query(t[x].l,l,mid,ql,qr);
	if(ql>mid)
		return Query(t[x].r,mid+1,r,ql,qr);
	else
		return Add(Query(t[x].l,l,mid,ql,qr),Query(t[x].r,mid+1,r,ql,qr));
}

int Min_Con(int x,int y) //y -> x
{
	if(t[x].siz<t[y].siz)
		swap(x,y);
	tot=0;
	dfs(y,1,n);
	for(int i=1;i<=tot;i++)
		val2[i]=val[i]*Query(x,1,n,pos[i]+1,n)%P;
	for(int i=tot,s=0;i;i--)
	{
		Inc(s,val[i]);
		Mul(x,1,n,pos[i-1]+1,pos[i],s+1);
	}
	for(int i=1;i<=tot;i++)
		Insert(x,1,n,pos[i],Add(val[i],val2[i]));
	return x;
}

int Max_Con(int x,int y) //y -> x
{
	if(t[x].siz<t[y].siz)
		swap(x,y);
	ll sx=t[x].s,sy=t[y].s;
	tot=0;
	dfs(y,1,n);
	pos[tot+1]=n+1;
	for(int i=1;i<=tot;i++)
		val2[i]=val[i]*Query(x,1,n,1,pos[i]-1)%P;
	Mul(x,1,n,1,pos[1]-1,0);
	for(int i=1,s=0;i<=tot;i++)
	{
		Inc(s,val[i]);
		Mul(x,1,n,pos[i],pos[i+1]-1,s);
	}
	for(int i=1;i<=tot;i++)
		Insert(x,1,n,pos[i],val2[i]);
	Insert(x,1,n,n,Add(sx,sy));
	return x;
}

void pre_dfs(int x,int fa,int dep)
{
	w[x]=dep&1?-INF:INF;
	siz2[x]=1;
	for(int v:T[x])
	{
		if(v==fa)
			continue;
		pre_dfs(v,x,dep+1);
		siz[x]+=siz[v];
		siz2[x]=siz2[x]*siz2[v]%P;
		if((dep&1)&&(w[x]<w[v]))
			son[x]=v,w[x]=w[v];
		else if((~dep&1)&&(w[x]>w[v]))
			son[x]=v,w[x]=w[v];
	}
	if(T[x].size()==1)
		siz[x]=1,siz2[x]=2,w[x]=x;
}

void dfs(int x,int fa,int dep,int d)
{
	if(T[x].size()==1)
		Insert(rt[x],1,n,max(1,abs(d)),1);
	if(!d||((dep&1)&&d>0)||((~dep&1)&&d<0))
	{
		int tar=0,fir=1;
		if(d) tar=w[x]+d;
		else tar=dep&1?w[x]+1:w[x]-1;
		for(int v:T[x])
		{
			if(v==fa)
				continue;
			if(v==son[x])
				dfs(v,x,dep+1,d);
			else
				dfs(v,x,dep+1,tar-w[v]);
			if(fir) rt[x]=rt[v],fir=0;
			else rt[x]=Min_Con(rt[x],rt[v]);
		}
	}
	else
	{
		ll Mult=1;
		bool fir=1;
		for(int v:T[x])
		{
			if(v==fa)
				continue;
			if(((dep&1)&&w[v]<=w[x]+d)||((~dep&1)&&w[v]>=w[x]+d))
				(Mult*=siz2[v])%=P;
			else
			{
				dfs(v,x,dep+1,w[x]+d-w[v]);
				if(!fir) rt[x]=Max_Con(rt[x],rt[v]);
				else rt[x]=rt[v],fir=0;
			}
		}
		Mul(rt[x],1,n,1,n,Mult);
		Insert(rt[x],1,n,n,Mult-1);
	}
}

int main()
{
	scanf("%d%d%d",&n,&L,&R);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),T[u].push_back(v),T[v].push_back(u);
	pre_dfs(1,0,1);dfs(1,0,1,0);
	tot=0;dfs(rt[1],1,n);
	for(int i=1;i<=tot;i++)
		Ans[pos[i]]=val[i];
	for(int i=L;i<=R;i++)
		printf("%lld%c",Ans[i],"\n "[i!=R]);
}
