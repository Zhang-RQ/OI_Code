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

const int MAXN=62;

int m,a[MAXN],mx,d[MAXN],n;
int tms[MAXN][MAXN][MAXN*MAXN],u[MAXN];
bool f[MAXN][MAXN][MAXN*MAXN],Ans[MAXN][MAXN],vis[MAXN];
vector<int> v;

int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+m);mx=61;
	int lim=mx*(mx-1)/2;
	f[0][0][0]=1;
	int fi=-1,se=-1,th=-1;
	for(int i=0;i<m&&(!~fi);i++)
	{
		for(int j=i;j<=mx;j++)
			for(int k=j*(j-1)/2;k<=lim;k++)
				if(f[i][j][k])
					for(int l=1;l<=mx-j;l++)
					{
						f[i+1][j+l][k+l*a[i+1]]=1;
						tms[i+1][j+l][k+l*a[i+1]]=l;
					}
		if(i==m-1)
			for(int j=i+1;j<=mx;j++)
				if(f[i+1][j][j*(j-1)/2])
					{fi=i+1;se=j;th=j*(j-1)/2;break;}
	}
	if(fi==-1) return puts("=("),0;
	for(int i=fi;i>=1;i--)
	{
		for(int j=1;j<=tms[i][se][th];j++)
			v.push_back(a[i]);
		int _th=th;
		th-=tms[i][se][_th]*a[i];
		se-=tms[i][se][_th];
	}
	n=v.size();
	for(int i=0;i<n;i++)
		d[i+1]=v[i];
	sort(d+1,d+1+n);
	for (int i=1;i<=n;i++)
    {
        u[i]=i-1;
        for(int j=1;j<i;j++) Ans[i][j]=1;
    }
    for (int i,j,k,x;;)
    {
        for(i=1;i<=n&&d[i]<=u[i];i++);
        if(i>n) break;
        for(j=n;u[j]!=u[i];j--);
        for(k=1;d[k]>=u[k];k++);
        for(x=n;!(Ans[k][x] && Ans[x][j]);x--);
        Ans[k][x]=0;Ans[x][k]=1;Ans[x][j]=0;Ans[j][x]=1;u[k]--;u[j]++;
    }
	printf("%d\n",n);
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)
			printf("%d",Ans[i][j]);
}