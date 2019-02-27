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

const int MAXN=5E5+10;

char s[MAXN];
int n,buk[MAXN],ord[MAXN],q;
int son[MAXN][26],par[MAXN],mx[MAXN],Rt[MAXN],cnt=1,rt=1,lst=1,tot;

struct node_t{
	int l,r,v;
}t[MAXN*40];

void insert(int &x,int l,int r,int p)
{
	if(!x) x=++tot;
	t[x].v++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p);
	else insert(t[x].r,mid+1,r,p);
}

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	int z=++tot;
	t[z].v=t[x].v+t[y].v;
	t[z].l=merge(t[x].l,t[y].l);
	t[z].r=merge(t[x].r,t[y].r);
	return z;
}

int query(int x,int l,int r,int ql,int qr)
{
	if(!x||ql>qr) return 0;
	if(ql<=l&&r<=qr) return t[x].v;
	int mid=(l+r)>>1;
	if(qr<=mid) return query(t[x].l,l,mid,ql,qr);
	else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr);
	else return query(t[x].l,l,mid,ql,qr)+query(t[x].r,mid+1,r,ql,qr);
}

void append(int x,int pos)
{
	int p=lst,np=++cnt;
	mx[np]=mx[p]+1;insert(Rt[np],1,n,pos);
	while(p&&!son[p][x]) son[p][x]=np,p=par[p];
	if(!p) par[np]=rt;
	else
	{
		int q=son[p][x];
		if(mx[q]==mx[p]+1) par[np]=q;
		else
		{
			int nq=++cnt;
			mx[nq]=mx[p]+1;
			par[nq]=par[q];
			par[q]=par[np]=nq;
			memcpy(son[nq],son[q],sizeof son[q]);
			while(p&&son[p][x]==q) son[p][x]=nq,p=par[p];
		}
	}
	lst=np;
}

int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++) append(s[i]-'a',i);
	for(int i=1;i<=cnt;i++) buk[mx[i]]++;
	for(int i=1;i<=n;i++) buk[i]+=buk[i-1];
	for(int i=1;i<=cnt;i++) ord[buk[mx[i]]--]=i;
	for(int i=cnt;i;i--)
	{
		int p=ord[i];
		Rt[par[p]]=merge(Rt[par[p]],Rt[p]);
	}
	scanf("%d",&q);
	int l,r,t,lcp,nxc,x;
	while(q--)
	{
		scanf("%d%d%s",&l,&r,s+1);
		t=strlen(s+1);
		lcp=0;nxc=-1;x=rt;
		for(int i=0;i<=t;i++)
		{
			if(i)
			{
				if(son[x][s[i]-'a']) x=son[x][s[i]-'a'];
				else break;
			}
			int lim=(i==t)?-1:s[i+1]-'a';
			for(int j=25;j>lim;j--)
				if(son[x][j])
				{
					int y=son[x][j];
					if(query(Rt[y],1,n,l+i,r)) lcp=i,nxc=j;
				}
		}
		if(nxc==-1) puts("-1");
		else
		{
			for(int i=1;i<=lcp;i++) putchar(s[i]);
			putchar('a'+nxc);
			puts("");
		}
	}
}
