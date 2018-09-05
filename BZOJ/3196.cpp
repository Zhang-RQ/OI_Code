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

const int MAXN=5E4+10;

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==(x))

int rt[MAXN<<2],val[MAXN],n,m,nds[MAXN],tot;

namespace Splay{
	struct __node{
		int son[2],fa,siz,v;
		int tims;
		inline void clear(){son[0]=son[1]=fa=siz=v=tims=0;}
	}t[MAXN<<5];

	int cnt;
	queue<int> trash;

	inline int nd()
	{
		if(!trash.empty())
		{
			int x=trash.front();trash.pop();
			t[x].clear();
			return x;
		}
		t[++cnt].clear();
		return cnt;
	}

	inline void pushup(int x) {t[x].siz=t[x].tims+t[ls(x)].siz+t[rs(x)].siz;}

	inline void rotate(int x,int p)
	{
		int y=fa(x),z=fa(y);
		bool rsx=rson(x),rsy=rson(y);
		if(z) t[z].son[rsy]=x;
		else rt[p]=x;
		t[y].son[rsx]=t[x].son[!rsx];
		t[x].son[!rsx]=y;
		fa(t[y].son[rsx])=y;
		fa(y)=x;fa(x)=z;
		pushup(y);
	}

	inline void splay(int x,int p)
	{
		while(x!=rt[p])
		{
			if(fa(x)!=rt[p]) rotate((rson(x)^rson(fa(x))?x:fa(x)),p);
			rotate(x,p);
		}
		pushup(x);
	}

	inline int find(int x,int val)
	{
		if(t[x].v==val) return x;
		if(t[x].v<val) return rs(x)?find(rs(x),val):x;
		return ls(x)?find(ls(x),val):x;
	}

	inline void insert(int &x,int val,int p)
	{
		if(!x)
		{
			x=nd();
			t[x].v=val;
			t[x].tims=t[x].siz=1;
			return;
		}
		int y=find(x,val);
		if(t[y].v==val)
		{
			splay(y,p);
			t[y].tims++;
			t[y].siz++;
			return;
		}
		int z=nd();
		t[y].son[t[y].v<val]=z;
		t[z].v=val;fa(z)=y;
		t[z].siz=t[z].tims=1;
		while(y) t[y].siz++,y=fa(y);
	}

	inline int __pred(int x,int p) //node_num
	{
		splay(x,p);
		if(!ls(x)) return -1;
		x=ls(x);
		while(rs(x)) x=rs(x);
		return x;
	}

	inline int pred(int x,int v,int p)
	{
		int y=find(x,v);
		if(t[y].v<v) return t[y].v;
		else return ((y=__pred(y,p))==-1)?0:t[y].v;
	}

	inline int __succ(int x,int p) //node_num
	{
		splay(x,p);
		if(!rs(x)) return -1;
		x=rs(x);
		while(ls(x)) x=ls(x);
		return x;
	}

	inline int succ(int x,int v,int p)
	{
		int y=find(x,v);
		if(t[y].v>v) return t[y].v;
		else return ((y=__succ(y,p))==-1)?1<<30:t[y].v;
	}

	inline void del(int x,int val,int p)
	{
		int y=find(x,val);
		if(t[y].v!=val) return assert(0);
		splay(y,p);
		if(t[y].tims>1) return --t[y].tims,void();
		if(!ls(y))
		{
			rt[p]=rs(y);
			fa(rs(y))=0;
			t[y].clear();
			trash.push(y);
			return;
		}
		int z=__pred(y,p);
		fa(ls(y))=0;
		rt[p]=ls(y);splay(z,p);
		t[z].son[1]=t[y].son[1];
		fa(z)=0;fa(t[z].son[1])=z;
		pushup(z);rt[p]=z;
		t[y].clear();
		trash.push(y);
	}

	int __kth(int x,int k)//node_num
	{
		if(t[ls(x)].siz<k&&k<=t[ls(x)].siz+t[x].tims) return x;
		if(t[ls(x)].siz>k) return __kth(ls(x),k);
		return __kth(rs(x),k-t[ls(x)].siz-t[x].tims);
	}

	int kth(int x,int k){return t[__kth(x,k)].v;} //val

	int rnk(int x,int val,int p)
	{
		int y=find(x,val);
		splay(y,p);
		if(t[y].v>=val) return t[ls(y)].siz;
		return t[ls(y)].siz+t[y].tims;
	}
}

using namespace Splay;

void build(int x,int l,int r)
{
	for(int i=l;i<=r;i++) insert(rt[x],val[i],x);
	if(l==r) return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}

void change(int x,int l,int r,int pos,int _v,int v)
{
	del(rt[x],_v,x);insert(rt[x],v,x);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) change(x<<1,l,mid,pos,_v,v);
	else change(x<<1|1,mid+1,r,pos,_v,v);
}

void get_nodes(int x,int l,int r,int ql,int qr)
{
	if(x==1) tot=0;
	if(ql<=l&&r<=qr) return nds[++tot]=x,void();
	int mid=(l+r)>>1;
	if(ql<=mid) get_nodes(x<<1,l,mid,ql,qr);
	if(qr>mid) get_nodes(x<<1|1,mid+1,r,ql,qr);
}

inline int __Rank(int val)
{
	int Ret=0;
	for(int i=1;i<=tot;i++)
		Ret+=rnk(rt[nds[i]],val,nds[i]);
	return Ret+1;
}

inline int Rank(int L,int R,int val)
{
	get_nodes(1,1,n,L,R);
	return __Rank(val);
}

inline int Kth(int L,int R,int k)
{
	get_nodes(1,1,n,L,R);
	int l=0,r=1e8+10,Ret=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		// printf("mid=%d Rank=%d\n",mid,__Rank(mid));
		if(__Rank(mid)<=k) l=mid+1,Ret=mid;
		else r=mid-1;
	}
	return Ret;
}

inline int Pred(int L,int R,int val)
{
	get_nodes(1,1,n,L,R);
	int Ret=0;
	for(int i=1;i<=tot;i++)
		Ret=max(Ret,pred(rt[nds[i]],val,nds[i]));
	return Ret;
}

inline int Succ(int L,int R,int val)
{
	get_nodes(1,1,n,L,R);
	int Ret=1<<30;
	for(int i=1;i<=tot;i++)
		Ret=min(Ret,succ(rt[nds[i]],val,nds[i]));
	return Ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	build(1,1,n);
	for(int i=1,opt,l,r,k;i<=m;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",Rank(l,r,k));
		}
		else if(opt==2)
		{
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",Kth(l,r,k));
		}
		else if(opt==3)
		{
			scanf("%d%d",&l,&k);
			change(1,1,n,l,val[l],k);
			val[l]=k;
		}
		else if(opt==4)
		{
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",Pred(l,r,k));
		}
		else if(opt==5)
		{
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",Succ(l,r,k));
		}
	}
}