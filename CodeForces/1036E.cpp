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

const int MAXN=1010;
const ll INF=1ll<<60;

struct Pnt{
	ll x,y;
	Pnt(){}
	Pnt(ll _x,ll _y){x=_x;y=_y;}
	bool operator < (const Pnt &rhs)const{return x<rhs.x||(x==rhs.x&&y<rhs.y);}
}t;

struct Line{
	Pnt a,b;
	ll d;
}L[MAXN];

set<Pnt> s,st;
int n;
ll Ans;

bool in(ll v,ll l,ll r)
{
	if(l>r) swap(l,r);
	return l<=v&&v<=r;
}

Pnt intersect(Line a,Line b)
{
	ll x0=a.a.x,y0=a.a.y;
	ll u0=(a.b.x-a.a.x)/a.d;
	ll v0=(a.b.y-a.a.y)/a.d;

	ll x1=b.a.x,y1=b.a.y;
	ll u1=(b.b.x-b.a.x)/b.d;
	ll v1=(b.b.y-b.a.y)/b.d;

	ll up1=(y1-y0)*u0-(x1-x0)*v0;
	ll dw1=u1*v0-v1*u0;
	if(!dw1||up1%dw1) return Pnt(INF,INF);
	ll k1=up1/dw1;
	ll x=x1+k1*u1,y=y1+k1*v1;
	if(in(x,a.a.x,a.b.x)&&in(x,b.a.x,b.b.x)&&in(y,a.a.y,a.b.y)&&in(y,b.a.y,b.b.y)) return Pnt(x,y);
	return Pnt(INF,INF);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld%lld",&L[i].a.x,&L[i].a.y,&L[i].b.x,&L[i].b.y);
		L[i].d=__gcd(abs(L[i].a.x-L[i].b.x),abs(L[i].a.y-L[i].b.y));
	}
	for(int i=1;i<=n;i++)
	{
		st.clear();
		Ans+=L[i].d+1;
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			t=intersect(L[i],L[j]);
			if(t.x==INF) continue;
			s.insert(t);st.insert(t);
		}
		Ans-=st.size();
	}
	printf("%lld\n",Ans+s.size());
}