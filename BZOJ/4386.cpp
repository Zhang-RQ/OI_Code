#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const ll INF=2000000000000000000ll;
const int MAXN=125;

struct dat{
	ll x;

	dat(ll _x=0){x=_x;}

	dat operator + (const dat &rhs) const {return dat(min(x+rhs.x,INF));}

	dat operator * (const dat &rhs) const
	{
		if(x!=0&&INF/x<=rhs.x) return INF;
		return dat(min(INF,x*rhs.x));
	}

	void operator += (const dat &rhs) {*this=*this+rhs;}
};

int siz,n,m,fafa;
ll k;

struct Mat{
	dat v[MAXN][MAXN];

	dat* operator [] (int x){return v[x];}
	const dat* operator [] (int x) const {return v[x];}

	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		for(int i=0;i<=siz;i++)
			for(int j=0;j<=siz;j++)
				for(int k=0;k<=siz;k++)
				{
					ret[i][j]=ret[i][j]+v[i][k]*rhs[k][j];
					//if(fafa&&(v[i][k]*rhs[k][j]).x&&i==0&&j==siz) printf("%d ->%d -> %d dlt=%d\n",i,k,j,(v[i][k]*rhs[k][j]).x);
				}
		return ret;
	}
}tr,I,jmp[21];

int main()
{
	scanf("%d%d%lld",&n,&m,&k);
	siz=3*n+1;
	for(int i=0;i<=siz+1;i++)
		I[i][i]=1;
	for(int i=1;i<=n;i++)
	{
		tr[3*i][3*i-1]=dat(1);
		tr[3*i-1][3*i-2]=dat(1);
		tr[0][3*i]=dat(1);
		tr[3*i][siz]=dat(1);
	}
	tr[siz][siz]=dat(1);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		if(w==1) tr[3*u][3*v]+=dat(1);
		else if(w==2) tr[3*u-1][3*v]+=dat(1);
		else tr[3*u-2][3*v]+=dat(1);
	}
	jmp[0]=tr;
	for(int i=1;i<=20;i++)
		jmp[i]=jmp[i-1]*jmp[i-1];
	//for(int i=0;i<=20;i++)
	//	printf("stp=%d %lld\n",(1<<i)-2,jmp[i][0][siz].x-n);
	int Ans=0;
	Mat cur=I;
	/*for(int i=1;i<=233333;i++)
	{
		cur=cur*tr;
		printf("i=%d ways=%lld\n",i,cur[0][siz].x-n);
		if(cur[0][siz].x-n>k-1)
		{
			printf("%d\n",i);
			break;
		}
		}*/
	for(int j=20;~j;j--)
	{
		Mat tmp=cur*jmp[j];
		if(tmp[0][siz].x-n<=k-1)
			Ans+=1<<j,cur=tmp;//,printf("j=%d val=%lld\n",j,tmp[0][siz].x-n);
		}
	printf("%d\n",Ans-1);
}
