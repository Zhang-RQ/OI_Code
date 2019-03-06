#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1E9+7;
const int MAXN=262144;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

int n,f[MAXN],a[MAXN],Ans;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=n;i;i--)
	{
		int t=a[i];
		for(int s=t;s;s=(s-1)&t)
			Inc(Ans,f[s]),Inc(f[t],f[s]);
		Inc(f[t],1);
	}
	printf("%d\n",Ans);
}
