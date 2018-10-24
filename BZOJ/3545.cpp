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

const int MAXN=2E5+10;
const int MAXM=5E5+10;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
        {
            x=0;static char ch=get_char();
            while(!isdigit(ch)) ch=get_char();
            while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
        }
}

using namespace FastIO;

struct _edge{
	int u,v,w;
	bool operator < (const _edge &rhs) const {return w<rhs.w;}
}E[MAXM];

struct node{
	int l,r,v;
}t[MAXN<<5];

int n,m,q,fa[MAXN],jmp[MAXN][20],cnt,val[MAXN],d[MAXN],a[MAXN],rt[MAXN],Val[MAXN];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

void insert(int &x,int l,int r,int p)
{
	if(!x) x=++cnt;
	t[x].v++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) insert(t[x].l,l,mid,p);
	else insert(t[x].r,mid+1,r,p);
}

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	int z=++cnt;
	t[z].v=t[x].v+t[y].v;
	t[z].l=merge(t[x].l,t[y].l);
	t[z].r=merge(t[x].r,t[y].r);
	return z;
}

int kth(int x,int l,int r,int k)
{
	if(k>t[x].v) return -1;
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(t[t[x].r].v>=k) return kth(t[x].r,mid+1,r,k);
	else return kth(t[x].l,l,mid,k-t[t[x].r].v);
}

int main()
{
	read(n);read(m);read(q);
	for(int i=1;i<=n;i++) read(val[i]),a[i]=val[i];
	sort(a+1,a+1+n);Val[0]=1<<30;
	int Mx=unique(a+1,a+1+n)-a-1;
	for(int i=1;i<=n;i++) val[i]=lower_bound(a+1,a+1+Mx,val[i])-a,insert(rt[i],1,Mx,val[i]);
	for(int i=1;i<=m;i++)
		read(E[i].u),read(E[i].v),read(E[i].w);
	sort(E+1,E+1+m);int tot=n;
	for(int i=1;i<=2*n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int U=find(E[i].u),V=find(E[i].v);
		if(U!=V)
		{
			++tot;Val[tot]=E[i].w;
			jmp[U][0]=tot;jmp[V][0]=tot;
			fa[U]=tot;fa[V]=tot;d[tot]+=2;
		}
	}
	for(int j=1;j<=18;j++)
		for(int i=1;i<=tot;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
	queue<int> Q;
	for(int i=1;i<=tot;i++)
		if(!d[i]) Q.push(i);
	while(!Q.empty())
	{
		int x=Q.front();Q.pop();
		rt[jmp[x][0]]=merge(rt[jmp[x][0]],rt[x]);
		if(!(--d[jmp[x][0]])) Q.push(jmp[x][0]);
	}
	for(int i=1,v,x,k;i<=q;i++)
	{
		read(v);read(x);read(k);
		for(int j=18;~j;j--)
			if(Val[jmp[v][j]]<=x)
				v=jmp[v][j];
		int Ret=kth(rt[v],1,Mx,k);
		if(~Ret) printf("%d\n",a[Ret]);
		else puts("-1");
	}
}