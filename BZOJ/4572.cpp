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

const int MAXS=1<<12;
const int MAXC=7;
const int P=1E9+7;

char str[2][MAXC];
int trans[2][MAXC][3],nxt[2][MAXC],st[2][MAXC],n,m,c,q;
int f[2][MAXS][MAXC][MAXC],t[MAXS];

void inc(int& x,int y){x+=y;if(x>P) x-=P;}
void dec(int &x,int y){x-=y;if(x<0) x+=P;}

int split(int s,int bit){return (s&(1<<bit))?(s^(1<<bit)):s;}

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void solve_trans(int *s,int tr[MAXC][3],int *nx)
{
	for(int i=2,j=0;i<=c;i++)
	{
		while(j&&s[j+1]!=s[i]) j=nx[j];
		if(s[j+1]==s[i]) ++j;
		nx[i]=j;
	}
	for(int i=0;i<c;i++)
		for(int j=0,k=i;j<3;j++,k=i)
		{
			while(k&&s[k+1]!=j) k=nx[k];
			if(s[k+1]==j) ++k;
			tr[i][j]=k;
		}
}

void solve()
{
	scanf("%s%s",str[0]+1,str[1]+1);
	memset(trans,0,sizeof trans);
	for(int p=0;p<2;p++)
		for(int i=1;i<=c;i++)
			st[p][i]=str[p][i]=='W'?0:(str[p][i]=='B'?1:2);
	solve_trans(st[0],trans[0],nxt[0]);solve_trans(st[1],trans[1],nxt[1]);
	memset(f,0,sizeof f);f[m&1][0][0][0]=1;
	for(int i=1;i<=n;i++)
	{
		t[0]=0;
		for(int s=0;s<1<<m;t[++s]=0)
			for(int j=0;j<c;j++)
				for(int k=0;k<c;k++)
					inc(t[s],f[m&1][s][j][k]);
		memset(f,0,sizeof f);
		for(int s=0;s<1<<m;s++) f[0][s][0][0]=t[s];
		for(int j=0,nw;j<m;j++)
		{
			nw=j&1;memset(f[!nw],0,sizeof f[!nw]);
			for(int s=0;s<1<<m;s++)
				for(int k=0;k<c;k++)
					for(int l=0;l<c;l++)
						for(int p=0;p<3;p++)
						{
							int nk=trans[0][k][p],nl=trans[1][l][p],ns=split(s,j);
							if(nl==c&&(s&(1<<j))) continue;
							if(nl==c) nl=nxt[1][c];
							if(nk==c) ns|=1<<j,nk=nxt[0][c];
							inc(f[!nw][ns][nl][nk],f[nw][s][l][k]);
						}
		}
	}
	int Ans=ksm(3,n*m);
	for(int s=0;s<1<<m;s++)
		for(int k=0;k<c;k++)
			for(int l=0;l<c;l++)
				dec(Ans,f[m&1][s][k][l]);
	printf("%d\n",Ans);
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&c,&q);
	while(q--) solve();
}