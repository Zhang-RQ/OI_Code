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
#include<valarray>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=55;
const long double EPS=1E-8;

int n;
valarray<long double> a[MAXN];
long double tAns=1;

void Gauss()
{
	int f=1;
	for(int i=1;i<n;i++)
	{
		int pos=i;
		for(int j=i+1;j<n;j++)
			if(abs(a[pos][i])<abs(a[j][i]))
				pos=j,f*=-1;
		swap(a[i],a[pos]);
		for(int j=i+1;j<n;j++)
			a[j]-=a[i]*(a[j][i]/a[i][i]);
	}
	for(int i=1;i<n;i++)
		tAns=tAns*a[i][i];
	tAns*=f;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		a[i].resize(n+1);
		for(int j=1;j<=n;j++)
		{
			if(i==j) scanf("%*f");
			else
			{
				scanf("%Lf",&a[i][j]);
				if(abs(1-a[i][j])<EPS) a[i][j]-=EPS;
				if(i<j) tAns*=(1-a[i][j]);
				a[i][j]=-a[i][j]/(1-a[i][j]);
				a[i][i]-=a[i][j];
			}
		}
	}
	Gauss();
	printf("%.15Lf\n",tAns);
}
