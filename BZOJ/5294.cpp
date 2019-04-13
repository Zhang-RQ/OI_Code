#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

struct dat{
	ll pre[2][3][3],suf[2][3][3],Ans;
	int c0,c1,cc;

	friend dat merge(const dat &l,const dat &r)
		{
			dat ret;
			memcpy(ret.pre,l.pre,sizeof ret.pre);
			memcpy(ret.suf,r.suf,sizeof ret.suf);
			for(int i=0;i<2;i++)
				for(int j=0;j<3;j++)
					for(int k=0;k<3;k++)
						ret.pre[i^l.cc][min(2,l.c0+j)][min(2,l.c1+k)]+=r.pre[i][j][k],
						ret.suf[i^r.cc][min(2,r.c0+j)][min(2,r.c1+k)]+=l.suf[i][j][k];
			ret.Ans=l.Ans+r.Ans;

			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					for(int k=0;k<3;k++)
						for(int o=0;o<3;o++)
							ret.Ans+=l.suf[0][i][k]*r.pre[0][j][o]+l.suf[1][i][k]*r.pre[1][j][o];
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					for(int k=0;k<3;k++)
						for(int o=0;o<3;o++)
							if(i+j>1&&k+o>1)
								ret.Ans+=l.suf[1][i][k]*r.pre[0][j][o]+l.suf[0][i][k]*r.pre[1][j][o];
			ret.c1=min(2,l.c1+r.c1);
			ret.c0=min(2,l.c0+r.c0);
			ret.cc=l.cc^r.cc;
			return ret;
		}
}t[MAXN<<2],b[2];

int n,q,a[MAXN];

void pushup(int x){t[x]=merge(t[x<<1],t[x<<1|1]);}

void build(int x,int l,int r)
{
	if(l==r)
		return t[x]=b[a[l]],void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	pushup(x);
}

void change(int x,int l,int r,int p)
{
	if(l==r)
		return t[x]=b[a[l]^=1],void();
	int mid=(l+r)>>1;
	if(p<=mid) change(x<<1,l,mid,p);
	else change(x<<1|1,mid+1,r,p);
	pushup(x);
}

dat query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return t[x];
	int mid=(l+r)>>1;
	if(qr<=mid) return query(x<<1,l,mid,ql,qr);
	else if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
	else return merge(query(x<<1,l,mid,ql,qr),query(x<<1|1,mid+1,r,ql,qr));
}

int main()
{
	b[0].Ans=1;b[0].c0=1;
	b[0].pre[0][1][0]=b[0].suf[0][1][0]=1;
	b[1].Ans=0;b[1].c1=b[1].cc=1;
	b[1].pre[1][0][1]=b[1].suf[1][0][1]=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	scanf("%d",&q);
	for(int i=1,op,x,y;i<=q;i++)
	{
		scanf("%d%d",&op,&x);
		if(op==1)
			change(1,1,n,x);
		else
		{
			scanf("%d",&y);
			printf("%lld\n",query(1,1,n,x,y).Ans);
		}
	}
}
