#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

int a,b,n,m;

struct Mat{
	ll a[2][2];
	
	Mat(){memset(a,0,sizeof a);}
	ll* operator [] (int i){return a[i];}
	const ll* operator [] (int i) const {return a[i];}
	
	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					(ret[i][j]+=a[i][k]*rhs[k][j]%m)%=m;
		return ret;
	}
}tr,I;

Mat ksm(Mat a,ll b)
{
	Mat ret=I;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

int main()
{
	I[0][0]=I[1][1]=1;
	ios::sync_with_stdio(0);
	while(cin>>a>>b>>n>>m)
	{
		tr[0][0]=a;tr[1][0]=b;
		tr[0][1]=1;tr[1][1]=a;
		Mat res;
		res[0][0]=a;res[0][1]=1;
		res=res*ksm(tr,n-1);
		cout<<res[0][0]*2%m<<endl;
	}
}

