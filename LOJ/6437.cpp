#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

mt19937 RandEngine(chrono::steady_clock::now().time_since_epoch().count());

inline int RandInt(int l,int r) {return uniform_int_distribution<int>(l,r)(RandEngine);}
inline double RandDouble(double l,double r) {return uniform_real_distribution<double>(l,r)(RandEngine);}

const double EPS=1E-3;
const double PI=acos(-1);

double sqr(double x){return x*x;}
int sgn(double x){return x>EPS?1:(x<-EPS?-1:0);}

struct Vec{
	double x,y;

	Vec(double _x=0,double _y=0){x=_x;y=_y;}

	bool operator == (const Vec &rhs) const {return !sgn(x-rhs.x)&&!sgn(y-rhs.y);}
	bool operator != (const Vec &rhs) const {return sgn(x-rhs.x)||sgn(y-rhs.y);}
	double len() const {return sqrt(sqr(x)+sqr(y));}
	Vec operator + (const Vec &rhs) const {return Vec(x+rhs.x,y+rhs.y);}
	Vec operator - (const Vec &rhs) const {return Vec(x-rhs.x,y-rhs.y);}
	Vec operator * (const double &rhs) const {return Vec(x*rhs,y*rhs);}
	Vec operator / (const double &rhs) const {return Vec(x/rhs,y/rhs);}
	double operator * (const Vec &rhs) const {return x*rhs.y-y*rhs.x;}
	Vec unit() const {return (*this)/len();}
	Vec rotate(const double &theta) const {double cs=cos(theta),sn=sin(theta);return Vec(cs*x+sn*y,-sn*x+cs*y);}
	friend double dot(const Vec &lhs,const Vec &rhs) {return lhs.x*rhs.x+lhs.y*rhs.y;}
	friend double dis(const Vec &lhs,const Vec &rhs) {return sqrt(sqr(lhs.x-rhs.x)+sqr(lhs.y-rhs.y));}
};

const Vec ERR(19260817,-19260817),O;

typedef Vec Point;

struct Line{
	Point a,b;

	Line(Point _a=O,Point _b=O){a=_a;b=_b;}
	
	friend Point Inter(const Line &lhs,const Line &rhs)
	{
		Vec va=lhs.b-lhs.a,vb=rhs.b-rhs.a,u=lhs.a-rhs.a;
		if(sgn(va*vb)==0)
			return ERR;
		double t=(vb*u)/(va*vb);
		return lhs.a+va*t;
	}

	friend double Dis(const Line &L,const Point &P)
	{
		return abs((L.b-L.a)*(P-L.a)/dis(L.a,L.b));
	}
};

struct Circle{
	Point o;
	double r;

	Circle(Point _o,double _r){o=_o;r=_r;}
	
	friend pair<Point,Point> Inter(const Circle &C,const Line &L)
	{
		double d=Dis(L,C.o);
		if(sgn(C.r-d)<0)
			return make_pair(ERR,ERR);
		Vec vl=L.b-L.a,vt=Vec(vl.y,-vl.x);
		Line t=Line(C.o,C.o+vt);
		Point p=Inter(t,L);
		if(!sgn(C.r-d))
			return make_pair(p,ERR);
		double q=sqrt(sqr(C.r)-sqr(d));
		Vec dlt=(L.b-L.a).unit()*q;
		return make_pair(p-dlt,p+dlt);
	}
};

bool Chk_Pnt_On_Line(const Line &L,const Point &P)
{
	return !sgn((L.b-L.a)*(P-L.a));
}

bool Chk_Pnt_On_Seg(const Line &L,const Point &P)
{
	return Chk_Pnt_On_Line(L,P)&&sgn(dot(L.b-P,L.a-P))!=1;
}

bool Chk_On_Two_Side(const Line &L,const Point &P1,const Point &P2)
{
	Vec t=L.b-L.a;
	return sgn(t*(P1-L.a))*sgn(t*(P2-L.a))!=1;
}

bool Chk_Seg_Inter(const Line &L1,const Line &L2)//two seg intersect
{
	return (Chk_On_Two_Side(L1,L2.a,L2.b))&&(Chk_On_Two_Side(L2,L1.a,L1.b));
}

bool Pnt_In_Poly(const vector<Point> &Poly,const Point &P) //hope that P is not on Poly
{
	double theta=RandDouble(-PI,PI);
	Line L(P,P+Vec(cos(theta),sin(theta))*1E7);
	bool ret=0;
	for(int i=0;i<Poly.size();i++)
		ret^=Chk_Seg_Inter(Line(Poly[i],Poly[(i+1)%Poly.size()]),L);
	return ret;
}

pair<Point,Point> Circle_Inter_Seg(const Circle &C,const Line &L)
{
	pair<Point,Point> Ret=Inter(C,L);
	if(Ret.first!=ERR&&!Chk_Pnt_On_Seg(L,Ret.first))
		Ret.first=ERR;
	if(Ret.second!=ERR&&!Chk_Pnt_On_Seg(L,Ret.second))
		Ret.second=ERR;
	return Ret;
}

const int MAXM=610;

struct PointS{
	Point p;
	double k;

	PointS(Point _p=O)
	{
		k=atan2(_p.y,_p.x);
		if(k<0) k+=100;
		p=_p;
	}

	bool operator < (const PointS &rhs) const {return k<rhs.k;}
}Pnt[MAXM<<1];

int n,m,flag;
double Rad[MAXM];
Point Po[MAXM];
vector<Point> Poly;

double Solve(double R)
{
	if(sgn(R)==0)
		return !flag&&Pnt_In_Poly(Poly,O)?1:0;
	int tot=0;
	Circle C(O,R);
	double Ret=0;
	for(int i=1;i<=m;i++)
	{
		int nxt=i==m?1:i+1;
		auto t=Circle_Inter_Seg(C,Line(Po[i],Po[nxt]));
		if(t.first!=ERR)
			Pnt[++tot]=PointS(t.first);
		if(t.second!=ERR)
			Pnt[++tot]=PointS(t.second);
	}
	if(!tot)
	{
		double theta=RandInt(-PI,PI);
		Ret=Pnt_In_Poly(Poly,Point(cos(theta),sin(theta))*R);
		return Ret;
	}
	sort(Pnt+1,Pnt+1+tot);
	for(int i=1;i<=tot;i++)
	{
		int nxt=i==tot?1:i+1;
		double k1=Pnt[i].k>50?Pnt[i].k-100:Pnt[i].k,k2=Pnt[nxt].k>50?Pnt[nxt].k-100:Pnt[nxt].k,range=k2<k1?(k2-k1+2*PI):(k2-k1);
		double kMid=k1+range/2;
		Point p=Point(cos(kMid),sin(kMid))*R;
		if(Pnt_In_Poly(Poly,p))
			Ret+=range/PI/2;
	}
	return Ret;
}

int main()
{
	double Ans=0;
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=n;i++)
		scanf("%d%d",&x,&y),Rad[i]=sqrt(sqr(x)+sqr(y));
	for(int i=1;i<=m;i++)
	{
		scanf("%lf%lf",&Po[i].x,&Po[i].y);
		flag|=Po[i]==O;
		Poly.push_back(Po[i]);
	}
	for(int i=1;i<=n;i++)
		Ans+=Solve(Rad[i]);
	printf("%.5lf\n",Ans);
}
