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
#include<iomanip>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXS=110;

int siz;

struct Mat{
	long double a[MAXS][MAXS];

	Mat(){memset(a,0,sizeof a);}
	long double* operator [] (int i) {return a[i];}
	const long double * operator [] (int i) const {return a[i];}

	Mat operator * (const Mat &rhs) const 
	{
		Mat ret;
		for(int i=0;i<=siz;i++)
			for(int j=0;j<=siz;j++)
				for(int k=0;k<=siz;k++)
					ret[i][j]+=a[i][k]*rhs[k][j];
		return ret;
	}
}bs;

char s[MAXS];
int son[MAXS][26],cnt,rt,ban[MAXS],fail[MAXS],n,l,al;

void insert()
{
	int x=rt;
	for(int i=1;s[i];i++)
	{
		if(!son[x][s[i]-'a']) son[x][s[i]-'a']=++cnt;
		x=son[x][s[i]-'a'];
	}
	ban[x]=1;
}

void build()
{
	queue<int> q;
	for(int i=0;i<26;i++)
		if(son[rt][i])
			q.push(son[rt][i]);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		ban[x]|=ban[fail[x]];
		for(int i=0;i<26;i++)
			if(son[x][i]) fail[son[x][i]]=son[fail[x]][i],q.push(son[x][i]);
			else son[x][i]=son[fail[x]][i];
	}
}

Mat ksm(Mat a,ll b)
{
	Mat ret;
	for(int i=0;i<=siz;i++) ret[i][i]=1;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

int main()
{
	scanf("%d%d%d",&n,&l,&al);
	for(int i=1;i<=n;i++) scanf("%s",s+1),insert();
	siz=cnt+1;build();
	for(int i=0;i<=cnt;i++)
	{
		for(int j=0;j<al;j++)
		{
			if(!ban[son[i][j]]) bs[i][son[i][j]]+=(long double)1.0/al;
			else bs[i][0]+=(long double)1.0/al,bs[i][siz]+=(long double)1.0/al;
		}
	}
	bs[siz][siz]=1;
	Mat Res;
	Res[1][0]=1;
	Res=Res*ksm(bs,l);
	cout<<fixed<<setprecision(10)<<Res[1][cnt+1]<<endl;
}