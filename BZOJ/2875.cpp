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

ll n,m,a,c,X,g;

ll mul(ll a,ll b)
{
	if(a<2E9&&b<2E9) return a*b%m;
	ll ret=0;
	for(;b;b>>=1,(a+=a)%=m) if(b&1) (ret+=a)%=m;
	return ret;
}

struct Mat{
	ll v[2][2];
	Mat(){memset(v,0,sizeof v);}
	ll* operator [] (const int &i) {return v[i];}
	const ll* operator [](const int &i) const {return v[i];}
	Mat operator * (const Mat &rhs)
	{
		Mat ret;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					(ret[i][j]+=mul(v[i][k],rhs[k][j]))%=m;
		return ret;
	}
}I,base,Res;

Mat ksm(Mat a,ll b)
{
	Mat ret=I;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

int main()
{
	scanf("%lld%lld%lld%lld%lld%lld",&m,&a,&c,&X,&n,&g);
	base[0][0]=1;base[0][1]=c;base[1][1]=a;
	I[0][0]=I[1][1]=1;Res[0][0]=1;Res[0][1]=X;
	Res=Res*ksm(base,n);
	printf("%lld\n",Res[0][1]%g);
}