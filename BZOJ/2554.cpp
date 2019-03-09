#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E4+10;

struct dat{
	double k,b;

	dat(double _k=0,double _b=0){k=_k;b=_b;}
	
	dat operator + (const dat &rhs) const {return dat(k+rhs.k,b+rhs.b);}
	dat operator - (const dat &rhs) const {return dat(k-rhs.k,b-rhs.b);}
	dat operator * (const double &rhs) const {return dat(k*rhs,b*rhs);}
	dat operator / (const double &rhs) const {return dat(k/rhs,b/rhs);}
}f[MAXN];

char str[MAXN];
double g[MAXN],F[MAXN];
int n,cnt[26];

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	if(n==1) return puts("0.0"),0;
	for(int i=1;i<=n;i++)
		cnt[str[i]-'A']++;
	f[1]=dat(1,0);
	for(int i=1;i<n;i++)
		g[i]=(1.0*n*(n-1))/(2.0*i*(n-i));
	for(int i=1;i<n;i++)
		f[i+1]=(f[i]*(2*i)-dat(0,g[i]*(2*i))-f[i-1]*(i-1))/(i+1);
	double X=-f[n].b/f[n].k,Ans=0;
	for(int i=1;i<=n;i++)
		F[i]=f[i].k*X+f[i].b;
	for(int i=0;i<26;i++)
		if(cnt[i])
			Ans+=F[cnt[i]]*cnt[i]/n;
	printf("%.1lf\n",Ans);
}
