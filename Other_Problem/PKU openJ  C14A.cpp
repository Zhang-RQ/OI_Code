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

double Gx;
int dep[MAXN],n,tot,Ans[MAXN];

struct Circle{
	int x,y,r;
}cir[MAXN];

struct Operation{
	int x,id,tp;
	Operation(){}
	Operation(int _x,int _id,int _tp){x=_x;id=_id;tp=_tp;}
	bool operator < (const Operation &rhs) const {return x<rhs.x;}
}opt[MAXN<<1];

double gety(int i,int tp) {return cir[i].y+(tp?-1:1)*sqrt(1ll*cir[i].r*cir[i].r-1ll*(Gx-cir[i].x)*(Gx-cir[i].x));}

struct Pnt{
	int id,tp;//tp 0 up tp 1 down
	Pnt(){}
	Pnt(int _id,int _tp){id=_id;tp=_tp;}
	bool operator < (const Pnt &rhs)const{return id==rhs.id?tp>rhs.tp:gety(id,tp)<gety(rhs.id,rhs.tp);}
};

set<Pnt> s;
set<Pnt>::iterator it;

void solve()
{
	scanf("%d",&n);tot=0;
	memset(dep,0,sizeof dep);memset(Ans,0,sizeof Ans);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&cir[i].x,&cir[i].y,&cir[i].r),opt[++tot]=Operation(cir[i].x-cir[i].r,i,1),opt[++tot]=Operation(cir[i].x+cir[i].r,i,-1);
	sort(opt+1,opt+1+tot);
	for(int i=1;i<=tot;i++)
	{
		Gx=opt[i].x;
		if(opt[i].tp==1)
		{
			it=s.lower_bound(Pnt(opt[i].id,0));
			if(it!=s.end())
			{
				if(it->tp==1) dep[opt[i].id]=dep[it->id];
				else dep[opt[i].id]=dep[it->id]+1;
			}
			s.insert(Pnt(opt[i].id,0));
			s.insert(Pnt(opt[i].id,1));
		}
		else
		{
			s.erase(Pnt(opt[i].id,0));
			s.erase(Pnt(opt[i].id,1));
		}
	}
	int mx=0;
	for(int i=1;i<=n;i++) Ans[dep[i]+1]++,mx=max(mx,dep[i]+1);
	// for(int i=1;i<=n;i++) printf("i=%d dep=%d\n",i,dep[i]);
	for(int i=1;i<=mx;i++) printf("%d\n",Ans[i]);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}