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

const int MAXN=1E5+10;
const int MxBlk=340;

int n,m,L[MxBlk],R[MxBlk],bl[MAXN],blksiz,a[MAXN];
int idx[MxBlk][MAXN],val[MAXN],fa[MAXN],siz[MAXN],tag[MxBlk],mx[MAXN];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

inline void apply(int B)
{
	for(int i=L[B];i<=R[B];++i)
		a[i]=val[find(i)],idx[B][a[i]]=0,a[i]-=tag[B];
	for(int i=L[B];i<=R[B];++i)
		fa[i]=0;
	tag[B]=0;
}

inline void build(int B)
{
	mx[B]=0;
	for(int i=L[B];i<=R[B];++i)
	{
		siz[i]=1;mx[B]=max(mx[B],a[i]);
		if(!idx[B][a[i]]) idx[B][a[i]]=i,fa[i]=i,val[i]=a[i];
		else fa[i]=idx[B][a[i]],siz[idx[B][a[i]]]+=siz[i];
	}
}

inline void change(int l,int r,int x)
{
	int Bl=bl[l],Br=bl[r];
	if(Br-Bl<=1)
	{
		apply(Bl);
		if(Bl!=Br) apply(Br);
		for(int i=l;i<=r;++i)
			if(a[i]>x) a[i]-=x;
		build(Bl);
		if(Bl!=Br) build(Br);
		return;
	}
	++Bl;--Br;
	apply(Bl-1);apply(Br+1);
	for(int i=l;i<=L[Bl]-1;++i) if(a[i]>x) a[i]-=x;
	for(int i=R[Br]+1;i<=r;++i) if(a[i]>x) a[i]-=x;
	build(Bl-1);build(Br+1);
	for(int i=Bl;i<=Br;++i)
	{
		if(mx[i]-tag[i]>=2*x)
		{
			for(int j=tag[i]+1;j<=x+tag[i];j++)
				if(idx[i][j])
				{
					if(idx[i][j+x]) fa[idx[i][j]]=idx[i][j+x],siz[idx[i][j+x]]+=siz[idx[i][j]],idx[i][j]=0;
					else idx[i][j+x]=idx[i][j],val[idx[i][j+x]]=j+x,idx[i][j]=0;
				}
			tag[i]+=x;
		}
		else
		{
			for(int j=tag[i]+x+1;j<=mx[i];j++)
				if(idx[i][j])
				{
					if(idx[i][j-x]) fa[idx[i][j]]=idx[i][j-x],siz[idx[i][j-x]]+=siz[idx[i][j]],idx[i][j]=0;
					else idx[i][j-x]=idx[i][j],val[idx[i][j-x]]=j-x,idx[i][j]=0;
				}
			mx[i]=min(mx[i],x+tag[i]);
		}
	}
}

inline int query(int l,int r,int x)
{
	int Bl=bl[l],Br=bl[r];
	if(Br-Bl<=1)
	{
		int ret=0;
		for(int i=l;i<=r;++i)
			if(val[find(i)]-tag[bl[i]]==x) ++ret;
		return ret;
	}
	++Bl;--Br;
	int ret=0;
	for(int i=l;i<=L[Bl]-1;++i) if(val[find(i)]-tag[bl[i]]==x) ++ret;
	for(int i=R[Br]+1;i<=r;++i) if(val[find(i)]-tag[bl[i]]==x) ++ret;
	for(int i=Bl;i<=Br;++i)
		if(x+tag[i]<MAXN)
			ret+=siz[idx[i][x+tag[i]]];
	return ret;
}

int main()
{
	read(n);read(m);
	blksiz=sqrt(n);
	for(int i=1;i<=n;++i) read(a[i]);
	for(int i=1;i<=n;++i)
	{
		bl[i]=(i-1)/blksiz+1;
		if(!L[bl[i]]) L[bl[i]]=i;
		R[bl[i]]=i;
	}
	for(int i=1;i<=bl[n];++i) build(i);	
	for(int i=1,opt,l,r,x;i<=m;++i)
	{
		read(opt,l,r,x);
		if(opt==1) change(l,r,x);
		else printf("%d\n",query(l,r,x));
	}
}