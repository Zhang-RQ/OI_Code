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

int a,b,c,d;
double Ans,cur;

int main()
{
	scanf("%d%d%d%d",&a,&b,&c,&d);
	cur=1;
	while(1)
	{
		Ans+=cur*(1.0*a/b);
		cur=cur*(1-1.0*a/b)*(1-1.0*c/d);
		if(cur<1E-10) break;
	}
	printf("%.10lf\n",Ans);
}