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

const int MAXN=1E5+10;

int c;
bool a[MAXN][2];
char str[12];

struct dat{
	dat(){memset(v,0,sizeof v);}
	bool* operator [] (int i) {return v[i];}
	const bool* operator [] (int i) const {return v[i];}	
	bool v[2][2],l,r;
	void print(){printf("%d %d\n%d %d\n%d %d\n\n",v[0][0],v[0][1],v[1][0],v[1][1],l,r);}
}t[MAXN<<2],A,B;

inline dat merge(const dat &lhs,const dat &rhs,int p)
{
	dat ret;
	ret.l=lhs.l||(lhs[0][0]&&lhs[1][1]&&a[p][0]&&a[p][1]&&rhs.l);
	ret.r=rhs.r||(rhs[0][0]&&rhs[1][1]&&a[p][0]&&a[p][1]&&lhs.r);
	ret[0][0]=(lhs[0][0]&&a[p][0]&&rhs[0][0])||(lhs[0][1]&&a[p][1]&&rhs[1][0]);
	ret[0][1]=(lhs[0][0]&&a[p][0]&&rhs[0][1])||(lhs[0][1]&&a[p][1]&&rhs[1][1]);
	ret[1][0]=(lhs[1][0]&&a[p][0]&&rhs[0][0])||(lhs[1][1]&&a[p][1]&&rhs[1][0]);
	ret[1][1]=(lhs[1][0]&&a[p][0]&&rhs[0][1])||(lhs[1][1]&&a[p][1]&&rhs[1][1]);
	return ret;
}

void pushup(int x,int l,int r){t[x]=merge(t[x<<1],t[x<<1|1],(l+r)>>1);}

void build(int x,int l,int r)
{
	if(l==r) return t[x]=B,void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}

void update(int x,int l,int r,int pos)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) update(x<<1,l,mid,pos);
	else update(x<<1|1,mid+1,r,pos);
	pushup(x,l,r);
}

void change(int x,int l,int r,int pos,const dat &val)
{
	if(l==r) return t[x]=val,void();
	int mid=(l+r)>>1;
	if(pos<=mid) change(x<<1,l,mid,pos,val);
	else change(x<<1|1,mid+1,r,pos,val);
	pushup(x,l,r);
}

dat query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return t[x];
	int mid=(l+r)>>1;
	if(qr<=mid) return query(x<<1,l,mid,ql,qr);
	if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
	else return merge(query(x<<1,l,mid,ql,qr),query(x<<1|1,mid+1,r,ql,qr),mid);
}

int main()
{
	scanf("%d",&c);
	int r1,r2,c1,c2;
	B[0][0]=B[1][1]=1;
	A[0][0]=A[0][1]=A[1][0]=A[1][1]=1;
	A.l=A.r=1;
	build(1,1,c);
	while(1)
	{
		scanf("%s",str+1);
		if(str[1]=='E') break;
		if(str[1]=='C')
		{
			scanf("%d%d%d%d",&c1,&r1,&c2,&r2);
			if(r1>r2) swap(r1,r2),swap(c1,c2);
			if(r1==r2) change(1,1,c,r1,B);
			else a[r1][c1-1]=0,update(1,1,c,r1),update(1,1,c,r2);
		}
		if(str[1]=='O')
		{
			scanf("%d%d%d%d",&c1,&r1,&c2,&r2);
			if(r1>r2) swap(r1,r2),swap(c1,c2);
			if(r1==r2) change(1,1,c,r1,A);
			else a[r1][c1-1]=1,update(1,1,c,r1),update(1,1,c,r2);
		}
		if(str[1]=='A')
		{
			scanf("%d%d%d%d",&c1,&r1,&c2,&r2);
			c1--;c2--;
			if(r1>r2) swap(r1,r2),swap(c1,c2);
			dat t1=query(1,1,c,r1,r2);
			if(t1[c1][c2]) puts("Y");
			else
			{
				dat t2=query(1,1,c,1,r1),t3=query(1,1,c,r2,c);
				if((t2.r&&t1[!c1][c2])||(t3.l&&t1[c1][!c2])||(t2.r&&t3.l&&t1[!c1][!c2])) puts("Y");
				else puts("N");
			}
		}
	}
}