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

const int MAXN=2010;

struct dat{
	double x,y;
	bool operator < (const dat &rhs) const {return y<rhs.y;}
}a[MAXN];

int n,m;
double f[MAXN][MAXN<<1],g[MAXN][MAXN<<1],h[MAXN],Ans;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=n;i++) scanf("%d%d",&x,&y),a[i].x=x/1000.0,a[i].y=y/1000.0;
	sort(a+1,a+1+n);
	for(int i=n;i;i--) h[i]=h[i+1]+1/a[i].y;
	if (n*2==m)
	{
        printf("%.7lf\n",h[1]);
        return 0;
    }
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		double px=a[i].x/(a[i].x+a[i].y),py=a[i].y/(a[i].x+a[i].y);
        double c=1/(a[i].x+a[i].y);
		for(int j=1;j<=n*2;j++)
		{
			if((n-i)*2>=m-j)
			{
				f[i][j]+=f[i-1][j-1]*px;
				if(j>1) f[i][j]+=f[i-1][j-2]*py;
				g[i][j]+=(g[i-1][j-1]+c*f[i-1][j-1])*px;
				if(j>1) g[i][j]+=(g[i-1][j-2]+c*f[i-1][j-2])*py;
				if((n-i)*2==m-j)
				{
					Ans+=g[i][j]+f[i][j]*h[i+1];
					f[i][j]=g[i][j]=0;
				}
			}
		}
	}
	for(int i=m+1;i<=n*2;i++) Ans+=g[n][i];
	printf("%lf\n",Ans);
}