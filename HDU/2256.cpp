#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1024;

struct Mat{
	int a[2][2];
	Mat(){memset(a,0,sizeof a);}
	int* operator [](int i){return a[i];}
	const int* operator [](int i) const {return a[i];}
	
	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					(ret[i][j]+=a[i][k]*rhs[k][j]%P)%=P;
		return ret;
	}
}tr,I;

Mat ksm(Mat a,ll b)
{
	Mat ret=I;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

void solve()
{
	int n;
	scanf("%d",&n);
	Mat res;
	res[0][0]=5;res[0][1]=2;
	res=res*ksm(tr,n-1);
	printf("%d\n",(2*res[0][0]-1+P)%P);
}

int main()
{
	I[0][0]=I[1][1]=1;
	tr[0][0]=5;tr[0][1]=2;tr[1][0]=12;tr[1][1]=5;
	int T;
	for(scanf("%d",&T);T--;solve());
}
