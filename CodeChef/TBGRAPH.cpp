#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

struct PQ{
    priority_queue<int> val,delv;

	void clear(){priority_queue<int> nv,nd;swap(nv,val);swap(nd,delv);}
	
    void pop(int x) {delv.push(x);}
	
    void push(int x) {val.push(x);}
	
    int top()
    {
        while(!delv.empty()&&delv.top()==val.top())
            delv.pop(),val.pop();
        return val.empty()?0:val.top();
    }
};

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

const int P=1E9+7;
const int MAXN=2100;
const int INF=1<<30;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

struct T{
	int tp,l,r;
};

struct dat{
	int dis,sum;

	dat(int _dis=0,int _sum=0){dis=_dis;sum=_sum;}

	dat operator + (const dat &rhs) const
	{
		if(dis!=rhs.dis)
			return dis>rhs.dis?*this:rhs;
		return dat(dis,Add(sum,rhs.sum));
	}
}f[MAXN][MAXN];

struct BIT{
	dat t[MAXN];

	void clear(int lim){memset(t,0,sizeof(dat)*(lim+5));}

	void C(int up,int p,dat v)
	{
		for(;p<=up;p+=p&(-p))
			t[p]=t[p]+v;
	}

	dat Q(int p)
	{
		dat ret(0,0);
		for(;p;p-=p&(-p))
			ret=ret+t[p];
		return ret;
	}
}Row[MAXN],Cou[MAXN];

PQ qR[MAXN],qC[MAXN];
vector<T> vR[MAXN],vC[MAXN];
int n,m,q,MxR[MAXN][MAXN],MxD[MAXN][MAXN];

void Insert_R(int p,int val) {qR[p].push(val);}

void Erase_R(int p,int val) {qR[p].pop(val);}

void Insert_C(int p,int val) {qC[p].push(val);}

void Erase_C(int p,int val) {qC[p].pop(val);}

void solve()
{
	read(n,m,q);
	for(int i=1;i<=n;i++)
		Row[i].clear(m),qC[i].clear(),vR[i].clear();
	for(int i=1;i<=m;i++)
		Cou[i].clear(n),qR[i].clear(),vC[i].clear();
	vR[0].clear();vC[0].clear();
	for(int i=1,r1,c1,r2,c2;i<=q;i++)
	{
		read(r1,c1,r2,c2);
		vR[r2-1].push_back((T){1,c1,c2});
		vR[r1-1].push_back((T){-1,c1,c2});
		vC[c2-1].push_back((T){1,r1,r2});
		vC[c1-1].push_back((T){-1,r1,r2});
	}
	for(int i=n;i;i--)
	{
		for(auto pr:vR[i])
			if(pr.tp==1)
				Insert_R(pr.l,pr.r);
			else
				Erase_R(pr.l,pr.r);
		int tmp=0;
		for(int j=1;j<=m;j++)
		{
			tmp=max(tmp,qR[j].top());
			MxR[i][j]=tmp;
		}
	}
	for(int i=m;i;i--)
	{
		for(auto pr:vC[i])
			if(pr.tp==1)
				Insert_C(pr.l,pr.r);
			else
				Erase_C(pr.l,pr.r);
		int tmp=0;
		for(int j=1;j<=n;j++)
		{
			tmp=max(tmp,qC[j].top());
			MxD[j][i]=tmp;
		}
	}
	dat Ans=dat(0,0);
	for(int s=n+m;s;s--)
	{
		int lim=min(n,s);
		for(int i=lim;i;i--)
		{
			int j=s-i;
			if(j>m||j<1)
				continue;
			f[i][j]=dat(1,1);
			dat nw=dat(-INF,0);
			if(j<m&&i+2<=MxD[i][j])
				nw=nw+Cou[j+1].Q(MxD[i][j]);
			if(i<n&&j+2<=MxR[i][j])
				nw=nw+Row[i+1].Q(MxR[i][j]);
			if(i+1<=MxD[i][j]||j+1<=MxR[i][j])
				nw=nw+f[i+1][j+1];
			nw.dis++;
			f[i][j]=f[i][j]+nw;
			Ans=Ans+f[i][j];
		}
		int ns=s+2;lim=min(n,ns);
		for(int i=lim;i;i--)
		{
			int j=ns-i;
			if(j>m||j<1)
				continue;
			Cou[j].C(n,i,f[i][j]);
			Row[i].C(m,j,f[i][j]);
		}
	}
	printf("%d %d\n",Ans.dis,Ans.sum);
}

int main()
{
	int T;
	for(read(T);T--;solve());
}
