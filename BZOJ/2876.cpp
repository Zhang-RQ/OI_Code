#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=10010;

int n;
double Eu,s[MAXN],k[MAXN],v1[MAXN];

double Cost(double lamda)
{
	double Ret=0;
	for(int i=1;i<=n;i++)
	{
		double L=max(0.0,v1[i]),R=1E5;
		for(int _=1;_<=70;_++)
		{
			double Mid=(L+R)/2;
			if(2*lamda*k[i]*Mid*Mid*(Mid-v1[i])>=1)
				R=Mid;
			else
				L=Mid;
		}
		Ret+=k[i]*s[i]*(L-v1[i])*(L-v1[i]);
	}
	return Ret;
}

double Calc(double lamda)
{
	double Ret=0;
	for(int i=1;i<=n;i++)
	{
		double L=max(0.0,v1[i]),R=1E5;
		for(int _=1;_<=70;_++)
		{
			double Mid=(L+R)/2;
			if(2*lamda*k[i]*Mid*Mid*(Mid-v1[i])>=1)
				R=Mid;
			else
				L=Mid;
		}
		Ret+=s[i]/L;
	}
	return Ret;
}

int main()
{
	scanf("%d%lf",&n,&Eu);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf",&s[i],&k[i],&v1[i]);
	double L=0,R=1E5;
	for(int _=1;_<=70;_++)
	{
		double Mid=(L+R)/2;
		if(Cost(Mid)>=Eu)
			L=Mid;
		else
			R=Mid;
	}
	printf("%.10lf\n",Calc(L));	
}
