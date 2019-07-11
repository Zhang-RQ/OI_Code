#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1010;
const int MAXV=1E5+10;
const int P=998244353;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n,k,a[MAXN];
int f[MAXN][MAXN],sum[MAXN];
ll Ans;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	int lst=0;
	for(int s=a[n]/(k-1);~s;s--)
	{
		for(int i=1;i<=k;i++)
			sum[i]=0;
		int ptr=0,tot=0;
		for(int i=1;i<=n;i++)
		{
			while(ptr+1<=i&&a[i]-a[ptr+1]>=s)
			{
				++ptr;
				for(int j=1;j<=k;j++)
					Inc(sum[j],f[ptr][j]);
			}
			for(int j=1;j<=k;j++)
				f[i][j]=sum[j-1];
			Inc(f[i][1],1);
			Inc(tot,f[i][k]);
		}
		Inc(Ans,1ll*Sub(tot,lst)*s%P);
		lst=tot;
	}
	printf("%lld\n",Ans);
}
