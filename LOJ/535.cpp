#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3E5+10;

int n,h[MAXN],totl,totr,Lft[MAXN],Rht[MAXN];

namespace swipe_line{
	struct opt{
		int x,l,r,dlt;

		bool operator < (const opt &rhs) const {return x<rhs.x;}
	}op[MAXN<<1];
	
	int t[MAXN<<2],tag[MAXN<<2],tot,L[MAXN],R[MAXN];

	void apply_tag(int x,int dlt) {t[x]+=dlt,tag[x]+=dlt;}

	void pushup(int x){t[x]=max(t[x<<1],t[x<<1|1]);}

	void pushdown(int x)
	{
		if(tag[x])
		{
			apply_tag(x<<1,tag[x]);
			apply_tag(x<<1|1,tag[x]);
			tag[x]=0;
		}
	}

	void change(int x,int l,int r,int cl,int cr,int dlt)
	{
		if(cl>cr) return;
		if(cl<=l&&r<=cr) return apply_tag(x,dlt),void();
		int mid=(l+r)>>1;pushdown(x);
		if(cl<=mid) change(x<<1,l,mid,cl,cr,dlt);
		if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,dlt);
		pushup(x);
	}

	int query(int x,int l,int r,int ql,int qr)
	{
		if(ql>qr) return 0;
		if(ql<=l&&r<=qr) return t[x];
		int mid=(l+r)>>1;pushdown(x);
		if(qr<=mid) return query(x<<1,l,mid,ql,qr);
		else if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
		else return max(query(x<<1,l,mid,ql,qr),query(x<<1|1,mid+1,r,ql,qr));
	}

	void add_rect(int x1,int y1,int x2,int y2)
	{
		if(x1>x2||y1>y2) return;
		op[++tot]=(opt){x1,y1,y2,1};
		op[++tot]=(opt){x2+1,y1,y2,-1};
	}

	int solve()
	{
		int Ans=0;
		sort(op+1,op+1+tot);
		for(int x=1,ptr=1;x<=totl;x++)
		{
			while(ptr<=tot&&op[ptr].x==x)
				change(1,1,totr,op[ptr].l,op[ptr].r,op[ptr].dlt),++ptr;
			Ans=max(Ans,query(1,1,totr,L[x],R[x]));
		}
		return Ans;
	}
}

ll calc_ans()
{
	int t[MAXN]={0};
	auto C=[&](int x){for(;x<=n;x+=x&(-x)) t[x]++;};
	auto Q=[&](int x){int Ret=0;for(;x;x-=x&(-x)) Ret+=t[x];return Ret;};
	ll Ans=0;
	for(int i=n;i;i--)
		Ans+=Q(h[i]),C(h[i]);
	return Ans;
}

int Find1(int *a,int L,int R,int v)
{
	int Ans=R+1;
	while(L<=R)
	{
		int Mid=(L+R)>>1;
		if(h[a[Mid]]>=v) Ans=Mid,R=Mid-1;
		else L=Mid+1;
	}
	return Ans;
}

int Find2(int *a,int L,int R,int v)
{
	int Ans=L-1;
	while(L<=R)
	{
		int Mid=(L+R)>>1;
		if(h[a[Mid]]<=v) Ans=Mid,L=Mid+1;
		else R=Mid-1;
	}
	return Ans;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	Lft[totl=1]=1;
	for(int i=2;i<=n;i++)
		if(h[i]>h[Lft[totl]])
			Lft[++totl]=i;
	Rht[totr=1]=n;
	for(int i=n-1;i;i--)
		if(h[i]<h[Rht[totr]])
			Rht[++totr]=i;
	reverse(Rht+1,Rht+1+totr);
	for(int i=1;i<=n;i++)
	{
		int ur=upper_bound(Lft+1,Lft+totl+1,i)-Lft-1;
		int ul=Find1(Lft,1,ur,h[i]);
		int dl=lower_bound(Rht+1,Rht+totr+1,i)-Rht;
		int dr=Find2(Rht,dl,totr,h[i]);
		swipe_line::add_rect(ul,dl,ur,dr);
	}
	for(int i=1;i<=totl;i++)
	{
		swipe_line::L[i]=lower_bound(Rht+1,Rht+totr+1,Lft[i])-Rht;
		swipe_line::R[i]=Find2(Rht,swipe_line::L[i],totr,h[Lft[i]]);
	}
	int Ans2=swipe_line::solve();
	if(Ans2>1)
		printf("%lld\n",calc_ans()-2*(Ans2-2));
	else
		printf("%lld\n",calc_ans());
}
