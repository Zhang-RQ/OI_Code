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
#include<iomanip>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1<<20;
const double EPS=1E-7;

int n,g,t;
double f[MAXN],Ans;

int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	int ful=(1<<n)-1;
	for(int s=0;s<1<<n;s++)
	{
		cin>>f[s];
		if(f[s]>EPS) t|=s;
	}
	if(t!=ful) return puts("INF"),0;
	for(int i=0;i<n;i++)
		for(int s=0;s<1<<n;s++)
			if((s>>i)&1)
				f[s]+=f[s^(1<<i)];
	for(int s=0;s<1<<n;s++)
	{
		int c=__builtin_popcount(s);
		if(abs(1-f[ful^s])>EPS) Ans+=(c&1?1:-1)/(1-f[ful^s]);
	}
	cout<<fixed<<setprecision(10)<<Ans<<endl;
}