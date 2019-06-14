#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;

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

int n,m,C[MAXN],TST;
pair<int,int> t[MAXN];

void solve()
{
	read(n,m);
	for(int i=1;i<=n;i++)
		read(t[i].first,t[i].second);
	for(int i=1;i<=m;i++)
		read(C[i]);
	sort(t+1,t+n+1);
	sort(C+1,C+m+1);
	int Ans=0,ptr=1;
	priority_queue<int,vector<int>,greater<int> > pq;
	for(int i=1;i<=m;i++)
	{
		while(ptr<=n&&t[ptr].first<=C[i])
			pq.push(t[ptr++].second);
		while(!pq.empty()&&pq.top()<C[i])
			pq.pop();
		if(pq.empty())
			return printf("Case #%d: IMPOSSIBLE!\n",++TST),void();
		Ans=max(Ans,(int)(n-pq.size()+1));	
		pq.pop();
	}
	if(Ans>n)
		printf("Case #%d: IMPOSSIBLE!\n",++TST);
	else
		printf("Case #%d: %d\n",++TST,Ans);
}

int main()
{
	int T;
	for(read(T);T--;solve());
}
