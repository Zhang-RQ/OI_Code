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

const int MAXN=210;
const int MAXV=1<<4;
const int MAXM=(1<<MAXV)+666;
const int MAXK=(1<<MAXV);
const int P=1E9+7;

int n,tp[MAXN],ls[MAXN],rs[MAXN],cnt,rt,len;//tp=1 (lson)|(rson),tp=2 (lson)&(rson),tp=3 (lson)?(rson),tp=4 A,tp=5 B,tp=6 C,tp=7 D,tp=8 a,tp=9 b,tp=10 c,tp=11 d,tp=12 ?
ll f[MAXN][MAXM],Ans;//A(bit3),B(bit2),C(bit1),D(bit0)
char s[600];
pair<int,int> p[(1<<4)+10];

inline void add(ll& x,ll y){x+=y;if(x>P) x%=P;}

namespace FWT{
	int t1[MAXM],t2[MAXM];
	inline void FWT(int *a,int n,int tp) //1,or 2,and
	{
	    for(int i=2;i<=n;i<<=1)
	        for(int j=0;j<n;j+=i)
	            for(int k=0;k<(i>>1);k++)
	            {
	            	assert(j+k+(i>>1)<MAXM);
	                ll x=a[j+k],y=a[j+k+(i>>1)];
	                if(tp==1) a[j+k]=x,a[j+k+(i>>1)]=(x+y)%P;
	                if(tp==2) a[j+k]=(x+y)%P,a[j+k+(i>>1)]=y;
	            }
	}
	inline void UFWT(int *a,int n,int tp)
	{
	    for(int i=2;i<=n;i<<=1)
	        for(int j=0;j<n;j+=i)
	            for(int k=0;k<(i>>1);k++)
	            {
	                ll x=a[j+k],y=a[j+k+(i>>1)];
	                if(tp==1) a[j+k]=x,a[j+k+(i>>1)]=(y-x+P)%P;
	                if(tp==2) a[j+k]=(x-y+P)%P,a[j+k+(i>>1)]=y;
	            }
	}
	inline void solve(ll *a,ll *b,ll *res,int n,int tp)
	{
		for(int i=0;i<MAXM;i++) t1[i]=a[i],t2[i]=b[i];
	    FWT(t1,n,tp);FWT(t2,n,tp);
	    for(int i=0;i<n;i++) t1[i]=1ll*t1[i]*t2[i]%P;
	    UFWT(t1,n,tp);
	    for(int i=0;i<n;i++) add(res[i],t1[i]);
	}
}

void build(int &x,int L,int R)
{
	x=++cnt;
	if(L==R)
	{
		switch(s[L])
		{
			case 'A':tp[x]=4;break;
			case 'B':tp[x]=5;break;
			case 'C':tp[x]=6;break;
			case 'D':tp[x]=7;break;
			case 'a':tp[x]=8;break;
			case 'b':tp[x]=9;break;
			case 'c':tp[x]=10;break;
			case 'd':tp[x]=11;break;
			case '?':tp[x]=12;break;
		}
		return;
	}
	int tmp=0,pos=L;
	for(int i=L;i<=R;i++)
	{
		if(s[i]=='('||s[i]==')')
			tmp+=s[i]=='('?1:-1;
		if(tmp==0) {pos=i;break;}
	}
	++pos;assert(s[pos]!='(');assert(s[pos]!=')');
	switch(s[pos])
	{
		case '|':tp[x]=1;break;
		case '&':tp[x]=2;break;
		case '?':tp[x]=3;break;
	}
	build(ls[x],L+1,pos-2);build(rs[x],pos+2,R-1);
}

void dfs(int x)
{
	if(ls[x])
	{
		dfs(ls[x]),dfs(rs[x]);
		if(tp[x]==1) FWT::solve(f[ls[x]],f[rs[x]],f[x],MAXK,1);
		else if(tp[x]==2) FWT::solve(f[ls[x]],f[rs[x]],f[x],MAXK,2);
		else FWT::solve(f[ls[x]],f[rs[x]],f[x],MAXK,1),FWT::solve(f[ls[x]],f[rs[x]],f[x],MAXK,2);
	}
	else
	{
		switch(tp[x])
		{
			case 4:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if((s>>3)&1)
						S|=1<<s;
				f[x][S]=1;
				break;
			}
			case 5:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if((s>>2)&1)
						S|=1<<s;
				f[x][S]=1;
				break;
			}
			case 6:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if((s>>1)&1)
						S|=1<<s;
				f[x][S]=1;
				break;
			}
			case 7:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if((s)&1)
						S|=1<<s;
				f[x][S]=1;
				break;
			}
			case 8:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if(!((s>>3)&1))
						S|=1<<s;
				f[x][S]=1;
				break;
			}
			case 9:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if(!((s>>2)&1))
						S|=1<<s;
				f[x][S]=1;
				break;
			}
			case 10:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if(!((s>>1)&1))
						S|=1<<s;
				f[x][S]=1;
				break;
			}
			case 11:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if(!(((s)&1)))
						S|=1<<s;
				f[x][S]=1;
				break;
			}
			case 12:
			{
				int S=0;
				for(int s=0;s<MAXV;s++)
					if((s>>3)&1)
						S|=1<<s;
				f[x][S]++;S=0;
				for(int s=0;s<MAXV;s++)
					if((s>>2)&1)
						S|=1<<s;
				f[x][S]++;S=0;
				for(int s=0;s<MAXV;s++)
					if((s>>1)&1)
						S|=1<<s;
				f[x][S]++;S=0;
				for(int s=0;s<MAXV;s++)
					if((s)&1)
						S|=1<<s;
				f[x][S]++;S=0;
				for(int s=0;s<MAXV;s++)
					if(!((s>>3)&1))
						S|=1<<s;
				f[x][S]++;S=0;
				for(int s=0;s<MAXV;s++)
					if(!((s>>2)&1))
						S|=1<<s;
				f[x][S]++;S=0;
				for(int s=0;s<MAXV;s++)
					if(!((s>>1)&1))
						S|=1<<s;
				f[x][S]++;S=0;
				for(int s=0;s<MAXV;s++)
					if(!((s)&1))
						S|=1<<s;
				f[x][S]++;S=0;
				break;
			}
		}
	}
}

int main()
{
	scanf("%s",s+1);len=strlen(s+1);
	build(rt,1,len);dfs(rt);
	scanf("%d",&n);
	for(int i=1,a,b,c,d,e;i<=n;i++)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
		p[i].first=(a<<3)|(b<<2)|(c<<1)|d;
		p[i].second=e;
	}
	for(int s=0;s<MAXM;s++)
	{
		int fafa=1;
		for(int i=1;i<=n;i++)
			if(((s>>p[i].first)&1)!=p[i].second)
				{fafa=0;break;}
		if(fafa) add(Ans,f[rt][s]);
	}
	cout<<Ans%P<<endl;
}