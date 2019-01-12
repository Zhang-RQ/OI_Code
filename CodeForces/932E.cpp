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

const int P=1E9+7;
const int MAXK=5010;

int n,k;
ll S[MAXK][MAXK],Ans;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

int main()
{
	cin>>n>>k;
	S[0][0]=1;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=i;j++)
			S[i][j]=(S[i-1][j]*j%P+S[i-1][j-1])%P;
	ll fac=1,C=1;
	for(int i=0;i<=min(n,k);i++)
		Ans=(Ans+fac*S[k][i]%P*C%P*ksm(2,n-i)%P)%P,fac=fac*(i+1)%P,C=C*(n-i)%P*ksm(i+1,P-2)%P;
	cout<<Ans<<endl;
}