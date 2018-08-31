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
const double x0=0.5;

double frac[20];

struct Poly{
	double v[16];
	double& operator [] (int i){return v[i];}
	const double& operator [] (int i) const {return v[i];}
	Poly operator + (const Poly &rhs) const 
	{
		Poly ret;
		for(int i=0;i<=15;i++)
			ret[i]=v[i]+rhs[i];
		return ret;
	}
	double operator () (double x) const 
	{
		x-=x0;
		double ret=v[0],_x=x,fac=1;
		for(int i=1;i<=15;i++,x*=_x,fac*=i)
			ret+=v[i]*x/fac;
		return ret;
	}
	void set_sin(double a,double b) //sin(ax+b)
	{
		double Sin=sin(a*x0+b),Cos=cos(a*x0+b),_a=a;
		v[0]=Sin;
		for(int i=1;i<=15;i++,a*=_a)
		{
			if(i%4==1) v[i]=a*Cos;
			else if (i%4==2) v[i]=-a*Sin;
			else if(i%4==3) v[i]=-a*Cos;
			else if(i%4==0) v[i]=a*Sin;
		}
	}
	void set_exp(double a,double b)//e^(ax+b)
	{
		double _a=a;
		v[0]=b=exp(a*x0+b);
		for(int i=1;i<=15;i++,a*=_a)
			v[i]=a*b;
	}
	void set_line(double a,double b)
	{
		memset(v,0,sizeof v);
		v[1]=a;v[0]=b+x0*a;
	}
};

struct node{
	int son[2],fa;
	Poly s,v;
	bool rev;
}t[MAXN];

int n,m;
char str[110];

#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define fa(x) t[x].fa
#define rson(x) (rs(fa(x))==(x))

inline bool isroot(int x){return ls(fa(x))!=x&&rs(fa(x))!=x;}

inline void pushup(int x){t[x].s=t[x].v+t[ls(x)].s+t[rs(x)].s;}

inline void pushdown(int x){if(t[x].rev) swap(ls(x),rs(x)),t[ls(x)].rev^=1,t[rs(x)].rev^=1,t[x].rev=0;}

void pd(int x){if(!isroot(x)) pd(fa(x));pushdown(x);}

inline void rotate(int x)
{
	int y=fa(x),z=fa(y);
	bool rsx=rson(x),rsy=rson(y);
	if(!isroot(y)) t[z].son[rsy]=x;
	t[y].son[rsx]=t[x].son[!rsx];
	t[x].son[!rsx]=y;
	fa(t[y].son[rsx])=y;
	fa(x)=z;fa(y)=x;
	pushup(y);
}

inline void splay(int x)
{
	pd(x);
	while(!isroot(x))
	{
		if(!isroot(fa(x))) rotate(rson(x)==rson(fa(x))?fa(x):x);
		rotate(x);
	}
	pushup(x);
}

inline void access(int x)
{
	for(int y=0;x;y=x,x=fa(x))
		splay(x),rs(x)=y,pushup(x);
}

inline void makeroot(int x)
{
	access(x);splay(x);
	t[x].rev^=1;
}

inline int findroot(int x)
{
	access(x);splay(x);
	while(ls(x)) x=ls(x);
	return x;
}

inline void split(int x,int y)
{
	makeroot(x);
	access(y);splay(y);
}

inline void link(int x,int y)
{
	makeroot(y);
	fa(y)=x;
}

inline void cut(int x,int y)
{
	split(x,y);
	if(ls(y)==x) ls(y)=fa(x)=0,pushup(y);
}

int main()
{
	scanf("%d%d%*s",&n,&m);
	double x,a,b;
	for(int i=1,f;i<=n;i++)
	{
		scanf("%d%lf%lf",&f,&a,&b);
		if(f==1) t[i].v.set_sin(a,b);
		else if(f==2) t[i].v.set_exp(a,b);
		else if(f==3) t[i].v.set_line(a,b);
	}
	for(int i=1,u,v,f;i<=m;i++)
	{
		scanf("%s",str+1);
		if(str[1]=='a')
		{
			scanf("%d%d",&u,&v);
			++u,++v;
			link(u,v);
		}
		else if(str[1]=='d')
		{
			scanf("%d%d",&u,&v);
			++u,++v;
			cut(u,v);
		}
		else if(str[1]=='m')
		{
			scanf("%d%d%lf%lf",&u,&f,&a,&b);
			++u,++v;splay(u);
			if(f==1) t[u].v.set_sin(a,b);
			else if(f==2) t[u].v.set_exp(a,b);
			else if(f==3) t[u].v.set_line(a,b);
		}
		else if(str[1]=='t')
		{
			scanf("%d%d%lf",&u,&v,&x);
			++u,++v;
			if(findroot(v)!=findroot(u)) puts("unreachable");
			else 
			{
				split(u,v);
				printf("%.20lf\n",t[v].s(x));
			}
		}
	}
}