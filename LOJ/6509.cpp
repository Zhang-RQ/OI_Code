#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int P=1E9+7;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

struct dat{
	ll a,b,c;//ax+by+c

	dat(ll _a=0,ll _b=0,ll _c=0){a=_a;b=_b;c=_c;}

	dat operator + (const dat &rhs) const {return dat(Add(a,rhs.a),Add(b,rhs.b),Add(c,rhs.c));}
	dat operator - (const dat &rhs) const {return dat(Sub(a,rhs.a),Sub(b,rhs.b),Sub(c,rhs.c));}
	dat operator * (const ll &rhs) const {return dat(a*rhs%P,b*rhs%P,c*rhs%P);}
}f[MAXN][2];

char str[MAXN];
int n,siz[MAXN],st[MAXN],cnt;
ll Ans[MAXN],fAns,val[2];
vector<int> T[MAXN];

pair<ll,ll> solve(dat e1,dat e2)
{
	dat t=e1-e2*(e1.a*ksm(e2.a,P-2)%P);
	assert(t.a==0);
	ll y=(P-t.c)*ksm(t.b,P-2)%P;
	ll x=Sub(P-e1.c,e1.b*y%P)*ksm(e1.a,P-2)%P;
	assert((e1.a*x+e1.b*y+e1.c)%P==0);
	assert((e2.a*x+e2.b*y+e2.c)%P==0);
	return make_pair(x,y);
}

void dfsi(int x,int fa,int dep)
{
	Ans[1]+=dep;siz[x]=1;
	for(int v:T[x])
		if(v!=fa)
			dfsi(v,x,dep+1),
			siz[x]+=siz[v];
}

void dfs(int x,int fa)
{
	if(fa)
		Ans[x]=Ans[fa]+n-2*siz[x];
	for(int v:T[x])
		dfs(v,x);
	Inc(fAns,Ans[x]*val[st[x]]%P);
}

int main()
{
	scanf("%d",&n);
	scanf("%s",str+1);
	for(int i=1;i<=n;i++)
		st[i]=str[i]=='1',
		cnt+=st[i];
	for(int i=2,f;i<=n;i++)
		scanf("%d",&f),T[f].push_back(i);
	f[1][0]=dat(1,0,0);
	f[1][1]=dat(0,1,0);
	for(int i=2;i<n;i++)
	{
		f[i][1]=(f[i-1][1]*n-f[i-2][1]*(i-2)-f[i-2][0]-dat(0,0,i!=2))*ksm(n-i+1,P-2);
		f[i][0]=(f[i-1][0]*n-f[i-2][0]*(i-1)-f[i][1]-dat(0,0,1))*ksm(n-i,P-2);
	}
	ll x,y;
	tie(x,y)=solve(f[n-1][0]*n-f[n-2][0]*(n-1),f[n-1][1]*n-f[n-2][1]*(n-2)-f[n-2][0]-dat(0,0,1));
	val[0]=Add(Add(f[cnt][0].a*x%P,Add(f[cnt][0].b*y%P,f[cnt][0].c)),ksm(n,P-2));
	val[1]=Add(Add(f[cnt][1].a*x%P,Add(f[cnt][1].b*y%P,f[cnt][1].c)),ksm(n,P-2));
	dfsi(1,0,0);dfs(1,0);
	printf("%lld\n",fAns*ksm(n,P-2)%P);
}
