#include<cstdio>
#include<cstring>
#include<cmath>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

double f[2][110];

int min(int x,int y){return x<y?x:y;}

int main()
{
	int c,n,m;
	while(~scanf("%d",&c))
	{
		if(!c)
			break;
		scanf("%d%d",&n,&m);
		if(m>c)
		{
			printf("0.000\n");
			continue;
		}
		memset(f,0,sizeof f);
		f[0][0]=1;int lst=0;
		for(int i=1;i<=min(n,1000+(n&1));i++)
		{
			memset(f[!lst],0,sizeof f[!lst]);
			for(int i=0;i<=c;i++)
			{
				if(fabs(f[lst][i])<1E-6)
					continue;
				if(i==0)
					f[!lst][1]+=f[lst][i];
				else if(i==c)
					f[!lst][i-1]+=f[lst][i];
				else
					f[!lst][i+1]+=f[lst][i]*(c-i)/c,
					f[!lst][i-1]+=f[lst][i]*i/c;
			}
			lst^=1;
		}
		printf("%.3f\n",f[lst][m]);
	}
}
