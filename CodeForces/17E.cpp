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
const int P=51123987;

char str[MAXN],str1[MAXN<<1];
int hw[MAXN<<1],n;
ll L[MAXN],R[MAXN],Ans,tot;

void manacher()
{
	int mxR=1,pos=1,N=n<<1;
	for(int i=1;i<=N;i++)
	{
		if(i>=mxR) hw[i]=1;
		else hw[i]=min(mxR-i,hw[2*pos-i]);
		while(i-hw[i]>0&&str1[i-hw[i]]==str1[i+hw[i]]) ++hw[i];
		if(i+hw[i]>mxR) mxR=i+hw[i],pos=i;
	}
	for(int i=1;i<=N;i++) tot+=(hw[i]>>1);
	for(int i=1;i<=N;i++) hw[i]--,hw[i]>>=1;
}

int main()
{
	scanf("%d",&n);
	scanf("%s",str+1);
	str1[1]='$';
	for(int i=1;i<=n;i++)
		str1[i<<1]=str[i],str1[i<<1|1]='$';
	manacher();
	for(int i=1;i<=n;i++)
	{
		L[i-hw[i<<1]]++,L[i+1]--;
		if(i>1&&+hw[(i<<1)-1]) L[i-hw[(i<<1)-1]]++,L[i]--;
	}
	for(int i=1;i<=n;i++)
	{
		R[i]++,R[i+hw[i<<1]+1]--;
		if(i>1&&+hw[(i<<1)-1]) R[i]++,R[i+hw[(i<<1)-1]]--;
	}
	for(int i=1;i<=n;i++) (L[i]+=L[i-1])%=P,(R[i]+=R[i-1])%=P;
	tot%=P;
	ll sumR=0;Ans=1ll*tot*(tot-1)%P*25561994%P;
	for(int i=1;i<=n;i++)
	{
		Ans=(Ans-sumR*L[i]%P+P)%P;
		(sumR+=R[i])%=P;
	}
	printf("%lld\n",Ans);
}