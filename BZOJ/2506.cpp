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
#include<ctime>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MxBlk=420;

int n,m,cnt,L[MxBlk],R[MxBlk],bl[MAXN],blc;
int a[MAXN],f[MxBlk][105][105],Ans[MAXN],val[MAXN];

struct Qs{
	int p,v,f,id;
};

vector<Qs> ve[MAXN];

void init()
{
	int blksiz=350;
	for(int i=1;i<=n;i++)
	{
		bl[i]=(i-1)/blksiz+1;
		if(!L[bl[i]]) L[bl[i]]=i;
		R[bl[i]]=i;
	}
	blc=bl[n];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=100;j++)
			f[bl[i]][j][a[i]%j]++;
	for(int i=1;i<=blc;i++)
		for(int j=1;j<=100;j++)
			for(int c=0;c<j;c++)
				f[i][j][c]+=f[i-1][j][c];
}

int query1(int l,int r,int p,int v) //p<=100
{
	int Bl=bl[l],Br=bl[r];
	if(Br-Bl<=1)
	{
		int cnt=0;
		for(int i=l;i<=r;i++)
			if(a[i]%p==v)
				++cnt;
		return cnt;
	}
	++Bl,--Br;
	int Ans=f[Br][p][v]-f[Bl-1][p][v];
	for(int x=L[Bl]-1;x>=l;x--)
		if(a[x]%p==v) Ans++;
	for(int x=R[Br]+1;x<=r;x++)
		if(a[x]%p==v) Ans++;
	return Ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init();
	for(int i=1,l,r,p,v;i<=m;i++)
	{
		scanf("%d%d%d%d",&l,&r,&p,&v);
		if(p<=100)
			Ans[i]=query1(l,r,p,v);
		else
		{
			if(l!=1) ve[l-1].push_back((Qs){p,v,-1,i});
			ve[r].push_back((Qs){p,v,1,i});
		}
	}
	for(int i=1;i<=n;i++)
	{
		++val[a[i]];
		for(int j=0;j<ve[i].size();j++)
		{
			if(ve[i][j].p>10000) Ans[ve[i][j].id]+=ve[i][j].f*val[ve[i][j].v];
			else
			{
				int tmp=0;
				for(int x=ve[i][j].v;x<=10000;x+=ve[i][j].p)
					tmp+=val[x];
				Ans[ve[i][j].id]+=tmp*ve[i][j].f;
			}
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",Ans[i]);
}