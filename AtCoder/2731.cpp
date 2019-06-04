#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1E9+7;

struct Mat{
	ll a[3][3];

	Mat(){memset(a,0,sizeof a);}

	ll* operator [] (int x){return a[x];}
	const ll* operator [] (int x) const {return a[x];}

	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					ret[i][j]+=a[i][k]*rhs[k][j]%P;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				ret[i][j]%=P;
		return ret;
	}
}trans0,trans1;

Mat ksm(Mat a,ll b)
{
	Mat ret;
	ret[0][0]=ret[1][1]=ret[2][2]=1;
	for(;b;b>>=1,a=a*a)
		if(b&1)
			ret=ret*a;
	return ret;
}

int main()
{
	//not break
	trans0[0][0]=1;trans0[0][1]=1;trans0[0][2]=1;
	trans0[1][1]=1;trans0[1][2]=2;
	trans0[2][2]=1;
	//break
	trans0[2][0]+=1;trans0[2][1]+=1;trans0[2][2]+=1;
	//not break
	trans1[0][0]=1;trans1[0][1]=1;trans1[0][2]=1;
	trans1[1][1]=1;trans1[1][2]=2;
	trans1[2][2]=1;
	Mat res;
	res[0][0]=1;res[0][1]=1;res[0][2]=1;
	int n,m,x,lst=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&x);
		int dlt=x-lst-1;
		res=res*ksm(trans0,dlt)*trans1;
		lst=x;
	}
	res=res*ksm(trans0,n-lst-1);
	printf("%lld\n",res[0][2]);
}
