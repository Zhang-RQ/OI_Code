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

const int MAXN=2E6+10;
const int P=19930726;

int hw[MAXN],n,f[MAXN],buk[MAXN];
char s[MAXN],s2[MAXN];
ll Ans=1,k;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void manacher()
{
	for(int i=1;i<=n;i++)
		s2[i<<1]=s[i],s2[i<<1|1]='#';
	s2[1]='#';
	for(int i=1,mxR=0,pos=0;i<=(n<<1);i++)
	{
		if(i<=mxR) hw[i]=min(hw[2*pos-i],mxR-i);
		while(i-hw[i]&&s2[i-hw[i]]==s2[i+hw[i]]) ++hw[i];
		if(i+hw[i]>mxR) mxR=i+hw[i],pos=i;
	}
	for(int i=2;i<=(n<<1);i+=2)
		f[i>>1]=hw[i]-1;
}

int main()
{
	scanf("%d%lld",&n,&k);
	scanf("%s",s+1);
	manacher();
	int mx=0;
	for(int i=1;i<=n;i++)
		buk[f[i]]++,mx=max(mx,f[i]);
	for(int i=mx,cnt=0;i;i-=2)
	{
		cnt+=buk[i];
		if(cnt>k)
		{
			Ans=Ans*ksm(i,k)%P;
			k=0;break;
		}
		else
		{
			Ans=Ans*ksm(i,cnt)%P;
			k-=cnt;
		}
	}
	if(k) puts("-1");
	else printf("%lld\n",Ans);
}