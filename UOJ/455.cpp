#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
	{
		x=0;static char ch=get_char();
		while(!isdigit(ch)) ch=get_char();
		while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
	}

#if __cplusplus >= 201103L
	template<typename T,typename ...Args>
		inline void read(T& x,Args& ...args)
	{
		read(x);
		read(args...);
	}
#endif
}

using namespace FastIO;

const int MAXN=2E5+10;
const int INF=1<<30;

int n,m;
int x[MAXN],y[MAXN];
int w[MAXN],c[MAXN];
priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> R,P;
ll Ans,tot;

void Insert_P(int x)
{
	pair<ll,ll> val=R.top();R.pop();
	val.second--;
	Ans+=x+val.first;
	if(val.second)
		R.push(val);
	P.emplace(-x-val.first-x,1);
}

void Insert_R(int x,int w,int c)
{
	int totc=0;
	while(!P.empty()&&P.top().first+w+x<0&&c)
	{
		pair<ll,ll> val=P.top();P.pop();
		int tms=min(c,(int)val.second);
		Ans+=(w+x+val.first)*tms;
		val.second-=tms;c-=tms;
		totc+=tms;
		if(val.second)
			P.push(val);
		R.emplace(-w-x-val.first-x+w,tms);
	}
	if(totc)
		P.emplace(-w-x,totc);//-val.first+val.first
	if(c)
		R.emplace(w-x,c);
}

int main()
{
	read(n,m);
	for(int i=1;i<=n;i++)
		read(x[i]);
	for(int i=1;i<=m;i++)
		read(y[i],w[i],c[i]),tot+=c[i];
	if(tot<n)
		return puts("-1"),0;
	y[0]=-INF;c[0]=INF;
	int ptr1=1,ptr2=0;
	while(ptr1<=n&&ptr2<=m)
		if(x[ptr1]<=y[ptr2])
			Insert_P(x[ptr1]),ptr1++;
		else
			Insert_R(y[ptr2],w[ptr2],c[ptr2]),ptr2++;
	while(ptr1<=n)
		Insert_P(x[ptr1]),ptr1++;
	while(ptr2<=m)
		Insert_R(y[ptr2],w[ptr2],c[ptr2]),ptr2++;
	printf("%lld\n",Ans);
}
