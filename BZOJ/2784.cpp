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

const int MAXT=55;
const int MAXN=35;

int a[MAXN],n,t;
bool vis[MAXT][MAXN];
double k[MAXT][MAXN],b[MAXT][MAXN],P;

pair<double,double> dfs(int x,int y)//x refers to the sum of energy,y refers to the min of energy 
{
	if(x>t) return make_pair(0,0);
	if(vis[x][y]) return make_pair(k[x][y],b[x][y]);
	vis[x][y]=1;pair<double,double> Res,tmp;
	Res.first=Res.second=0;
	double Px=x==0?0:P;
	double C=(1-Px)/y;
	for(int i=1;i<=y;i++)
	{
		tmp=dfs(x+a[i],i);
		Res.first+=tmp.first;Res.second+=tmp.second;
	}
	k[x][y]=Px/(1-C*Res.first);b[x][y]=(C*Res.second+1)/(1-C*Res.first);
	return make_pair(k[x][y],b[x][y]);
}

bool solve()
{
	memset(vis,0,sizeof vis);
	if(scanf("%lf%d%d",&P,&t,&n)==EOF) return false;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	pair<double,double> Res=dfs(0,n);
	printf("%.3lf\n",Res.second);
	return true;
}

int main() {while(solve());}