#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;

using namespace std;

void exgcd(i128 a,i128 b,i128 &x,i128&y)
{
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}

i128 inv(i128 v,i128 P)
{
	i128 x,y;
	exgcd(v,P,x,y);
	return (x%P+P)%P;
}

i128 ksm(i128 a,i128 b,i128 P)
{
	i128 ret=1;
	if(b<0) a=inv(a,P),b=-b;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

void solve()
{
	ll c1,c2,e1,e2,N;
	cin>>c1>>c2>>e1>>e2>>N;
	i128 x,y;
	exgcd(e1,e2,x,y);
	cout<<(ll)(ksm(c1,x,N)*ksm(c2,y,N)%N)<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	int T;
	for(cin>>T;T--;solve());
}
