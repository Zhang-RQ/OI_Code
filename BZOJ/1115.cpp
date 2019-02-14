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

int n;

void solve()
{
	int xs=0,lst=0,x=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if((n-i+1)&1) xs^=x-lst;
		lst=x;
	}
	cout<<(xs?"TAK":"NIE")<<endl;
}

int main()
{
	int T;
	for(cin>>T;T--;solve());
}