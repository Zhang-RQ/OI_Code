#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MAXX=1E9;

struct node_t{
	int l,r,v;
}t[MAXN*40];

struct dat_t{
	int x,r,q;

	bool operator < (const dat_t &rhs) const {return r>rhs.r;} 
}a[MAXN];

int cnt;

void insert(int &x,int l,int r,int p)
{
	if(!x) x=++cnt;
	t[x].v++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p);
	else insert(t[x].r,mid+1,r,p);
}

int query(int x,int l,int r,int ql,int qr)
{
	if(!x) return 0;
	if(ql<=l&&r<=qr) return t[x].v;
	int mid=(l+r)>>1;
	if(qr<=mid) return query(t[x].l,l,mid,ql,qr);
	else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr);
	else return query(t[x].l,l,mid,ql,qr)+query(t[x].r,mid+1,r,ql,qr);
}

int n,k;
ll Ans;
map<int,int> id;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i].x,&a[i].r,&a[i].q);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	{
		for(map<int,int>::iterator it=id.lower_bound(a[i].q-k);it!=id.end()&&it->first<=a[i].q+k;it++)
			Ans+=query(it->second,0,MAXX,max(0,a[i].x-a[i].r),min(MAXX,a[i].x+a[i].r));
		insert(id[a[i].q],0,MAXX,a[i].x);
	}
	printf("%lld\n",Ans);
}
