#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int MAXD=3010;
const int MAXN=500;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

void chmax(int &x,int y){if(x<y) x=y;}

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

int n,a[MAXN],lim;
ll fac[MAXN],ifac[MAXN],C[10][10],f[110][410][MAXD];

struct Mat{
	int v[3][3];

	Mat(){memset(v,0xcf,sizeof v);}

	bool operator == (const Mat &rhs) const
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(v[i][j]!=rhs.v[i][j])
					return false;
		return true;
	}

	bool operator < (const Mat &rhs) const
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(v[i][j]!=rhs.v[i][j])
					return v[i][j]<rhs.v[i][j];
		return false;
	}

	bool chk() const
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(v[i][j]==4)
					return 1;
		return 0;
	}

	void Update(const Mat &rhs)
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				v[i][j]=max(v[i][j],rhs.v[i][j]);
	}
	
	Mat Append(int c) const 
	{
		Mat Ret;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(v[i][j]>=0)
					for(int k=0;k<3&&i+j+k<=c;k++)
						chmax(Ret.v[j][k],min(v[i][j]+i+(c-i-j-k>2),4));
		return Ret;
	}
};

struct node{
	int t,son[5];
	Mat m0,m1;

	node(){t=son[0]=son[1]=son[2]=son[3]=son[4]=0;}

	bool chk() const {return t==-1||t>=7||m1.chk();}

	bool operator == (const node &rhs) const {return t==rhs.t&&m0==rhs.m0&&m1==rhs.m1;}

	bool operator < (const node &rhs) const
	{
		if(t!=rhs.t) return t<rhs.t;
		else if(!(m0==rhs.m0)) return m0<rhs.m0;
		else return m1<rhs.m1;
	}
	
	node Append(int c)
	{
		node ret;
		ret.t=t+(c>1);
		ret.m0=m0.Append(c);
		ret.m1=m1.Append(c);
		if(c>1) ret.m1.Update(m0.Append(c-2));
		return ret;
	}
};

struct Mahjong_Automaton{
	node t[MAXD];
	map<node,int> idx;
	int cnt;

	int get_id(const node &x) {return idx.count(x)?idx[x]:(t[idx[x]=++cnt]=x,cnt);}

	void build()
	{
		t[1].m0.v[0][0]=0;
		idx[t[1]]=1;
		t[2].t=-1;
		idx[t[2]]=2;
		cnt=2;
		for(int i=1;i<=cnt;i++)
			if(i!=2)
				for(int j=0;j<=4;j++)
				{
					node Nxt=t[i].Append(j);
					if(Nxt.chk()) t[i].son[j]=2;
					else t[i].son[j]=get_id(Nxt);
				}
	}

	void DP()
	{
		f[0][0][1]=1;
		int up=4*n-13;
		for(int i=0;i<n;i++)
			for(int j=0;j<=up;j++)
				for(int k=1;k<=cnt;k++)
				{
					if(k==2||!f[i][j][k]) continue;
					for(int l=0;l<=4-a[i+1];l++)
						f[i+1][j+l][t[k].son[l+a[i+1]]]=(f[i+1][j+l][t[k].son[l+a[i+1]]]+C[4-a[i+1]][l]*f[i][j][k])%P;
				}
	}
}M;

int main()
{
	scanf("%d",&n);lim=(n<<2)-13;
	for(int i=1,x;i<=13;i++)
		scanf("%d%*d",&x),a[x]++;
	for(int i=0;i<=5;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=Add(C[i-1][j-1],C[i-1][j]);
	}
	M.build();M.DP();
	ll Ans=1;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=lim;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[lim]=ksm(fac[lim],P-2);
	for(int i=lim-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(int j=1;j<=lim;j++)
		for(int k=1;k<=M.cnt;k++)
			if(k!=2)
				Inc(Ans,fac[j]*fac[lim-j]%P*ifac[lim]%P*f[n][j][k]%P);
	printf("%lld\n",Ans);
}
