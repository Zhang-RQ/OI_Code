#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int MAXD=MAXN*26*5;
const int P=998244353;
const int MAXV=10000;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b) {a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b) {a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b) {a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b) {a-=b;return a<0?a+P:a;}

struct node_t {
	int l,r,fail,s,tag;
}t[MAXD];

char str[233];
int mx[MAXN][26];
int cnt,rt[MAXN][26],Ans[MAXN],nodeid[MAXN],cur,n,tot,dep[MAXN],dis[MAXN],stk[MAXN],top,fail[MAXN];
vector<tuple<int,int,int> > T[MAXN];
pair<int,int> stke[MAXN];

void pushup(int x) {t[x].s=Add(t[t[x].l].s,t[t[x].r].s);}

void apply_tag(int &x,int val,int len)
{
	int y=++cnt;
	t[y]=t[x];
	t[y].tag=val;
	t[y].s=1ll*val*len%P;
	x=y;
}

void pushdown(int &x,int l,int r)
{
	if(t[x].tag)
	{
		int mid=(l+r)>>1,y=x;
		x=++cnt;t[x]=t[y];
		apply_tag(t[x].l,t[x].tag,mid-l+1);
		apply_tag(t[x].r,t[x].tag,r-mid);
		t[x].tag=0;
	}
}

void Change_Fail(int &x,int l,int r,int p,int nfail)
{
	int y=++cnt;
	t[y]=t[x];x=y;
	if(l==r)
		return t[x].fail=nfail,void();
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(p<=mid)
		Change_Fail(t[x].l,l,mid,p,nfail);
	else
		Change_Fail(t[x].r,mid+1,r,p,nfail);
}

void Change_F(int &x,int l,int r,int cl,int cr,int dlt)
{
	int y=++cnt;
	t[y]=t[x];x=y;
	if(cl<=l&&r<=cr)
		return apply_tag(x,dlt,r-l+1);
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(cl<=mid)
		Change_F(t[x].l,l,mid,cl,cr,dlt);
	if(cr>mid)
		Change_F(t[x].r,mid+1,r,cl,cr,dlt);
	pushup(x);
}

int Query_Fail(int x,int l,int r,int p)
{
	if(!x)
		return 0;
	if(l==r)
		return t[x].fail;
	int mid=(l+r)>>1;
	if(p<=mid)
		return Query_Fail(t[x].l,l,mid,p);
	else
		return Query_Fail(t[x].r,mid+1,r,p);
}

int Query_F(int x,int l,int r,int ql,int qr)
{
	if(!x||ql>qr)
		return 0;
	if(ql<=l&&r<=qr)
		return t[x].s;
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(qr<=mid)
		return Query_F(t[x].l,l,mid,ql,qr);
	else if(ql>mid)
		return Query_F(t[x].r,mid+1,r,ql,qr);
	else
		return Add(Query_F(t[x].l,l,mid,ql,qr),Query_F(t[x].r,mid+1,r,ql,qr));
}

int S1(int x){return 1ll*x*(x+1)/2%P;}

void dfs(int x)
{
	for(auto e:T[x])
	{
		auto [v,c,l]=e;
		dep[v]=dep[x]+1;
		dis[v]=dis[x]+l;
		stk[++top]=v;
		stke[top]=make_pair(c,l);
		int premx=mx[x][c],prert=rt[x][c];
		if(!x)
		{
			Ans[v]=S1(l-1);
			mx[x][c]=l;
			dfs(v);
		}
		else
		{
			int nxt=Query_Fail(rt[x][c],1,MAXV,l);
			Ans[v]=Ans[x];
			if(stke[dep[nxt]+1]==make_pair(c,l))
				nxt=stk[dep[nxt]+1];
			int len=min(l,mx[x][c]);
			Inc(Ans[v],Query_F(rt[x][c],1,MAXV,1,l));
			Inc(Ans[v],S1(len));
			if(len<l&&stke[2].first==c)
			{
				int remain=l-len;
				Inc(Ans[v],1ll*stke[2].second*remain%P);
				if(!nxt)
					nxt=stk[2];
			}
			for(int i=0;i<26;i++)
				rt[v][i]=rt[nxt][i],
				mx[v][i]=mx[nxt][i];
			Change_F(rt[x][c],1,MAXV,1,l,dis[x]);
			Change_Fail(rt[x][c],1,MAXV,l,x);
			mx[x][c]=max(mx[x][c],l);
			dfs(v);
		}
		--top;
		mx[x][c]=premx;
		rt[x][c]=prert;
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,opt,x,c;i<=n;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%s",&x,str+1);
			c=str[1]-'a';
			int lst=cur;cur=++tot;
			T[lst].emplace_back(cur,c,x);
		}
		else
		{
			scanf("%d",&x);
			cur=nodeid[x];
		}
		nodeid[i]=cur;
	}
	dep[0]=1;dis[0]=0;
	stk[++top]=0;
	stke[top].first=-1;
	dfs(0);
	for(int i=1;i<=n;i++)
		printf("%d\n",Ans[nodeid[i]]);
}
