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

int a[MAXN][MAXN],k,n,h[MAXN][MAXN],L[MAXN],R[MAXN],stk[MAXN],top;
int X1,Y1,X2,Y2;
ll s[MAXN][MAXN],tAns;

inline ll S(int x1,int y1,int x2,int y2){return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];}

void solve(int x1,int y1,int x2,int y2)
{
	if(S(x1,y1,x2,y2)<=2*k) return printf("%d %d %d %d\n",y1,x1,y2,x2),exit(0),void();
	if(y1==y2)
	{
		if(a[x2][y2]<k) solve(x1,y1,x2-1,y2);
		else solve(x1,y1,x1,y2);
	}
	else
	{
		if(S(x1,y2,x2,y2)<k) solve(x1,y1,x2,y2-1);
		else solve(x1,y2,x2,y2);
	}
}

int main()
{
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]),s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]>2*k) h[i][j]=0;
			else h[i][j]=h[i-1][j]+1;
		}
	for(int i=1;i<=n;i++)
	{
		top=0;stk[++top]=0;
		for(int j=1;j<=n;j++)
		{
			if(!h[i][j]) {stk[++top]=j;continue;}
			while(h[i][stk[top]]>=h[i][j]) --top;
			L[j]=stk[top]+1;
			stk[++top]=j;
		}
		top=0;stk[++top]=n+1;
		for(int j=n;j>=1;j--)
		{
			if(!h[i][j]) {stk[++top]=j;continue;}
			while(h[i][stk[top]]>=h[i][j]) --top;
			R[j]=stk[top]-1;
			stk[++top]=j;
		}
		for(int j=1;j<=n;j++)
		{
			if(!h[i][j]) continue;
			if(S(i-h[i][j]+1,L[j],i,R[j])>tAns)
			{
				tAns=S(i-h[i][j]+1,L[j],i,R[j]);
				X1=i-h[i][j]+1;Y1=L[j];
				X2=i;Y2=R[j];
			}
		}
	}
	if(tAns<k) puts("NIE");
	else solve(X1,Y1,X2,Y2);
}