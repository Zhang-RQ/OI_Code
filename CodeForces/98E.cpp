#include<bits/stdc++.h>

using namespace std;

const int MAXN=1010;

bool vis[MAXN][MAXN];
long double f[MAXN][MAXN];

long double F(int n,int m)
{
	if(vis[n][m]) return f[n][m];
	vis[n][m]=1;
	if(!n) return f[n][m]=1.0/(m+1);
	if(!m) return f[n][m]=1;
	long double k1=1.0*m/(m+1)*(1-F(m-1,n))-1,k2=1.0*m/(m+1)*(1-F(m-1,n))+1.0/(m+1)+F(m,n-1)-1;
	long double x=(-F(m,n-1))/(k1-k2);
	return f[n][m]=x*(1.0*m/(m+1)*(1-F(m-1,n)))+1-x;
}

int main()
{
	int n,m;
	cin>>n>>m;
	long double Ans=F(n,m);
	cout<<fixed<<setprecision(15)<<Ans<<" "<<1-Ans<<endl;
}
