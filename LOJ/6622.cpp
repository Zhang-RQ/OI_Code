#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=75;
const int MAXV=1<<12;
const int P=1E9+7;
const int inv2=(P+1)>>1;

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

int n,m,w,fa[MAXN],sum[MAXN];
char op[233];
ll V[MAXN][MAXN][MAXV],Final_Ans[MAXV];

namespace Mat{
	ll A[MAXN][MAXN];
	
	ll Det(int siz)
	{
		int f=1;
		for(int i=1;i<=siz;i++)
		{
			int pos=0;
			for(int j=i;j<=siz;j++)
				if(A[j][i])
				{pos=j;break;}
			if(!pos) return 0;
			if(pos!=i) f*=-1;
			for(int j=1;j<=siz;j++)
				swap(A[i][j],A[pos][j]);
			ll inv=ksm(A[i][i],P-2);
			for(int j=i+1;j<=siz;j++)
				if(A[j][i])
				{
					ll coef=A[j][i]*inv%P;
					for(int k=1;k<=siz;k++)
						Dec(A[j][k],A[i][k]*coef%P);
				}
		}
		ll Ans=1;
		for(int i=1;i<=siz;i++)
			Ans=Ans*A[i][i]%P;
		return (Ans*f+P)%P;
	}
}

void Transform(ll *a,int n)
{
	ll *ed=a+n;
	for(int i=2,b=0;i<=n;i<<=1,++b)
	{
		if(op[b]=='&')
		{
			for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
				for(int k=0;k<(i>>1);k++)
				{
					ll u=x[k],t=y[k];
					x[k]=Add(u,t);y[k]=t;
				}
		}
		else if(op[b]=='|')
		{
			for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
				for(int k=0;k<(i>>1);k++)
				{
					ll u=x[k],t=y[k];
					x[k]=u;y[k]=Add(u,t);
				}
		}
		else if(op[b]=='^')
		{
			for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
				for(int k=0;k<(i>>1);k++)
				{
					ll u=x[k],t=y[k];
					x[k]=Add(u,t);y[k]=Sub(u,t);
				}
			
		}
	}
}

void ITransform(ll *a,int n)
{
	
	ll *ed=a+n;
	for(int i=2,b=0;i<=n;i<<=1,++b)
	{
		if(op[b]=='&')
		{
			for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
				for(int k=0;k<(i>>1);k++)
				{
					ll u=x[k],t=y[k];
					x[k]=Sub(u,t);y[k]=t;
				}
		}
		else if(op[b]=='|')
		{
			for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
				for(int k=0;k<(i>>1);k++)
				{
					ll u=x[k],t=y[k];
					x[k]=u;y[k]=Sub(t,u);
				}
		}
		else if(op[b]=='^')
		{
			for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
				for(int k=0;k<(i>>1);k++)
				{
					ll u=x[k],t=y[k];
					x[k]=Add(u,t)*inv2%P;y[k]=Sub(u,t)*inv2%P;
				}
			
		}
	}
}

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",op);w=strlen(op);
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		V[x][y][z]++;V[y][x][z]++;
		x=find(x);y=find(y);
		if(x!=y)
			fa[x]=y;
	}
	for(int i=2;i<=n;i++)
		if(find(i)!=find(1))
			puts("-1"),exit(0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			Transform(V[i][j],1<<w);
	for(int s=0;s<1<<w;s++)
	{
		for(int i=1;i<=n;i++)
			sum[i]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				Inc(sum[i],V[i][j][s]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				Mat::A[i][j]=Sub((i==j)?sum[i]:0,V[i][j][s]);
		Final_Ans[s]=Mat::Det(n-1);
	}
	ITransform(Final_Ans,1<<w);
	for(int s=(1<<w)-1;~s;s--)
		if(Final_Ans[s])
			printf("%d\n",s),exit(0);
}
