#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1E9+7;
const int MAXN=55;
const int MAXS=MAXN<<1;

int n,siz;

struct Mat{
	ll a[MAXS][MAXS];

	Mat(){memset(a,0,sizeof a);}

	ll* operator [] (int x){return a[x];}
	const ll* operator [] (int x)const{return a[x];}

	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		for(int i=0;i<siz;i++)
			for(int j=0;j<siz;j++)
				for(int k=0;k<siz;k++)
					ret[i][j]+=a[i][k]*rhs[k][j]%P;
		for(int i=0;i<siz;i++)
			for(int j=0;j<siz;j++)
				ret[i][j]%=P;
		return ret;
	}
}trans[MAXN];

void init(string s)
{
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<n;j++)
		{
			trans[i][j+n][j+n]++;
			trans[i][(j+1)%n+n][j+n]++;
			if(s[j]!=s[(j+(i-1+n)%n)%n])
				(trans[i][(j+1)%n][j+n]+=(P-1))%=P;
			trans[i][j+n][j]++;
		}
	}
}

Mat ksm(Mat a,ll b)
{
	Mat ret;
	for(int i=0;i<siz;i++)
		ret[i][i]=1;
	for(;b;b>>=1,a=a*a)
		if(b&1)
			ret=ret*a;
	return ret;
}

class LongPalindromes{
public:
	int count(int repeats,string pattern)
	{
		n=pattern.length();siz=2*n;
		init(pattern);
		Mat T,Res;
		for(int i=0;i<siz;i++)
			T[i][i]=1;
		for(int i=1;i<=n;i++)
			T=T*trans[i];
		for(int i=0;i<n;i++)
			Res[0][i+n]=1;
		Res=Res*ksm(T,repeats);
		return Res[0][n];
	}
};
