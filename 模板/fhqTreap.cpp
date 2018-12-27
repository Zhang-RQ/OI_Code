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

int son[MAXN][2],v[MAXN],fix[MAXN],siz[MAXN],cnt,Rt,n;

int nd(int val)
{
	++cnt;v[cnt]=val;siz[cnt]=1;fix[cnt]=rand();
	return cnt;
}

void pushup(int x){siz[x]=siz[son[x][0]]+siz[son[x][1]]+1;}

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	if(fix[x]>fix[y]) return son[x][1]=merge(son[x][1],y),pushup(x),x;
	else return son[y][0]=merge(x,son[y][0]),pushup(y),y;
}

pair<int,int> split(int x,int val)
{
	if(!x) return make_pair(0,0);
	if(v[x]<=val)
	{
		pair<int,int> t=split(son[x][1],val);
		son[x][1]=t.first;pushup(x);
		return make_pair(x,t.second);
	}
	else
	{
		pair<int,int> t=split(son[x][0],val);
		son[x][0]=t.second;pushup(x);
		return make_pair(t.first,x);
	}
}

void insert(int val)
{
	pair<int,int> t=split(Rt,val);
	Rt=merge(t.first,merge(nd(val),t.second));
}

void erase(int val)
{
	pair<int,int> t2=split(Rt,val);
	pair<int,int> t1=split(t2.first,val-1);
	assert(v[t1.second]==val);
	int x=merge(son[t1.second][0],son[t1.second][1]);
	Rt=merge(t1.first,merge(x,t2.second));
}

int kth(int x,int k) //return val
{
	if(siz[son[x][0]]+1==k) return v[x];
	if(siz[son[x][0]]+1>k) return kth(son[x][0],k);
	else return kth(son[x][1],k-siz[son[x][0]]-1);
}

int Rank(int val)
{
	pair<int,int> t=split(Rt,val-1);
	int ret=siz[t.first];
	Rt=merge(t.first,t.second);
	return ret+1;
}

int Pred(int val) //return val
{
	pair<int,int> t=split(Rt,val-1);
	int x=t.first;
	while(son[x][1]) x=son[x][1];
	Rt=merge(t.first,t.second);
	return v[x];
}

int Succ(int val) //return val
{
	pair<int,int> t=split(Rt,val);
	int x=t.second;
	while(son[x][0]) x=son[x][0];
	Rt=merge(t.first,t.second);
	return v[x];
}


int main()
{
	srand((ull)new char);
	scanf("%d",&n);
	for(int i=1,opt,x;i<=n;i++)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1) insert(x);
		else if(opt==2) erase(x);
		else if(opt==3) printf("%d\n",Rank(x));
		else if(opt==4) printf("%d\n",kth(Rt,x));
		else if(opt==5) printf("%d\n",Pred(x));
		else if(opt==6) printf("%d\n",Succ(x));
	}
}