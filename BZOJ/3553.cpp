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

const int MAXN=5E5+10;

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==(x))

struct __node{
	bool p[2];
	int v,son[2],fa,tag;
}t[MAXN];

int n,m,cnt[MAXN],mp[MAXN*3],st[MAXN*3],tot[MAXN],Ans;
int fafa;
queue<int> q;

inline bool isroot(int x){return ls(fa(x))!=x&&rs(fa(x))!=x;}

inline void pushup(int x)
{
	t[x].p[0]=t[x].v==1;t[x].p[1]=t[x].v==2;
	if(ls(x)) t[x].p[0]&=t[ls(x)].p[0],t[x].p[1]&=t[ls(x)].p[1];
	if(rs(x)) t[x].p[0]&=t[rs(x)].p[0],t[x].p[1]&=t[rs(x)].p[1];
}

inline void pushdown(int x)
{
	if(t[x].tag==1)
	{
		t[rs(x)].tag=t[ls(x)].tag=t[x].tag;
		if(ls(x)) t[ls(x)].v=1,t[ls(x)].p[0]=1,t[ls(x)].p[1]=0;
		if(rs(x)) t[rs(x)].v=1,t[rs(x)].p[0]=1,t[rs(x)].p[1]=0;
		t[x].tag=0;
	}
	if(t[x].tag==2)
	{
		t[rs(x)].tag=t[ls(x)].tag=t[x].tag;
		if(ls(x)) t[ls(x)].v=2,t[ls(x)].p[0]=0,t[ls(x)].p[1]=1;
		if(rs(x)) t[rs(x)].v=2,t[rs(x)].p[0]=0,t[rs(x)].p[1]=1;
		t[x].tag=0;
	}
}

void pd(int x) {if(!isroot(x)) pd(fa(x));pushdown(x);}

inline void rotate(int x)
{
	int y=fa(x),z=fa(y);
	bool rsx=rson(x),rsy=rson(y);
	if(!isroot(y)) t[z].son[rsy]=x;
	t[y].son[rsx]=t[x].son[!rsx];
	t[x].son[!rsx]=y;
	fa(t[y].son[rsx])=y;
	fa(y)=x;fa(x)=z;
	pushup(y);pushup(x);
}

inline void splay(int x)
{
	pd(x);
	while(!isroot(x))
	{
		if(!isroot(fa(x))) rotate(rson(x)==rson(fa(x))?fa(x):x);
		rotate(x);
	}
}

inline void access(int x)
{
	for(int y=0;x;y=x,x=fa(x))
		splay(x),rs(x)=y,pushup(x);
}

int find(int x,int tp)
{
	pushdown(x);
	if(!t[rs(x)].p[tp-1]) return find(rs(x),tp);
	if(t[x].v!=tp) return x;
	return find(ls(x),tp);
}

inline void setv(int x,int v)
{
	if(!x) return;
	t[x].p[v-1]=1;
	t[x].p[(v-1)^1]=0;
	t[x].v=t[x].tag=v;
}

inline void inc(int x)
{
	access(x);splay(x);
	if(x==1||t[x].v!=1) return ++t[x].v,pushup(x),void();
	if(t[x].p[0]) return setv(x,2),void();
	int y=find(x,1);
	splay(y);setv(rs(y),2);pushup(y);
	t[y].v++;pushup(y);
}

inline void dec(int x)
{
	access(x);splay(x);
	if(x==1||t[x].v!=2) return --t[x].v,pushup(x),void();
	if(t[x].p[1]) return setv(x,1),void();
	int y=find(x,2);
	splay(y);setv(rs(y),1);pushup(y);
	t[y].v--;pushup(y);
}

char B[1<<26],*S=B;

inline int F()
{
    for(;*S<'-';S++);
    int x=*S++-'0';
    for(;*S>='0';x=(x<<3)+(x<<1)+*S++-'0');
    return x;
}

int main()
{
	fread(B,1,1<<25,stdin);
	t[0].p[0]=t[0].p[1]=1;
	n=F();
	for(int i=1,x1,x2,x3;i<=n;i++)
	{
		x1=F();x2=F();x3=F();
		if(x1<=n) fa(x1)=i;
		else mp[x1]=i,++tot[i];
		if(x2<=n) fa(x2)=i;
		else mp[x2]=i,++tot[i];
		if(x3<=n) fa(x3)=i;
		else mp[x3]=i,++tot[i];
		if(tot[i]==3) q.push(i);
	}
	for(int i=n+1;i<=3*n+1;i++)
	{
		st[i]=F();
		if(st[i]) ++cnt[mp[i]];
	}
	while(!q.empty()) 
	{
		int x=q.front();q.pop();
		if(cnt[x]>=2) cnt[fa(x)]++;
		if(++tot[fa(x)]==3) q.push(fa(x));
	}
	for(int i=1;i<=n;i++) t[i].v=cnt[i],t[i].p[0]=t[i].v==1,t[i].p[1]=t[i].v==2;
	Ans=t[1].v>=2;
	m=F();
	for(int i=1,x;i<=m;i++)
	{
		x=F();
		st[x]^=1;
		if(st[x]) inc(mp[x]);
		else dec(mp[x]);
		splay(1);
		printf("%d\n",t[1].v>=2);
	}
}