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

const int MAXN=110;

int n,m,Siz,d[MAXN];
double a[MAXN<<1][MAXN<<1],X[MAXN];
vector<pair<int,int> > g[MAXN];
double Ans;

void Gaussian_Elimination()
{
	for(int i=1,pos;i<=Siz;i++)
	{
		pos=i;
		for(int j=i+1;j<=Siz;j++)
			if(fabs(a[pos][i])<fabs(a[j][i])) pos=j;
		for(int j=0;j<=Siz;j++) swap(a[i][j],a[pos][j]);
		for(int j=i+1;j<=Siz;j++)
		{
			if(fabs(a[j][i])<1E-9) continue;
			double t=a[j][i]/a[i][i];
			for(int k=0;k<=Siz;k++)
				a[j][k]-=t*a[i][k];
		}
	}
	for(int i=Siz;i>=1;i--)
	{
		if(fabs(a[i][i])<1E-9)
		{
			if(fabs(a[i][0])<1E-9) return puts("Inf"),void();
			else return puts("No"),void();
		}
		X[i]=a[i][0]/a[i][i];
		for(int j=i-1;j>=1;j--)
			a[j][0]-=X[i]*a[j][i];
	}
}

void build(int K)
{
	memset(a,0,sizeof a);a[n][n]=1;
	for(int i=1;i<=n-1;i++)
	{
		a[i][i]=-d[i];
		for(int j=0;j<g[i].size();j++)
		{
			if((g[i][j].second>>K)&1) a[i][g[i][j].first]--,a[i][0]--;
			else a[i][g[i][j].first]++;
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);Siz=n;
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w),g[u].push_back(make_pair(v,w));
		++d[u];
		if(u!=v) g[v].push_back(make_pair(u,w)),++d[v];
	}
	for(int i=30;~i;--i)
	{
		build(i);Gaussian_Elimination();
		Ans+=(1<<i)*X[1];
	}
	printf("%.3lf\n",Ans);
}