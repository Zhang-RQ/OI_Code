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

const int MAXN=25;

int n;
double va[MAXN],vb[MAXN],S;

double get_v(double T)
{
	double ret=1E20,Ts=T/va[n]+(S-T)/vb[n];
	for(int i=1;i<n;i++)
		ret=min(ret,(T/va[i]+(S-T)/vb[i])-Ts);
	return ret;
}

int main()
{
	while(~scanf("%lf",&S))
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lf%lf",&va[i],&vb[i]);
		double L=0,R=S;
		for(int i=1;i<=200;i++)
		{
			double mid1=(L+L+R)/3,mid2=(L+R+R)/3;
			if(get_v(mid1)>get_v(mid2)) R=mid2;
			else L=mid1;
		}
		if(get_v(L)<0) puts("The cheater cannot win.");
		else printf("The cheater can win by %d seconds with r = %.2lfkm and k = %.2lfkm.\n",(int)(0.5+get_v(L)*3600),L,S-L);	
	}
}