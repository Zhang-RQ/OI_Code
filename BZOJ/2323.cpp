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

const int P=1E9+7;
const int MAXN=1010;

struct Mat{
	ll v[3][3];
	Mat() {memset(v,0,sizeof v);}
	ll* operator [](int i) {return v[i];}
	const ll* operator [](int i) const {return v[i];}
	inline Mat operator + (const Mat &rhs) const
	{
		Mat ret;
		ret[1][1]=(v[1][1]+rhs[1][1])%P;
		ret[1][2]=(v[1][2]+rhs[1][2])%P;
		ret[2][1]=(v[2][1]+rhs[2][1])%P;
		ret[2][2]=(v[2][2]+rhs[2][2])%P;
		return ret;
	}
	inline Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		ret[1][1]=(v[1][1]*rhs[1][1]+v[1][2]*rhs[2][1])%P;
		ret[1][2]=(v[1][1]*rhs[1][2]+v[1][2]*rhs[2][2])%P;
		ret[2][1]=(v[2][1]*rhs[1][1]+v[2][2]*rhs[2][1])%P;
		ret[2][2]=(v[2][1]*rhs[1][2]+v[2][2]*rhs[2][2])%P;
		return ret;
	}
}f[MAXN],pre[MAXN][10],T,I;

int n,t[MAXN];
char s[MAXN];

void init()
{
	T[1][1]=1,T[1][2]=1;
	T[2][1]=1,T[2][2]=0;
	I[1][1]=I[2][2]=1;
	pre[0][0]=I;pre[0][1]=T;
	for(int i=0;i<=n;i++)
	{
		if(i) pre[i][1]=pre[i-1][9]*pre[i-1][1];
		for(int j=2;j<=9;j++)
			pre[i][j]=pre[i][j-1]*pre[i][1];
	}
}

inline Mat calc(int l,int r,bool f)
{
	Mat ret=I;
	for(int i=0;i<=r-l;i++) t[i]=s[r-i]-'0';
	if(f)
	{
		int pos=0;
		for(pos=0;pos<=r-l&&t[pos]==0;pos++) t[pos]=9;
		if(pos<=r-l) t[pos]--;
	}
	for(int i=0;i<=r-l;i++)
		ret=ret*pre[i][t[i]];
	return ret;
}

int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	init();f[0]=I;
	for(int i=1;i<n;i++)
	{
		Mat t=I;
		for(int j=i;j;j--)
		{
			t=t*pre[i-j][s[j]-'0'];
			f[i]=f[i]+f[j-1]*t;
		}
	}
	for(int i=0;i<n;i++)
		f[n]=f[n]+f[i]*calc(i+1,n,1);
	Mat res;res[1][1]=0;res[1][2]=1;
	res=res*f[n];
	printf("%lld\n",res[1][1]);
}