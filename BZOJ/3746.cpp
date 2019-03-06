#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E6+10;
const int P=1E9+7;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

bool ban[MAXN][7];
int n,k,p,f[MAXN],g[MAXN],a[MAXN];

bool ok(int x,int y){return abs(x-y)<=3&&!ban[x][3+x-y];}

void calc(int o)
{
	for(int i=n-o;i<=n;i++) a[i-n+o+1]=i;
	do
	{
		bool okf=1;
		for(int i=1;i<=o;i++) if(!ok(a[i],a[i+1])) okf=0;
		if(!okf) continue;
		if(a[1]==n-o&&a[o+1]==n-o+1) f[n-o]++;
		if(a[1]==n-o+1&&a[o+1]==n-o) g[n-o]++;
	}while(next_permutation(a+1,a+o+2));
}

void solve3()
{
	if(n<=8)
	{
		int Ans=0;
		for(int i=1;i<=n;i++) a[i]=i;
		do
		{
			bool f=1;
			for(int i=1;i<n;i++) if(abs(a[i]-a[i+1])>3||!ok(a[i],a[i+1])) f=0;
			if(!ok(a[n],a[1])) f=0;
			Ans+=f;
		}while(next_permutation(a+1,a+n));
		printf("%d\n",Ans);
	}
	else
	{
		for(int i=1;i<=8;i++) calc(i);
		for(int i=9;i<n;i++)
		{
			int *tf=&f[n-i],*tg=&g[n-i],pi=n-i;
			if(ok(pi+2,pi)) Inc(tg[0],tf[1]);
			if(ok(pi+1,pi+2)&&ok(pi+3,pi)) Inc(tg[0],tf[2]);
			if(ok(pi+1,pi+4)&&ok(pi+5,pi+2)&&ok(pi+2,pi+3)&&ok(pi+3,pi)) Inc(tg[0],tf[4]);
			if(ok(pi+1,pi+4)&&ok(pi+4,pi+2)&&ok(pi+2,pi+5)&&ok(pi+6,pi+3)&&ok(pi+3,pi)) Inc(tg[0],tf[5]);

			if(ok(pi,pi+2)) Inc(tf[0],tg[1]);
			if(ok(pi,pi+3)&&ok(pi+2,pi+1)) Inc(tf[0],tg[2]);
			if(ok(pi,pi+3)&&ok(pi+3,pi+2)&&ok(pi+2,pi+5)&&ok(pi+4,pi+1)) Inc(tf[0],tg[4]);
			if(ok(pi,pi+3)&&ok(pi+3,pi+6)&&ok(pi+5,pi+2)&&ok(pi+2,pi+4)&&ok(pi+4,pi+1)) Inc(tf[0],tg[5]);
		}
		int Ans=ok(2,1)?f[1]:0;
		if(ok(1,2)&&ok(3,1)) Inc(Ans,f[2]);
		if(ok(1,4)&&ok(5,2)&&ok(2,3)&&ok(3,1)) Inc(Ans,f[4]);
		if(ok(1,4)&&ok(4,2)&&ok(2,5)&&ok(6,3)&&ok(3,1)) Inc(Ans,f[5]);
		if(ok(1,2)&&ok(2,3)&&ok(4,1)) Inc(Ans,f[3]);
		if(ok(1,2)&&ok(2,5)&&ok(6,3)&&ok(3,4)&&ok(4,1)) Inc(Ans,f[5]);
		if(ok(1,3)&&ok(3,6)&&ok(5,2)&&ok(2,4)&&ok(4,1)) Inc(Ans,g[5]);
		if(ok(1,2)&&ok(2,5)&&ok(5,3)&&ok(3,6)&&ok(7,4)&&ok(4,1)) Inc(Ans,f[6]);
		if(ok(1,3)&&ok(3,2)&&ok(2,5)&&ok(4,1)) Inc(Ans,g[4]);
		printf("%d\n",Ans);
	}
}

int main()
{
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1,x,y;i<=k;i++)
	{
		scanf("%d%d",&x,&y);
		if(p==3) x=n-x+1,y=n-y+1;
		if(abs(x-y)>3) continue;
		ban[x][3+x-y]=1;
	}
	if(p==0) puts(n==1?"1":"0");
	else if(p==1) puts(n<=2&&ok(1,2)&&ok(2,1)?"1":"0");
	else if(p==2)
	{
		if(n==1) puts("1");
		else if(n==2) puts(ok(1,2)&&ok(2,1)?"1":"0");
		else
		{
			int cnt=1,f=1,Ans=0;
			a[1]=n;
			for(int i=n-1-(n&1);i>=1;i-=2) a[++cnt]=i;
			for(int i=2;i<=n-(~n&1);i+=2) a[++cnt]=i;
			for(int i=2;i<=n;i++) f&=ok(a[i-1],a[i]);
			f&=ok(a[n],a[1]);
			Ans+=f;
			f=cnt=1;
			for(int i=n-1-(~n&1);i>=1;i-=2) a[++cnt]=i;
			for(int i=1;i<=n-(n&1);i+=2) a[++cnt]=i;
			for(int i=2;i<=n;i++) f&=ok(a[i-1],a[i]);
			f&=ok(a[n],a[1]);
			Ans+=f;
			printf("%d\n",Ans);
		}
	}
	else solve3();
}
