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
#include<bitset>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=810;
const int MAXS=1<<16;
const int P=1E9+7;

inline int inc(int x,int y){x+=y;return x>P?x-P:x;}
inline int dec(int x,int y){x-=y;return x<0?x+P:x;}

inline void Inc(int &x,int y){x+=y;if(x>P) x-=P;}
inline void Dec(int &x,int y){x-=y;if(x<0) x+=P;}

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;(a*=a),b>>=1) if(b&1) (ret*=a)%=P;
	return ret;
}

namespace FWT{
	int t1[MAXS],t2[MAXS];
	void FWT(int *a,int n)
	{
		for(int i=2;i<=n;i<<=1)
		{
			for(int j=0;j<n;j+=i)
			{
				for(int k=0;k<(i>>1);k++)
				{
					int u=a[j+k],t=a[j+k+(i>>1)];
					a[j+k]=u;a[j+k+(i>>1)]=inc(u,t);
				}
			}
		}
	}

	void IFWT(int *a,int n)
	{
		for(int i=2;i<=n;i<<=1)
		{
			for(int j=0;j<n;j+=i)
			{
				for(int k=0;k<(i>>1);k++)
				{
					int u=a[j+k],t=a[j+k+(i>>1)];
					a[j+k]=u;a[j+k+(i>>1)]=dec(t,u);
				}
			}
		}
	}

	void multiply(int *a,int *b,int *res,int n)
	{
		assert(__builtin_popcount(n)==1);
		for(int i=0;i<n;i++)
			t1[i]=a[i],t2[i]=b[i];
		FWT(t1,n);FWT(t2,n);
		for(int i=0;i<n;i++)
			res[i]=1ll*t1[i]*t2[i]%P;
		IFWT(res,n);
	}
}

struct dat{
	int v,st;
	dat(){}
	dat(int _v,int _st){v=_v;st=_st;}
	bool operator < (const dat &rhs) const {return v<rhs.v||(v==rhs.v&&st<rhs.st);}
}st[MAXN];

int p[MAXN],mn[MAXN],mx[MAXN],n,tot,totp,G,L,q;
int pre[MAXN][MAXS],suf[MAXN][MAXS],tmp[MAXS],Res[MAXS];
map<int,int> Ans;

void dfs(int x,int cur,int sta)
{
	if(x==totp+1) 
	{
		if(cur>n) return;
		return st[++tot]=dat(cur,sta),void();
	}
	int f=ksm(p[x],mn[x]);
	for(int i=mn[x];i<=mx[x];i++,f*=p[x])
		dfs(x+1,cur*f,sta|((i==mn[x])<<(x-1))|((i==mx[x])<<(x+totp-1)));
}

int main()
{
	scanf("%d%d%d%d",&n,&G,&L,&q);
	if(L%G)
	{
		while(q--) puts("0");
		return 0;
	}
	int _L=L,_G=G;
	for(int i=2;i*i<=L;i++)
	{
		if(_L%i==0)
		{
			p[++totp]=i;
			while(!(_L%i)) 
				_L/=i,mx[totp]++;
		}
	}
	if(_L!=1)
	{
		++totp;
		p[totp]=_L;mx[totp]=1;
	}
	for(int i=1;i<=totp;i++)
		while(!(_G%p[i]))
			_G/=p[i],mn[i]++;
	dfs(1,1,0);sort(st+1,st+1+tot);
	int mxb=totp*2;
	pre[0][0]=1;
	for(int i=0;i<tot;i++)
		for(int s=0;s<1<<mxb;s++)
			Inc(pre[i+1][s|st[i+1].st],pre[i][s]),
			Inc(pre[i+1][s],pre[i][s]);
	suf[tot+1][0]=1;
	for(int i=tot+1;i>1;i--)
		for(int s=0;s<1<<mxb;s++)
			Inc(suf[i-1][s|st[i-1].st],suf[i][s]),
			Inc(suf[i-1][s],suf[i][s]);
	for(int i=1,x;i<=q;i++)
	{
		scanf("%d",&x);
		if(x%G||L%x||x>n) puts("0");
		else
		{
			if(Ans.find(x)!=Ans.end()) printf("%d\n",Ans[x]);
			else
			{
				memset(Res,0,sizeof Res);
				int p=lower_bound(st+1,st+1+tot,dat(x,0))-st;
				FWT::multiply(pre[p-1],suf[p+1],tmp,1<<mxb);
				for(int s=0;s<1<<mxb;s++)
					Inc(Res[s|st[p].st],tmp[s]);
				printf("%d\n",Ans[x]=Res[(1<<mxb)-1]);
			}
		}
	}
}