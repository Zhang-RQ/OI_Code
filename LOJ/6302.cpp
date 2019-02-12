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

    #if __cplusplus >= 201103L
        template<typename T,typename ...Args>
            inline void read(T& x,Args& ...args)
            {
                read(x);
                read(args...);
            }
    #endif
}

using namespace FastIO;

const int MAXN=4E6+10;
const int MAXSQRT=2010;

int *Lft[MAXN<<2],*Rht[MAXN<<2],*tAns[MAXN<<2];//从右边界向左延申多少和从左边界向右延伸多少
int Pool[MAXN*40],*cur=Pool,*a[MAXN];
int n,m,q,Q1[MAXN],Q2[MAXN],hd1,tl1,hd2,tl2,cLft[MAXSQRT];

bool fafa;

int solve(int *aL,int *aR,int up_lim,int down_lim)
{
	int Ret=0,L=up_lim;hd1=hd2=1;tl1=tl2=0;
	for(int i=up_lim;i<=down_lim;i++)
	{
		while(hd1<=tl1&&aL[Q1[tl1]]>=aL[i]) --tl1;
		while(hd2<=tl2&&aR[Q2[tl2]]>=aR[i]) --tl2;
		Q1[++tl1]=i;Q2[++tl2]=i;
		while(L<=i&&aL[Q1[hd1]]+aR[Q2[hd2]]<i-L+1)
			++L,hd1=L>Q1[hd1]?hd1+1:hd1,hd2=L>Q2[hd2]?hd2+1:hd2;
		Ret=max(Ret,i-L+1);
	}
	return Ret;
}

void update(int *aL,int *aR,int *Ans)
{
	int L=1;hd1=hd2=1;tl1=tl2=0;
	for(int i=1;i<=m;i++)
	{
		while(hd1<=tl1&&aL[Q1[tl1]]>=aL[i]) --tl1;
		while(hd2<=tl2&&aR[Q2[tl2]]>=aR[i]) --tl2;
		Q1[++tl1]=i;Q2[++tl2]=i;
		while(L<=i&&aL[Q1[hd1]]+aR[Q2[hd2]]<i-L+1)
			++L,hd1=L>Q1[hd1]?hd1+1:hd1,hd2=L>Q2[hd2]?hd2+1:hd2;
		Ans[i]=i-L+1;
	}
}

void pushup(int x,int l,int r)
{
	int mid=(l+r)>>1;
	for(int i=1;i<=m;i++)
	{
		Rht[x][i]=Rht[x<<1][i]==mid-l+1?Rht[x<<1][i]+Rht[x<<1|1][i]:Rht[x<<1][i];
		Lft[x][i]=Lft[x<<1|1][i]==r-mid?Lft[x<<1|1][i]+Lft[x<<1][i]:Lft[x<<1|1][i];
	}
	update(Lft[x<<1],Rht[x<<1|1],tAns[x]);
	for(int i=1;i<=m;i++) tAns[x][i]=max(tAns[x][i],max(tAns[x<<1][i],tAns[x<<1|1][i]));
}

void build(int x,int l,int r)
{
	Lft[x]=cur;cur+=m+1;
	Rht[x]=cur;cur+=m+1;
	tAns[x]=cur;cur+=m+1;
	if(l==r)
	{
		for(int i=1;i<=m;i++) Lft[x][i]=Rht[x][i]=tAns[x][i]=a[l][i];
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	pushup(x,l,r);
}

void change(int x,int l,int r,int posx,int posy)
{
	if(l==r) return Lft[x][posy]=Rht[x][posy]=tAns[x][posy]=(a[posx][posy]^=1),void();
	int mid=(l+r)>>1;
	if(posx<=mid) change(x<<1,l,mid,posx,posy);
	else change(x<<1|1,mid+1,r,posx,posy);
	pushup(x,l,r);
}

int query(int x,int l,int r,int ql,int qr,int up_lim,int down_lim)
{
	if(x==1) for(int i=up_lim;i<=down_lim;i++) cLft[i]=0;
	if(ql<=l&&r<=qr)
	{
		int Ret=solve(cLft,Rht[x],up_lim,down_lim);
		for(int i=up_lim;i<=down_lim;i++)
			cLft[i]=Lft[x][i]==r-l+1?cLft[i]+Lft[x][i]:Lft[x][i];
		for(int i=up_lim;i<=down_lim;i++) 
			Ret=max(Ret,min(i-up_lim+1,tAns[x][i]));
		return Ret;
	}
	int mid=(l+r)>>1,Ret=0;
	if(ql<=mid) Ret=max(Ret,query(x<<1,l,mid,ql,qr,up_lim,down_lim));
	if(qr>mid) Ret=max(Ret,query(x<<1|1,mid+1,r,ql,qr,up_lim,down_lim));
	return Ret;
}

int main()
{
	read(n,m,q);
	for(int i=1;i<=n;i++)
	{
		a[i]=cur,cur+=m+1;
		for(int j=1;j<=m;j++)
			read(a[i][j]);
	}
	build(1,1,n);
	for(int i=1,opt,x,y,a,b;i<=q;i++)
	{
		read(opt);
		if(!opt) read(x,y),change(1,1,n,x,y);
		else read(x,a,y,b),printf("%d\n",query(1,1,n,x,y,a,b));
	}
}