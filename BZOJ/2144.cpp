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

struct dat{
	int a,b,c;
	bool operator != (const dat &rhs) const {return a!=rhs.a||b!=rhs.b||c!=rhs.c;}
	dat(int _a=0,int _b=0,int _c=0){a=_a;b=_b;c=_c;}
	void print(){printf("(%d,%d,%d)\n",a,b,c);}
};

int a,b,c,x,y,z;

pair<dat,int> jmp(dat x,int t)
{
	int cnt=0;
	while(1)
	{
		int dx=x.b-x.a,dy=x.c-x.b;
		assert(dx>0&&dy>0);
		if(dx==dy||!t) break;
		if(dx>dy)
		{
			int o=min(t,(dx-1)/dy);
			cnt+=o;t-=o;
			dx-=o*dy;
			x.b=x.a+dx;x.c=x.b+dy;
		}
		else
		{
			int o=min(t,(dy-1)/dx);
			cnt+=o;t-=o;
			dy-=o*dx;
			x.b=x.c-dy;x.a=x.b-dx;
		}
	}
	assert(t>=0);
	return make_pair(x,cnt);
}

int main()
{
	scanf("%d%d%d%d%d%d",&a,&b,&c,&x,&y,&z);
	if(a>b) swap(a,b);
	if(b>c) swap(b,c);
	if(a>b) swap(a,b);
	if(x>y) swap(x,y);
	if(y>z) swap(y,z);
	if(x>y) swap(x,y);
	dat A=dat(a,b,c),B=dat(x,y,z);
	pair<dat,int> l1=jmp(A,1<<30),l2=jmp(B,1<<30);
	if(l1.first!=l2.first) return puts("NO"),0;
	else puts("YES");
	if(l1.second<l2.second) swap(l1,l2),swap(A,B);
	int Ans=l1.second-l2.second,L=0,R=1E9,tAns=0;
	A=jmp(A,l1.second-l2.second).first;
	if(!(A!=B)) return printf("%d\n",Ans),0;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(jmp(A,mid).first!=jmp(B,mid).first) tAns=mid,L=mid+1;
		else R=mid-1;
	}
	printf("%d\n",Ans+2*tAns+2);
}