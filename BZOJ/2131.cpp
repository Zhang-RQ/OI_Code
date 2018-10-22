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

int n,W,cnt,Ans,rt;

struct node{
	int l,r,v;
}t[MAXN<<4];

struct T{
	int p,t,v;
	bool operator < (const T &rhs) const {return t-p<rhs.t-rhs.p||(t-p==rhs.t-rhs.p&&t+p<rhs.t+rhs.p);}
}a[MAXN];

void C(int &x,int l,int r,int p,int v)
{
	if(!x) x=++cnt;
	t[x].v=max(t[x].v,v);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) C(t[x].l,l,mid,p,v);
	else C(t[x].r,mid+1,r,p,v);
}

int Q(int x,int l,int r,int ql,int qr)
{
	if(!x||(ql<=l&&r<=qr)) return t[x].v;
	int mid=(l+r)>>1;
	if(qr<=mid) return Q(t[x].l,l,mid,ql,qr);
	else if(ql>mid) return Q(t[x].r,mid+1,r,ql,qr);
	return max(Q(t[x].l,l,mid,ql,qr),Q(t[x].r,mid+1,r,ql,qr));
}

int main()
{
	scanf("%d%d",&W,&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&a[i].t,&a[i].p,&a[i].v),a[i].t<<=1,W=max(W,a[i].t+a[i].p);
	sort(a+1,a+1+n);
	for(int i=1,v;i<=n;i++)
	{
		v=Q(rt,1,W,1,a[i].t+a[i].p)+a[i].v;
		Ans=max(v,Ans);
		C(rt,1,W,a[i].t+a[i].p,v);
	}
	printf("%d\n",Ans);
}