#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int cov[MAXN<<5],t[MAXN<<5];
int n,m,a[MAXN],lim,ofs,global_dlt;
map<int,int> cnt;

void pushup(int x,int l,int r)
{
	if(cov[x])
		t[x]=r-l+1;
	else
		t[x]=t[x<<1]+t[x<<1|1];
}

void change(int x,int l,int r,int cl,int cr,int dlt)
{
	if(cl<=l&&r<=cr)
		return cov[x]+=dlt,pushup(x,l,r),void();
	int mid=(l+r)>>1;
	if(cl<=mid)
		change(x<<1,l,mid,cl,cr,dlt);
	if(cr>mid)
		change(x<<1|1,mid+1,r,cl,cr,dlt);
	pushup(x,l,r);
}

int query(int x,int l,int r,int ql,int qr,int f)
{
	assert(1<=ql&&qr<=lim);
	if(ql<=l&&r<=qr)
		return f?r-l+1:t[x];
	int mid=(l+r)>>1,nxtf=f|(cov[x]>0);
	if(qr<=mid)
		return query(x<<1,l,mid,ql,qr,nxtf);
	else if(ql>mid)
		return query(x<<1|1,mid+1,r,ql,qr,nxtf);
	else
		return query(x<<1,l,mid,ql,qr,nxtf)+query(x<<1|1,mid+1,r,ql,qr,nxtf);
}

void insert(int x)
{
	if(cnt[x]&&global_dlt+1<=x&&x<=global_dlt+n)
		change(1,1,lim,ofs+x-cnt[x]+1,ofs+x,1);
}

void erase(int x)
{
	if(cnt[x]&&global_dlt+1<=x&&x<=global_dlt+n)
		change(1,1,lim,ofs+x-cnt[x]+1,ofs+x,-1);
}

int main()
{
	scanf("%d%d",&n,&m);
	ofs=n+m+1;lim=ofs<<1;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),a[i]+=global_dlt,cnt[a[i]]++;
	for(int i=1;i<=n;i++)
		insert(global_dlt+i);
	for(int i=1,p,x;i<=m;i++)
	{
		scanf("%d%d",&p,&x);
		if(!p)
		{
			if(x==1)
			{
				erase(global_dlt+n);
				global_dlt--;
				insert(global_dlt+1);
			}
			else
			{
				erase(global_dlt+1);
				global_dlt++;
				insert(global_dlt+n);
			}
		}
		else
		{
			x+=global_dlt;
			if(a[p]!=x)
			{
				erase(a[p]);
				cnt[a[p]]--;
				insert(a[p]);
				erase(x);
				cnt[x]++;
				insert(x);
				a[p]=x;
			}
		}
		printf("%d\n",n-query(1,1,lim,ofs+1+global_dlt,ofs+n+global_dlt,0));
	}
}
