#include<cstdio>
#include<cstdlib>

typedef long long ll;
typedef unsigned long long ull;

int n,v,t;

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(x==v) ++t;
		else if(--t<=0) v=x,t=1;
	}
	printf("%d\n",v);
}