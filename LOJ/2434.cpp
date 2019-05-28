#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

struct FastIO{
    static const int S=1e7;
    int wpos;
    char wbuf[S];
    FastIO():wpos(0){}

    inline int xchar()
    {
        static char buf[S];
        static int len=0,pos=0;
        if(pos==len)
            pos=0,len=fread(buf,1,S,stdin);
        return buf[pos++];
    }

    inline int operator () ()
    {
        int c=xchar(),x=0,ng=0;
        while (!isdigit(c)) ng|=(c=='-'),c=xchar();
        for(;isdigit(c);c=xchar()) x=x*10+c-'0';
        return ng?-x:x;
    }

    inline ll operator ! ()
    {
        int c=xchar(),ng=0;ll x=0;
        while(!isdigit(c)) ng|=(c=='-'),c=xchar();
        for(;isdigit(c);c=xchar()) x=x*10+c-'0';
        return ng?-x:x;
    }

    inline void wchar(int x)
    {
        if(wpos==S) fwrite(wbuf,1,S,stdout),wpos=0;
        wbuf[wpos++]=x;
    }

    inline void operator () (ll x)
    {
        if (x<0) wchar('-'),x=-x;
        char s[24];
        int n=0;
        while(x||!n) s[n++]='0'+x%10,x/=10;
        while(n--) wchar(s[n]);
        wchar('\n');
    }

    inline void space(ll x)
    {
        if (x<0) wchar('-'),x=-x;
        char s[24];
        int n=0;
        while(x||!n) s[n++]='0'+x%10,x/=10;
        while(n--) wchar(s[n]);
        wchar(' ');
    }

    inline void nextline() {wchar('\n');}

    ~FastIO() {if(wpos) fwrite(wbuf,1,wpos,stdout),wpos=0;}
}io;

const int MAXN=4E5+10;

struct node_t{
	node_t *son[2],*fa;
	ll val,siz,lsiz,tsiz,dltA; //tsiz is validate iff *this is root
}pool[MAXN],*cur=pool;

node_t *refn[MAXN];
int n,m;
ll Ans,siz[MAXN];
vector<int> T[MAXN];

void pushup(node_t *x)
{
	x->siz=x->val+x->lsiz;
	x->tsiz=x->val+x->lsiz;
	if(x->son[0]!=nullptr)
		x->siz+=x->son[0]->siz;
	if(x->son[1]!=nullptr)
		x->siz+=x->son[1]->siz,x->tsiz+=x->son[1]->siz;
}

bool isrt(node_t *x)
{
	if(x->fa!=nullptr)
		return x->fa->son[0]!=x&&x->fa->son[1]!=x;
	else
		return true;
}

bool rson(node_t *x)
{
	if(x->fa!=nullptr)
		return x->fa->son[1]==x;
	else
		return false;
}

void Rotate(node_t *x)
{
	node_t *y=x->fa,*z=y->fa;
	bool rsx=rson(x),rsy=rson(y);
	if(!isrt(y))
		z->son[rsy]=x;
	y->son[rsx]=x->son[!rsx];
	x->son[!rsx]=y;
	y->fa=x;x->fa=z;
	if(y->son[rsx]!=nullptr)
		y->son[rsx]->fa=y;
	pushup(y);pushup(x);
}

void Splay(node_t *x)
{
	while(!isrt(x))
	{
		if(!isrt(x->fa))
			Rotate(rson(x)^rson(x->fa)?x:x->fa);
		Rotate(x);
	}
}

void Access(node_t *x,ll dlt)
{
	Splay(x);
	x->val+=dlt;x->tsiz+=dlt;x->siz+=dlt;
	Ans-=x->dltA;
	if(2*x->val>x->tsiz)
	{
		x->dltA=2*(x->tsiz-x->val);
		x->lsiz+=(x->son[1]==nullptr)?0:x->son[1]->siz;
		x->son[1]=nullptr;
	}
	else if(x->son[1]!=nullptr)
	{
		if(2*x->son[1]->siz>x->tsiz)
			x->dltA+=2*dlt;
		else
			x->dltA=x->tsiz-1,x->lsiz+=x->son[1]->siz,x->son[1]=nullptr;
	}
	else
		x->dltA=x->tsiz-1;
	Ans+=x->dltA;
	pushup(x);
	node_t *y=x;x=x->fa;
	for(;x!=nullptr;y=x,x=x->fa)
	{
		Splay(x);
		x->tsiz+=dlt;
		x->lsiz+=dlt;
		x->siz+=dlt;
		Ans-=x->dltA;
		if(2*y->siz>x->tsiz)
		{
			x->dltA=2*(x->tsiz-y->siz);
			if(x->son[1]!=nullptr)
				x->lsiz+=x->son[1]->siz;
			x->son[1]=y;
			x->lsiz-=x->son[1]->siz;
		}
		else if(x->son[1]!=nullptr)
		{
			if(2*x->son[1]->siz>x->tsiz)
				x->dltA+=2*dlt;
			else
			{
				x->lsiz+=x->son[1]->siz;
				x->dltA=x->tsiz-1;
				x->son[1]=nullptr;
			}
		}
		else
		{
			if(2*x->val>x->tsiz)
				x->dltA+=2*dlt;
			else
				x->dltA=x->tsiz-1;
		}
		Ans+=x->dltA;
		pushup(x);
	}
}

void dfs(int x,int fa)
{
	refn[x]=++cur;
	refn[x]->fa=refn[fa];
	refn[x]->val=siz[x];
	ll mx=siz[x];
	for(int v:T[x])
		if(v!=fa)
		{
			dfs(v,x);
			siz[x]+=siz[v];
			refn[x]->lsiz+=siz[v];
		}
	for(int v:T[x])
		if(v!=fa&&2*siz[v]>siz[x])
			refn[x]->son[1]=refn[v],refn[x]->lsiz-=siz[v];
	if(refn[x]->son[1]!=nullptr)
		Ans+=(refn[x]->dltA=2*(siz[x]-refn[x]->son[1]->siz));
	else
	{
		if(2*mx>siz[x])
			Ans+=(refn[x]->dltA=2*(siz[x]-mx));
		else
			Ans+=(refn[x]->dltA=siz[x]-1);
	}
	refn[x]->siz=siz[x];
	pushup(refn[x]);
}

int main()
{
	n=io();m=io();
	for(int i=1;i<=n;i++)
		siz[i]=io();
	for(int i=1,u,v;i<n;i++)
	{
		u=io();v=io();
		T[u].push_back(v);
		T[v].push_back(u);
	}
	dfs(1,0);
	io(Ans);
	for(int i=1,u,d;i<=m;i++)
	{
		u=io();d=io();
		Access(refn[u],d);
		io(Ans);
	}
}
