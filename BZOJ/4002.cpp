#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const ull P=7528443412579576937ll;
const ull inv2=(P+1)>>1;

ull mul(ull a,ull b)
{
	ull ret=0;
	for(;b;b>>=1,a=(a+a)%P) if(b&1) ret=(ret+a)%P;
	return ret;
}

struct Mat{
	ull a[2][2];
	
	Mat(){memset(a,0,sizeof a);}
	ull* operator [] (int i){return a[i];}
	const ull* operator [](int i) const {return a[i];}
	
	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					(ret[i][j]+=mul(a[i][k],rhs[k][j]))%=P;
		return ret;
	}
}tr,I;

Mat ksm(Mat a,ull b)
{
	Mat ret=I;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

ull b,d,n;

int main()
{
	I[0][0]=I[1][1]=1;
	cin>>b>>d>>n;
	if(n==0) return cout<<1<<endl,0;
	tr[0][0]=mul(b,inv2);tr[0][1]=inv2;
	tr[1][0]=mul(d,inv2);tr[1][1]=mul(b,inv2);
	Mat res;
	res[0][0]=mul(b,inv2);res[0][1]=inv2;
	res=res*ksm(tr,n-1);
	ll Ans=res[0][0]*2%P;
	if(~n&1) Ans=(Ans-1+P)%P;
	cout<<Ans<<endl;
}

