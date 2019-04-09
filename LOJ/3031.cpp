#include"meetings.h"
#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

mt19937 RandEngine(chrono::steady_clock::now().time_since_epoch().count());
inline int RandInt(int l,int r) {return uniform_int_distribution<int>(l,r)(RandEngine);}

const int MAXN=1E5+10;
vector<int> TMP[MAXN];

void check(int u,int v){return Bridge(min(u,v),max(u,v));}

void solve_chain(const vector<int> &v,int x,int y)
{
	if(v.size()==1) return;
	if(v.size()==2) return check(v[0],v[1]),void();
	if(v.size()==3) return check(x,v[0]^v[1]^v[2]^y^x),check(y,v[0]^v[1]^v[2]^y^x),void();
	int z=v[RandInt(0,v.size()-1)];
	while(z==x||z==y) z=v[RandInt(0,v.size()-1)];
	vector<int> Xs,Ys;
	Xs.push_back(x);Ys.push_back(y);
	Xs.push_back(z);Ys.push_back(z);
	for(int p:v)
		if(p!=x&&p!=y&&p!=z)
		{
			int w=Query(x,z,p);
			if(w==p) Xs.push_back(p);
			else Ys.push_back(p),assert(w==z);
		}
	solve_chain(Xs,x,z);solve_chain(Ys,y,z);
}

void solve(const vector<int> &v)
{
	if(v.size()==1) return;
	if(v.size()==2) return check(v[0],v[1]),void();
	int Rt=v[RandInt(0,v.size()-1)];
	int x=v[RandInt(0,v.size()-1)];
	while(x==Rt) x=v[RandInt(0,v.size()-1)];
	vector<int> c;
	vector<vector<int> > V;
	c.push_back(Rt);c.push_back(x);
	for(auto p:v)
		TMP[p].clear();
	for(auto p:v)
		if(p!=Rt&&p!=x)
		{
			int y=Query(Rt,p,x);
			if(y==p) c.push_back(p);
			else TMP[y].push_back(p);
		}
	for(auto p:c)
		if(TMP[p].size())
			TMP[p].push_back(p),V.push_back(TMP[p]);
	for(auto vec:V)
		solve(vec);
	solve_chain(c,Rt,x);
}

void Solve(int n)
{
	vector<int> tmp;
	for(int i=0;i<n;i++)
		tmp.push_back(i);
	solve(tmp);
}
