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

const int MAXN=100010;
const int INF=1E9;

char str[233];
int n;

struct segment{
	double k,b;

	segment(double _k=-INF,double _b=-INF){k=_k;b=_b;}

	double operator ()(double x){return k*x+b;}
}t[MAXN<<2];

void insert(int x,int l,int r,segment S)
{
	if(S(l)<t[x](l)&&S(r)<t[x](r)) return;
	if(S(l)>t[x](l)&&S(r)>t[x](r)) return t[x]=S,void();
	int mid=(l+r)>>1;
	double dx=(S.b-t[x].b)/(t[x].k-S.k);
	if(S(l)>t[x](l))
	{
		if(dx<=mid) insert(x<<1,l,mid,S);
		else insert(x<<1|1,mid+1,r,t[x]),t[x]=S;
	}
	else
	{
		if(dx<=mid) insert(x<<1,l,mid,t[x]),t[x]=S;
		else insert(x<<1|1,mid+1,r,S);
	}
}

double query(int x,int l,int r,int p)
{
	if(l==r) return t[x](p);
	int mid=(l+r)>>1;
	if(p<=mid) return max(query(x<<1,l,mid,p),t[x](p));
	else return max(query(x<<1|1,mid+1,r,p),t[x](p));
}

int main()
{
	scanf("%d",&n);
	double S,P;int T;
	while(n--)
	{
		scanf("%s",str+1);
		if(str[1]=='P')
		{
			scanf("%lf%lf",&S,&P);
			insert(1,1,50000,segment(P,S-P));
		}
		else
		{
			scanf("%d",&T);
			printf("%d\n",max((int)floor(query(1,1,50000,T)/100),0));
		}
	}
}