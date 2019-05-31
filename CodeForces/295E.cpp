#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int LIM=2E9;

struct node{
	int l,r,c,tg;
	ll v,s;
}t[MAXN*40];

int cnt,n,m,rt;
ll x[MAXN],x1[MAXN];

void apply_tag(int x,int dlt)
{
	if(!x)
		return;
	t[x].v+=dlt*t[x].s;
	t[x].tg+=dlt;
}

void pushdown(int x)
{
	if(!x)
		return;
	if(t[x].tg)
	{
		if(t[x].l)
			apply_tag(t[x].l,t[x].tg);
		if(t[x].r)
			apply_tag(t[x].r,t[x].tg);
		t[x].tg=0;
	}
}

void pushup(int x)
{
	if(!x)
		return;
	t[x].c=t[t[x].l].c+t[t[x].r].c;
	t[x].s=t[t[x].l].s+t[t[x].r].s;
	t[x].v=t[t[x].l].v+t[t[x].r].v;
}

int queryc(int x,int l,int r,int ql,int qr)
{
	assert(-LIM<=ql&&qr<=LIM);
	if(ql>qr)
		return 0;
	if(!x)
		return 0;
	if(ql<=l&&r<=qr)
		return t[x].c;
	int mid=((ll)l+r)>>1;
	if(qr<=mid)
		return queryc(t[x].l,l,mid,ql,qr);
	else if(ql>mid)
		return queryc(t[x].r,mid+1,r,ql,qr);
	else return queryc(t[x].l,l,mid,ql,qr)+queryc(t[x].r,mid+1,r,ql,qr);
}

ll querys(int x,int l,int r,int ql,int qr)
{
	assert(-LIM<=ql&&qr<=LIM);
	if(ql>qr)
		return 0;
	if(!x)
		return 0;
	if(ql<=l&&r<=qr)
		return t[x].s;
	int mid=((ll)l+r)>>1;
	if(qr<=mid)
		return querys(t[x].l,l,mid,ql,qr);
	else if(ql>mid)
		return querys(t[x].r,mid+1,r,ql,qr);
	else return querys(t[x].l,l,mid,ql,qr)+querys(t[x].r,mid+1,r,ql,qr);
}

ll queryv(int x,int l,int r,int ql,int qr)
{
	assert(-LIM<=ql&&qr<=LIM);
	if(ql>qr)
		return 0;
	if(!x)
		return 0;
	if(ql<=l&&r<=qr)
		return t[x].v;
	int mid=((ll)l+r)>>1;pushdown(x);
	if(qr<=mid)
		return queryv(t[x].l,l,mid,ql,qr);
	else if(ql>mid)
		return queryv(t[x].r,mid+1,r,ql,qr);
	else return queryv(t[x].l,l,mid,ql,qr)+queryv(t[x].r,mid+1,r,ql,qr);
}

void change(int &x,int l,int r,int p,int rk,int f)
{
	assert(l<=p&&p<=r);
	if(!x)
		x=++cnt,
		assert(cnt<=MAXN*40);;
	if(l==r)
	{
		t[x].c+=f;
		t[x].s+=1ll*l*f;
		t[x].v+=1ll*l*rk*f;
		return;
	}
	int mid=((ll)l+r)>>1;pushdown(x);
	if(p<=mid)
		change(t[x].l,l,mid,p,rk,f);
	else
		change(t[x].r,mid+1,r,p,rk,f);
	pushup(x);
}

void change_r(int &x,int l,int r,int cl,int cr,int dlt)
{
	assert(-LIM<=cl&&cr<=LIM);
	if(cl>cr)
		return;
	if(!x)
		return;
	if(cl<=l&&r<=cr)
		return apply_tag(x,dlt),void();
	int mid=((ll)l+r)>>1;pushdown(x);
	if(cl<=mid)
		change_r(t[x].l,l,mid,cl,cr,dlt);
	if(cr>mid)
		change_r(t[x].r,mid+1,r,cl,cr,dlt);
	pushup(x);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&x[i]);
		x1[i]=x[i];
	}
	sort(x1+1,x1+1+n);
	for(int i=1;i<=n;i++)
		change(rt,-LIM,LIM,x1[i],i,1);
	scanf("%d",&m);
	for(int i=1,op,a,b;i<=m;i++)
	{
		scanf("%d%d%d",&op,&a,&b);
		if(op==1)
		{
			int prex=x[a];
			change(rt,-LIM,LIM,x[a],queryc(rt,-LIM,LIM,-LIM,x[a]),-1);
			x[a]+=b;
			change(rt,-LIM,LIM,x[a],queryc(rt,-LIM,LIM,-LIM,x[a])+1,1);
			if(b>0)
				change_r(rt,-LIM,LIM,prex+1,x[a]-1,-1);
			else
				change_r(rt,-LIM,LIM,x[a]+1,prex-1,1);
		}
		else
		{
			ll S=querys(rt,-LIM,LIM,a,b),Sa=S*queryc(rt,-LIM,LIM,a,b);
			ll S1=queryv(rt,-LIM,LIM,a,b)-queryc(rt,-LIM,LIM,-LIM,a-1)*S;
			ll S2=Sa+S-S1;
			printf("%lld\n",S1-S2);
		}
		assert(cnt<=MAXN*40);
	}
}
