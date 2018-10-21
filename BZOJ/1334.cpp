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

const int MAXN=310;
const int MAXM=50010;

int a[MAXN],f[MAXM],n,s;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),s+=a[i];
	sort(a+1,a+1+n,greater<int>());
	f[0]=1;int Ans=0;
	for(int i=1;i<=n;i++)
		for(int j=s/2+a[i];j>=a[i];j--)
			if(f[j-a[i]])
				f[j]=1,Ans=max(Ans,j);
	printf("%d\n",Ans);
}