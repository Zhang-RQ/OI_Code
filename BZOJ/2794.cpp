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

const int MAXN=1010;
const int MAXQ=1E5+10;

int n,q,f[MAXQ];
bool Ans[MAXQ*10];

struct ts{
	int a,b,c;
	bool operator < (const ts& rhs) const {return a<rhs.a;}
}p[MAXN];

struct Query{
	int m,s,k,id;
	bool operator < (const Query& rhs) const {return m<rhs.m;}
}Q[MAXQ*10];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&p[i].c,&p[i].a,&p[i].b);
	scanf("%d",&q);
	for(int i=1;i<=q;i++) 
		scanf("%d%d%d",&Q[i].m,&Q[i].k,&Q[i].s),Q[i].id=i;
	sort(p+1,p+1+n);sort(Q+1,Q+1+q);f[0]=1E9;
	for(int i=1,j=1;i<=q;i++)
	{
		while(j<=n&&p[j].a<=Q[i].m)
		{
			for(int k=100000;~k;k--)
				if(k+p[j].c<=100000)
					f[k+p[j].c]=max(f[k+p[j].c],min(f[k],p[j].b));
			j++;
		}
		Ans[Q[i].id]=f[Q[i].k]>Q[i].m+Q[i].s;
	}
	for(int i=1;i<=q;i++)
		puts(Ans[i]?"TAK":"NIE");
}