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

const int MAXN=1010;

int n,m,ln[MAXN],rw[MAXN];
int cnt,x[MAXN],y[MAXN];
char mp[MAXN][MAXN];
ll Ans;

ll calc(int x){return 1ll*x*(x+1)/2;}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",mp[i]+1);
		for(int j=1;j<=m;j++)
			if(mp[i][j]=='X')
				ln[i]=j,rw[j]=i,++cnt,
				x[cnt]=i,y[cnt]=j;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(mp[i][j]=='.')
				Ans+=m*(calc(i-1)+calc(n-i))+n*(calc(j-1)+calc(m-j));
	for(int i=1;i<=cnt;i++)
	{
		Ans-=m*(calc(x[i]-1)+calc(n-x[i]))+n*(calc(y[i]-1)+calc(m-y[i]));
		for(int j=1;j<=cnt;j++)
			Ans+=abs(x[i]-x[j])+abs(y[i]-y[j]);
	}
	for(int i=1;i<=n;i++)
		if(ln[i])
		{
			int lst=ln[i];
			Ans+=2ll*(ln[i]-1)*(m-ln[i]);
			for(int j=i+1;j<=n;j++)
				if(ln[j]&&ln[j]>lst)
				{
					Ans+=4ll*(ln[i]-1)*(m-ln[j]);
					lst=ln[j];
				}
				else break;
		}
	for(int i=1;i<=n;i++)
		if(ln[i])
		{
			int lst=ln[i];
			Ans+=2ll*(ln[i]-1)*(m-ln[i]);
			for(int j=i+1;j<=n;j++)
				if(ln[j]&&ln[j]<lst)
				{
					Ans+=4ll*(m-ln[i])*(ln[j]-1);
					lst=ln[j];
				}
				else break;
		}
	for(int i=1;i<=m;i++)
		if(rw[i])
		{
			int lst=rw[i];
			Ans+=2ll*(rw[i]-1)*(n-rw[i]);
			for(int j=i+1;j<=m;j++)
				if(rw[j]&&rw[j]>lst)
				{
					Ans+=4ll*(rw[i]-1)*(n-rw[j]);
					lst=rw[j];
				}
				else break;
		}
	for(int i=1;i<=m;i++)
		if(rw[i])
		{
			int lst=rw[i];
			Ans+=2ll*(rw[i]-1)*(n-rw[i]);
			for(int j=i+1;j<=m;j++)
				if(rw[j]&&rw[j]<lst)
				{
					Ans+=4ll*(n-rw[i])*(rw[j]-1);
					lst=rw[j];
				}
				else break;
		}
	int tot=n*m-cnt;
	printf("%.10lf\n",1.0*Ans/tot/tot);
}