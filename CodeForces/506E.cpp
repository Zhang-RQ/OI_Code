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

const int MAXS=210;
const int MAXK=605;
const int P=1E4+7;

char str[MAXS];
int siz,h[MAXS][MAXS][MAXS],n,s,g[MAXS],Ans;

inline void inc(int &x,int y){x+=y;if(x>P) x-=P;}

inline void dec(int &x,int y){x-=y;if(x<0) x+=P;}

struct Mat{
	int v[MAXK][MAXK];
	
	Mat(){memset(v,0,sizeof v);}

	int* operator [] (int i){return v[i];}
	
	const int* operator [] (int i) const {return v[i];}

	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		for(int i=1;i<=siz;i++)
			for(int k=i;k<=siz;k++)
				for(int j=k;j<=siz;j++)
					inc(ret[i][j],v[i][k]*rhs[k][j]%P);
		return ret;
	}

	void print()
	{
		for(int i=1;i<=siz;i++)
			for(int j=1;j<=siz;j++)
				printf("%d%c",v[i][j],j==siz?'\n':' ');
	}
}I,b,f;

int get_f(int cnt24,int cnt25){return cnt25?f[s-cnt24+1][s+(s+1)/2+cnt25]:f[s-cnt24+1][s+s+1];}

Mat ksm(Mat a,ll b)
{
	Mat ret=I;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

int main()
{
	scanf("%s%d",str+1,&n);
	s=strlen(str+1);n+=s;
	h[0][1][s]=1;siz=2*s+3;
	for(int i=1;i<=siz;i++)
		I[i][i]=1;
	for(int i=1;i<=s;i++)
		for(int j=s;j>=i;j--)
			for(int k=0;k<=s;k++)
			{
				if(str[i]==str[j]) inc(h[k][i+1][j-1],h[k][i][j]);
				if(k<s&&str[i]!=str[j])
					inc(h[k+1][i+1][j],h[k][i][j]),inc(h[k+1][i][j-1],h[k][i][j]);
			}
	for(int i=0;i<=s;i++)
		for(int j=1;j<=s;j++)
		{
			inc(g[i],h[i][j][j]);
			if(j<s&&str[j]==str[j+1]) inc(g[i],h[i][j][j+1]);
		}
	for(int i=1;i<=s;i++)
	{
		b[i][i+1]=1;
		b[i][i]=24;
	}
	for(int i=s+1;i<=s+(s+1)/2;i++)
	{
		b[i][i+(s+1)/2]=1;
		if(i<s+(s+1)/2) b[i][i+1]=1;
		b[i][i]=25;
		b[i+(s+1)/2][i+(s+1)/2]=26;
		
	}
	b[s][s+s+3]=1;
	f=ksm(b,(n>>1));
	if(~n&1)
	{
		for(int i=0;i<=s;i++)
			inc(Ans,1ll*get_f(i,(s-i+1)/2)*g[i]%P);
	}
	else
	{
		for(int i=0;i<=s;i++)
			for(int j=2;j<=s+1;j++)
				if((~(s-i))&1)
					dec(Ans,1ll*h[i][j][j-1]*f[s-i+1][s+(s-i+1)/2]%P);
		f=f*b;
		for(int i=0;i<=s;i++)
			inc(Ans,1ll*get_f(i,(s-i+1)/2)*g[i]%P);
	}
	printf("%d\n",Ans);
}