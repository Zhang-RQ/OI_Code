#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4E5+10;
const int P=1E9+7;

template<typename T1,typename T2>
	T1 Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;return a;}

template<typename T1,typename T2>
	T1 Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;return a;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int q,son[MAXN][26],par[MAXN],mx[MAXN],lst=1,rt=1,cnt=1,siz[MAXN];
ll Ans,lstdlt;
char str[MAXN];

struct node_t{
	node_t *son[2],*fa;
	int siz,tag,dlt; //dlt=mx-mx(fa)
	ll val,sdlt;

	void pushup()
	{
		val=1ll*dlt*siz%P;
		sdlt=dlt;
		if(son[0]!=nullptr)
			Inc(val,son[0]->val),Inc(sdlt,son[0]->sdlt);
		if(son[1]!=nullptr)
			Inc(val,son[1]->val),Inc(sdlt,son[1]->sdlt);
	}

	void apply_tag(int d)
	{
		siz+=d;tag+=d;
		val+=1ll*d*sdlt;
	}

	void pushdown()
	{
		if(tag)
		{
			if(son[0]!=nullptr)
				son[0]->apply_tag(tag);
			if(son[1]!=nullptr)
				son[1]->apply_tag(tag);
			tag=0;
		}
	}

	bool isrt() const
	{
		if(fa==nullptr)
			return true;
		return fa->son[0]!=this&&fa->son[1]!=this;
	}

	bool rson() const
	{
		if(fa==nullptr)
			return true;
		return fa->son[1]==this;
	}

	void pd(){if(!isrt()) fa->pd();pushdown();}
}Pool[MAXN],*cur=Pool,*refn[MAXN];

void rotate(node_t *x)
{
	node_t *y=x->fa,*z=y->fa;
	bool rsx=x->rson(),rsy=y->rson();
	if(!y->isrt())
		z->son[rsy]=x;
	y->son[rsx]=x->son[!rsx];
	x->son[!rsx]=y;
	if(y->son[rsx]!=nullptr)
		y->son[rsx]->fa=y;
	y->fa=x;x->fa=z;
	y->pushup();x->pushup();
}

void splay(node_t *x)
{
	x->pd();
	while(!x->isrt())
	{
		if(!x->fa->isrt())
			rotate(x->rson()^x->fa->rson()?x:x->fa);
		rotate(x);
	}
}

void access(node_t *x)
{
	for(node_t *y=nullptr;x!=nullptr;y=x,x=x->fa)
		splay(x),x->son[1]=y,x->pushup();
}

void append(int x)
{
	int np=++cnt,p=lst;
	refn[np]=++cur;
	mx[np]=mx[p]+1;
	while(p&&!son[p][x])
		son[p][x]=np,p=par[p];
	if(!p) par[np]=rt;
	else
	{
		int q=son[p][x];
		if(mx[q]==mx[p]+1)
			par[np]=q;
		else
		{
			int nq=++cnt;
			refn[q]->pd();
			refn[nq]=++cur;
			refn[nq]->siz=refn[q]->siz;
			siz[nq]=siz[q];
			mx[nq]=mx[p]+1;
			par[nq]=par[q];
			par[q]=par[np]=nq;
			while(p&&son[p][x]==q)
				son[p][x]=nq,p=par[p];
			memcpy(son[nq],son[q],sizeof son[q]);
			
			node_t *z=refn[par[nq]];
			access(refn[q]);splay(refn[q]);
			refn[q]->dlt=mx[q]-mx[nq];
			refn[nq]->dlt=mx[nq]-mx[par[nq]];
			refn[q]->pushup();
			splay(z);
			z->son[1]=refn[nq];
			refn[nq]->son[1]=refn[q];
			refn[q]->fa=refn[nq];
			refn[nq]->fa=z;
			refn[nq]->pushup();
			z->pushup();
		}
	}
	lst=np;
	refn[np]->fa=refn[par[np]];
	refn[np]->dlt=mx[np]-mx[par[np]];
	access(refn[np]);splay(refn[np]);
	Inc(Ans,Inc(lstdlt,refn[np]->val));
	refn[np]->apply_tag(1);
}

int main()
{
	refn[rt]=++cur;
	scanf("%d",&q);
	scanf("%s",str+1);
	for(int i=1;i<=q;i++)
	{
		append(str[i]-'a');
		printf("%lld\n",Ans);
	}
}
