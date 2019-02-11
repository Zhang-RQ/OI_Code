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
const int MAXS=110;

int SIZ;

struct Mat{
	ll v[MAXS][MAXS];

	Mat(){memset(v,0,sizeof v);}
	
	ll* operator [] (int x){return v[x];}
	const ll* operator [] (int x) const {return v[x];}

	Mat operator * (const Mat &rhs) const 
	{
		Mat ret;
		for(int i=0;i<=SIZ;i++)
			for(int j=0;j<=SIZ;j++)
				for(int k=0;k<=SIZ;k++)
					ret[i][j]+=v[i][k]*rhs[k][j]%P;
		for(int i=0;i<=SIZ;i++)
			for(int j=0;j<=SIZ;j++)
				ret[i][j]%=P;
		return ret;
	}
}I,tr;

int encode(tuple<int,int,int> x){return get<0>(x)*10000+get<1>(x)*100+get<2>(x);}

tuple<int,int,int> decode(int x){return make_tuple(x/10000,x/100%100,x%100);}

map<int,int> M;
int cst[256][256],tms[256][256];
int c,a,t,l,cnt,pt[5];
char s1[233],s2[233];
ll n;

Mat ksm(Mat a,int b)
{
	Mat ret=I;
	for(;b;b>>=1,a=a*a) if(b&1) ret=ret*a;
	return ret;
}

class ConversionMachine{
	public:
		int countAll(string word1,string word2,vector<int> costs,int maxCost)
		{
			for(int i=0;i<MAXS;i++) I[i][i]=1;
			c=costs[0];a=costs[1];t=costs[2];n=maxCost;
			cst['a']['b']=c;cst['a']['c']=c+a;
			cst['b']['c']=a;cst['b']['a']=a+t;
			cst['c']['a']=t;cst['c']['b']=t+c;
			tms['a']['b']=tms['b']['c']=tms['c']['a']=1;
			tms['a']['c']=tms['b']['a']=tms['c']['b']=2;
			l=word1.size();
			memcpy(s1+1,word1.c_str(),sizeof(char)*l);
			memcpy(s2+1,word2.c_str(),sizeof(char)*l);
			int tot=0;
			for(int i=1;i<=l;i++)
				tot+=tms[(int)s1[i]][(int)s2[i]],n-=cst[(int)s1[i]][(int)s2[i]],pt[tms[(int)s1[i]][(int)s2[i]]]++;
			if(n<0) return puts("0"),0;
			n/=c+a+t;
			for(int x=0;x<=l;x++)
				for(int y=0;y<=l-x;y++)
					M[encode(make_tuple(x,y,l-x-y))]=++cnt;
			SIZ=cnt;
			for(auto v:M)
			{
				int x,y,z;
				tie(x,y,z)=decode(v.first);
				if(x) tr[v.second][M[encode(make_tuple(x-1,y+1,z))]]=x;
				if(y) tr[v.second][M[encode(make_tuple(x,y-1,z+1))]]=y;
				if(z) tr[v.second][M[encode(make_tuple(x+1,y,z-1))]]=z;
			}
			tr[1][0]=1;tr[0][0]=1;
			Mat Res;
			Res[1][M[encode(make_tuple(pt[2],pt[1],pt[0]))]]++;
			Res=Res*ksm(tr,3*n+tot+1);
			return Res[1][0];
		}
};