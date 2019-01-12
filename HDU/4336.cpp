#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=22;

int n;
double P[MAXN],Ans;

int main()
{
	while(cin>>n)
	{
		for(int i=0;i<n;i++) cin>>P[i];
		Ans=0;
		for(int s=1;s<1<<n;s++)
		{
			int cnt=0;
			double sum=0;
			for(int i=0;i<n;i++)
				if((s>>i)&1)
					++cnt,sum+=P[i];
			Ans+=(cnt&1?1.0:-1.0)/sum;
		}
		cout<<fixed<<setprecision(10)<<Ans<<endl;
	}
}

