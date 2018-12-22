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

const int MAXN=200100;

struct blk{
	int l,r,c;
	blk(int _l=0,int _r=0,int _c=0)	{l=_l;r=_r;c=_c;}
	bool operator < (const blk &rhs) const {return l<rhs.l;}
};

struct opt{
	int x,y,tp,v,id; //opt=1 change,opt=2 query
	opt(){}
	opt(int _x,int _y,int _tp,int _v,int _id){x=_x;y=_y;tp=_tp;v=_v;id=_id;}
	bool operator <(const opt &rhs) const {return x<rhs.x||(x==rhs.x&&tp==1);}
}e[MAXN*15],te[MAXN*8];

int n,m,pre[MAXN],Ans[MAXN],t[MAXN],Cnt,qcnt,ecnt,top;
pair<int,int> stk[MAXN*8];
map<int,int> M;
set<int> S;
set<blk> glo,s[MAXN];
set<blk>:: iterator it,it1;

inline void add(int x,int v)
{
	x+=10;assert(x>0);
	for(int i=x;i<=n+10;i+=i&(-i))
		t[i]+=v;
}

inline int query(int x)
{
	x+=10;assert(x>0);
	int Ret=0;
	for(int i=x;i;i-=i&(-i))
		Ret+=t[i];
	return Ret;
}

void split(int p)
{
	it=glo.lower_bound(blk(p));
	if(it->l==p) return;
	--it;blk t=*it;
	glo.erase(it);
	s[t.c].erase(t);
	glo.insert(blk(t.l,p-1,t.c));
	s[t.c].insert(blk(t.l,p-1,t.c));
	glo.insert(blk(p,t.r,t.c));
	s[t.c].insert(blk(p,t.r,t.c));
}

void change(int l,int r,int c)
{
	split(l);
	if(r<n) split(r+1);
	S.clear();S.insert(c);
	while(1)
	{
		it=glo.lower_bound(blk(l));
		if(it==glo.end()||it->l>r) break;
		S.insert(it->c);blk t=*it;
		glo.erase(it);s[t.c].erase(t);
		if(pre[t.l]!=t.l-1&&t.l>l)
		{
			e[++ecnt]=opt(t.l,pre[t.l],1,-1,0);
			pre[t.l]=t.l-1;
			e[++ecnt]=opt(t.l,pre[t.l],1,1,0);
		}
	}
	it=s[c].lower_bound(blk(l));it--;
	e[++ecnt]=opt(l,pre[l],1,-1,0);
	pre[l]=it->r;
	e[++ecnt]=opt(l,pre[l],1,1,0);
	glo.insert(blk(l,r,c));s[c].insert(blk(l,r,c));
	for(int i:S)
	{
		it=s[i].upper_bound(blk(r));
		if(it==s[i].end()) continue;
		it1=s[i].lower_bound(blk(it->l));
		e[++ecnt]=opt(it->l,pre[it->l],1,-1,0);
		pre[it->l]=(--it1)->r;
		e[++ecnt]=opt(it->l,pre[it->l],1,1,0);
	}
}

void CDQ(int L,int R)
{
	if(L>=R) return;
	int mid=(L+R)>>1,l=L,r=mid+1,tot=0;
	CDQ(L,mid);CDQ(mid+1,R);
	while(l<=mid&&r<=R)
	{
		if(e[l]<e[r])
		{
			if(e[l].tp==1) add(e[l].y,e[l].v),stk[++top]=make_pair(e[l].y,e[l].v);
			te[++tot]=e[l++];
		}
		else
		{
			if(e[r].tp==2) Ans[e[r].id]+=e[r].v*query(e[r].y);
			te[++tot]=e[r++];
		}
	}
	while(l<=mid)
	{
		if(e[l].tp==1) add(e[l].y,e[l].v),stk[++top]=make_pair(e[l].y,e[l].v);
		te[++tot]=e[l++];
	}
	while(r<=R)
	{
		if(e[r].tp==2) Ans[e[r].id]+=e[r].v*query(e[r].y);
		te[++tot]=e[r++];
	}
	while(top) add(stk[top].first,-stk[top].second),top--;
	assert(R-L+1==tot);assert(tot<MAXN*8);
	bool f=1;
	for(int i=2;i<=tot;i++)
		f&=te[i].x>=te[i-1].x;
	assert(f);
	for(int i=1;i<=tot;i++)
		e[L+i-1]=te[i];
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(!M[x]) M[x]=++Cnt,s[Cnt].insert(blk());
		x=M[x];
		it=s[x].lower_bound(blk(i));
		pre[i]=(--it)->r;
		e[++ecnt]=opt(i,pre[i],1,1,0);
		s[x].insert(blk(i,i,x));
		glo.insert(blk(i,i,x));
	}
	for(int i=1,ot,l,r,x;i<=m;i++)
	{
		scanf("%d",&ot);
		if(ot==1) 
		{
			scanf("%d%d%d",&l,&r,&x);
			if(!M[x]) M[x]=++Cnt,s[Cnt].insert(blk());
			assert(Cnt<MAXN);
			x=M[x];
			change(l,r,x);
		}
		else scanf("%d%d",&l,&r),e[++ecnt]=opt(r,l-1,2,1,++qcnt),e[++ecnt]=opt(l-1,l-1,2,-1,qcnt);
	}
	CDQ(1,ecnt);
	for(int i=1;i<=qcnt;i++) printf("%d\n",Ans[i]);
}