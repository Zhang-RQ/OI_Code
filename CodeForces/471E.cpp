#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4E5+10;

namespace Segment_tree{
	int t[MAXN<<4];

	void insert(int x,int l,int r,int p,int v)
	{
		t[x]+=v;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(p<=mid) insert(x<<1,l,mid,p,v);
		else insert(x<<1|1,mid+1,r,p,v);
	}
	
	int pred(int x,int l,int r,int p)
	{
		if(!t[x]) return 0;
		if(l==r) return t[x]?l:0;
		int mid=(l+r)>>1;
		if(p>mid)
		{
			int ret=pred(x<<1|1,mid+1,r,p);
			return ret?ret:pred(x<<1,l,mid,p);
		}
		else return pred(x<<1,l,mid,p);
	}
	

	int succ(int x,int l,int r,int p)
	{
		if(!t[x]) return 0;
		if(l==r) return t[x]?l:0;
		int mid=(l+r)>>1;
		if(p<=mid)
		{
			int ret=succ(x<<1,l,mid,p);
			return ret?ret:succ(x<<1|1,mid+1,r,p);
		}
		else return succ(x<<1|1,mid+1,r,p);
	}

	int query(int x,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr) return t[x];
		int mid=(l+r)>>1;
		if(qr<=mid) return query(x<<1,l,mid,ql,qr);
		else if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
		else return query(x<<1,l,mid,ql,qr)+query(x<<1|1,mid+1,r,ql,qr);
	}
}
using namespace Segment_tree;

struct Opt{
	int tp,l,r,x,id; //tp=1 insert y=l,tp=2 swipe [l,r],tp=3 erase y=l

	bool operator < (const Opt &rhs) const {return x<rhs.x||(x==rhs.x&&tp<rhs.tp);}
}op[MAXN*2];

struct Line{
	int l,r,id;

	bool operator < (const Line &rhs) const {return l<rhs.l||(l==rhs.l&&r<rhs.r);}
};

int fa[MAXN],siz[MAXN],toty,yval[MAXN*2],n,totop;
ll val[MAXN],Ans;
set<Line> S;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

bool merge(int x,int y)
{
	x=find(x),y=find(y);
	if(x==y) return false;
	if(siz[x]<siz[y]) swap(x,y);
	siz[x]+=siz[y];
	val[x]+=val[y];
	fa[y]=x;
	Ans=max(Ans,val[x]);
	return true;
}

set<Line>::iterator Find_Inc(int k)
{
	if(!S.size()) return S.end();
	set<Line>::iterator it=S.lower_bound((Line){k,0,0});
	if(it!=S.end()&&it->l==k) return it;
	if(it==S.begin()) return S.end();
	--it;
	if(it->l<=k&&k<=it->r) return it;
	return S.end();
}

void insert_horizontal(int k,int id)//insert y=k
{
	insert(1,1,toty,k,1);
	if(!S.size()) return S.insert((Line){k,k,id}),void();
	set<Line>::iterator it=Find_Inc(k);
	if(it==S.end()) S.insert((Line){k,k,id});
	else
	{
		int L=it->l,pre=pred(1,1,toty,k-1),nxt=succ(1,1,toty,k+1),R=it->r,oid=it->id;
		S.erase(it);
		S.insert((Line){L,pre,oid});
		S.insert((Line){k,k,id});
		S.insert((Line){nxt,R,oid});
	}
}

void erase_horizontal(int k)//erase y=k
{
	insert(1,1,toty,k,-1);
	set<Line>::iterator it=Find_Inc(k);
	if(k==it->l)
	{
		int nxt=succ(1,1,toty,k+1),R=it->r,id=it->id;
		S.erase(it);
		if(nxt&&nxt<=R) S.insert((Line){nxt,R,id});
		return;
	}
	if(k==it->r)
	{
		int pre=pred(1,1,toty,k-1),L=it->l,id=it->id;
		S.erase(it);
		if(pre&&L<=pre) S.insert((Line){L,pre,id});
		return;
	}
}

void Swipe(int L,int R)
{
	if(!S.size()) return;
	int len=yval[R]-yval[L]+1;
	L=succ(1,1,toty,L);
	R=pred(1,1,toty,R);
	if(L>R||R==0||L==0) return;
	set<Line>::iterator it=Find_Inc(L);
	int lstrt=0,LL=it->l,RR=it->r;
	while(it!=S.end()&&it->l<=R)
	{
		if(lstrt) merge(lstrt,it->id);
		lstrt=find(it->id);
		RR=it->r;
		set<Line>::iterator tit=it;
		++it;
		S.erase(tit);
	}
	val[lstrt]+=len-query(1,1,toty,L,R);
	Ans=max(val[lstrt],Ans);
	S.insert((Line){LL,RR,lstrt});
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		fa[i]=i,siz[i]=1;
	for(int i=1,x1,y1,x2,y2;i<=n;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		yval[++toty]=y1;yval[++toty]=y2;
		if(x1==x2) op[++totop]=(Opt){2,y1,y2,x1,0},Ans=max(Ans,(ll)y2-y1+1);
		else
		{
			val[i]=x2-x1+1;
			op[++totop]=(Opt){1,y1,y1,x1,i};
			op[++totop]=(Opt){3,y1,y1,x2,i};
			Ans=max(Ans,val[i]);
		}
	}
	sort(yval+1,yval+1+toty);
	toty=unique(yval+1,yval+1+toty)-yval-1;
	for(int i=1;i<=totop;i++)
		op[i].l=lower_bound(yval+1,yval+1+toty,op[i].l)-yval,
		op[i].r=lower_bound(yval+1,yval+1+toty,op[i].r)-yval;
	sort(op+1,op+1+totop);
	for(int i=1;i<=totop;i++)
	{
		if(op[i].tp==1) insert_horizontal(op[i].l,op[i].id);
		else if(op[i].tp==2) Swipe(op[i].l,op[i].r);
		else erase_horizontal(op[i].l);
	}
	printf("%lld\n",Ans-1);
}
