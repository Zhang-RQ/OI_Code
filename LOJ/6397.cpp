#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const unsigned int P=2148473648;

ull tAns[20],Ans[20];

void solve()
{
	memset(Ans,0,sizeof Ans);
	memset(tAns,0,sizeof tAns);
	int ofs=0;
	ull a,b,c,d;
	scanf("%llu%llu%llu%llu",&a,&b,&c,&d);
	if(a==1) ofs++,a=0;
	else a-=2;
	if(b==1) ofs++,b=0;
	else b-=2;
	if(c==1) ofs++,c=0;
	else c-=2;
	if(d==1) ofs++,d=0;
	else d-=2;
	if(!ofs) tAns[0]=a*b%P*c%P*d%P;
	if(ofs<2) tAns[1]=(2>>ofs)*(a*b%P*c%P+a*b%P*d%P+a*c%P*d%P+b*c%P*d%P)%P;
	if(ofs<3) tAns[2]=(4>>ofs)*(a*b%P+a*c%P+a*d%P+b*c%P+b*d%P+c*d%P)%P;
	if(ofs<4) tAns[3]=(8>>ofs)*(a+b+c+d)%P;
	tAns[4]=16>>ofs;
	for(int i=0;i<5;i++) Ans[i+ofs]=tAns[i];
	for(int i=0;i<=8;i++) printf("%llu%c",Ans[i],"\n "[i!=8]);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
