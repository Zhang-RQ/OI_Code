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

struct vec{
	double x,y;
	vec(double _x=0,double _y=0){x=_x;y=_y;}
	vec operator + (const vec &rhs) const {return vec(x+rhs.x,y+rhs.y);}
	vec operator * (const double &rhs) const {return vec(x*rhs,y*rhs);}
}A,B,C,D,AB,DC;

double vP,vQ,vR,la,lb;

double dis(vec a,vec b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

double solve1(vec P1)
{
	double L=0,R=lb,lstT; //dis to D
	for(int i=1;i<=233;i++)
	{
		double mid1=(L+L+R)/3,mid2=(L+R+R)/3;
		vec P2=D+DC*(mid1/lb),P3=D+DC*(mid2/lb);
		double t1=mid1/vQ+dis(P1,P2)/vR,t2=mid2/vQ+dis(P1,P3)/vR;
		lstT=t1;
		if(t1>t2) L=mid1;
		else R=mid2;
	}
	return lstT;
}

double solve2()
{
	double L=0,R=la,lstT;// dis to A
	for(int i=1;i<=233;i++)
	{
		double mid1=(L+L+R)/3,mid2=(L+R+R)/3;
		vec P1=A+AB*(mid1/la),P2=A+AB*(mid2/la);
		double t1=mid1/vP+solve1(P1),t2=mid2/vP+solve1(P2);
		lstT=t1;
		if(t1>t2) L=mid1;
		else R=mid2;
	}
	return lstT;
}

int main()
{
	int x1,y1,x2,y2;
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	A=vec(x1,y1);B=vec(x2,y2);
	AB=vec(x2-x1,y2-y1);
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	C=vec(x1,y1);D=vec(x2,y2);
	DC=vec(x1-x2,y1-y2);
	scanf("%lf%lf%lf",&vP,&vQ,&vR);
	la=dis(A,B)+1E-10;lb=dis(C,D)+1E-10;
	printf("%.2lf\n",solve2());
}