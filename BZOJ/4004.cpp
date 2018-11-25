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

const int P=998244353;
const double EPS=1E-10;
const int MAXN=550;

struct obj{
	int w;
	int a[MAXN];
	int& operator [] (int i){return a[i];}
	bool operator < (const obj &rhs) const {return w<rhs.w;}
}a[MAXN];

int n,m;
int b[MAXN][MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].w);
	sort(a+1,a+1+n);
	int Ans1=0,Ans2=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!a[i][j]) continue;
			if(b[j][j])
			{
				int t=1ll*a[i][j]*ksm(b[j][j],P-2)%P;
				for(int k=j;k<=m;k++)
					a[i][k]=(a[i][k]-1ll*t*b[j][k]%P+P)%P;
			}
			else
			{
				++Ans1;Ans2+=a[i].w;
				for(int k=j;k<=m;k++)
					b[j][k]=a[i][k];
				break;
			}
		}
	}
	printf("%d %d\n",Ans1,Ans2);
}