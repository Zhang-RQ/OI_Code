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

const int MAXN=1E6+10;

ll Ans;
int n,m;
char s1[MAXN],s2[MAXN];
ll sum[2][6][MAXN]; //0:AB 1:BC 2:AC 3:BA 4:CB 5:CA

bool check(char *s,int tp)
{
	if(tp==0) return *(s-1)=='R'&&*s=='B';
	if(tp==1) return *(s-1)=='B'&&*s=='G';
	if(tp==2) return *(s-1)=='R'&&*s=='G';
	if(tp==3) return *(s-1)=='B'&&*s=='R';
	if(tp==4) return *(s-1)=='G'&&*s=='B';
	if(tp==5) return *(s-1)=='G'&&*s=='R';
	return 0;
}

void solve(int len,char *s,ll S[6][MAXN])
{
	for(int i=2;i<=len;i++)
		for(int j=0;j<6;j++)
			S[j][i]=S[j][i-1]+check(s+i,j);
}

int main()
{
	scanf("%s%s",s1+1,s2+1);
	n=strlen(s1+1);m=strlen(s2+1);
	solve(n,s1,sum[0]);solve(m,s2,sum[1]);
	for(int i=1,L=1,R=1;i<=n;i++)
	{
		if(s1[i-1]==s2[L]) ++L;
		if(i!=1) ++R;
		while(s2[R]!=s1[i]&&R+1<=m) ++R;
		if(R>m) --R;
		int tmp=0;
		if(s1[i]!=s1[i-1])
			for(int j=0;j<6;j++)
				if(check(s1+i,j))
					Ans-=(tmp=sum[1][(j+3)%6][R]-sum[1][(j+3)%6][L-1]);
		Ans+=R-L+1;
	}
	printf("%lld\n",Ans);
}