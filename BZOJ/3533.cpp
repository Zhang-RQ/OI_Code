#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("-funroll-loops")
#pragma GCC target("avx")

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=400010;

struct opt{
	int tp;
	ll x,y,l,r;
}O[MAXN];

struct vec{
	ll x,y;
	
	vec(ll _x=0,ll _y=0){x=_x;y=_y;}
	vec operator -(const vec& rhs) const {return vec(x-rhs.x,y-rhs.y);}
	ll operator *(const vec& rhs) const {return 1ll*x*rhs.x+1ll*y*rhs.y;}
	ll operator ^(const vec& rhs) const {return 1ll*x*rhs.y-1ll*y*rhs.x;}
}t1[MAXN],t2[MAXN];

vector<vec> t[2][MAXN<<2];

bool fl;
char tp[66],op[66];
int n,m;
ll lstans=0;

double slope(const vec &l,const vec &r){return (1.0*r.y-l.y)/(r.x-l.x);}

void Merge(const vector<vec> &l,const vector<vec> &r,vector<vec> &Res,bool f) //f=0 up,f=1 down
{
	auto chk=f?
		[](const vec &v1,const vec &v2,const vec &v3){return ((v1-v2)^(v3-v2))>=0;}:
		[](const vec &v1,const vec &v2,const vec &v3){return ((v1-v2)^(v3-v2))<=0;};
	auto cmp=f?
		[](const vec &v1,const vec &v2){return v1.y<v2.y;}:
		[](const vec &v1,const vec &v2){return v1.y>v2.y;};
	size_t tot1=0,ptr1=0,ptr2=0,tot2=0;
	while(ptr1<l.size()&&ptr2<r.size())
		if(l[ptr1].x<r[ptr2].x)	t1[++tot1]=l[ptr1++];
		else if(l[ptr1].x>r[ptr2].x) t1[++tot1]=r[ptr2++];
		else if(cmp(l[ptr1],r[ptr2])) t1[++tot1]=r[ptr2++],ptr1++;
		else t1[++tot1]=l[ptr1++],ptr2++;
	while(ptr1<l.size())
	{
		if(tot1&&t1[tot1-1].x==l[ptr1].x)
		{
			if(cmp(l[ptr1],t1[tot1])) {++ptr1;continue;}
			else --tot1;
		}
		t1[++tot1]=l[ptr1++];
	}
	while(ptr2<r.size())
	{
		if(tot1&&t1[tot1-1].x==r[ptr2].x)
		{
			if(cmp(r[ptr2],t1[tot1])) {++ptr2;continue;}
			else --tot1;
		}
		t1[++tot1]=r[ptr2++];
	}
	t2[++tot2]=t1[1];
	for(size_t i=2;i<=tot1;i++)
	{
		while(tot2>1&&chk(t2[tot2],t2[tot2-1],t1[i])) --tot2;
		t2[++tot2]=t1[i];
	}
	Res.resize(tot2);
	for(size_t i=0;i<tot2;i++)
		Res[i]=t2[i+1];
}

ll Query(const vector<vec> &a,vec p,bool f)
{
	if(a.size()==1) return p*a[0];
	double K=-1.0*p.x/p.y;
	if(f)
	{
		int L=1,R=a.size()-1,Ans=0;
		while(L<=R)
		{
			int Mid=(L+R)>>1;
			if(slope(a[Mid-1],a[Mid])>=K) Ans=Mid,L=Mid+1;
			else R=Mid-1;
		}
		return a[Ans]*p;
	}
	else
	{
		int L=0,R=a.size()-2,Ans=a.size()-1;
		while(L<=R)
		{
			int Mid=(L+R)>>1;
			if(slope(a[Mid],a[Mid+1])>=K) Ans=Mid,R=Mid-1;
			else L=Mid+1; 
		}
		return a[Ans]*p;
	}
}

ll Query(int x,int l,int r,int ql,int qr,vec p,bool f)
{
	if(ql<=l&&r<=qr) return Query(t[f][x],p,f);
	int mid=(l+r)>>1;
	if(qr<=mid) return Query(x<<1,l,mid,ql,qr,p,f);
	else if(ql>mid) return Query(x<<1|1,mid+1,r,ql,qr,p,f);
	else return max(Query(x<<1,l,mid,ql,qr,p,f),Query(x<<1|1,mid+1,r,ql,qr,p,f));
}

void insert(int x,int l,int r,int p,vec v)
{
	if(l==r) return t[0][x].push_back(v),t[1][x].push_back(v);
	int mid=(l+r)>>1;
	if(p<=mid) insert(x<<1,l,mid,p,v);
	else insert(x<<1|1,mid+1,r,p,v);
	if(p==r)	Merge(t[0][x<<1],t[0][x<<1|1],t[0][x],0),Merge(t[1][x<<1],t[1][x<<1|1],t[1][x],1);
}

inline ll decode (int x,ll lastans){return x^(lastans&0x7fffffff);}

int main()
{
	int now=0;
	scanf("%d%s",&n,tp+1);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",op+1);
		O[i].tp=op[1]=='A'?1:2;
		m+=O[i].tp==1;
		if(O[i].tp==1)  scanf("%lld%lld",&O[i].x,&O[i].y);
		else scanf("%lld%lld%lld%lld",&O[i].x,&O[i].y,&O[i].l,&O[i].r);
	}
	for(int i=1;i<=n;i++)
	{
		if(tp[1]!='E')
		{
			O[i].x=decode(O[i].x,lstans);O[i].y=decode(O[i].y,lstans);
			O[i].l=decode(O[i].l,lstans);O[i].r=decode(O[i].r,lstans);
		}
		if(O[i].tp==1) insert(1,1,m,++now,vec(O[i].x,O[i].y));
		else  printf("%lld\n",lstans=Query(1,1,m,O[i].l,O[i].r,vec(O[i].x,O[i].y),O[i].y>=0));
	}
}