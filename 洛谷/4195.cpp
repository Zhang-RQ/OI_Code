#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

unordered_map<ll,ll> mp;

ll ksm(ll a,ll b,ll P)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,y,x);y-=(a/b)*x;
}

ll inv(ll v,ll P)
{
	ll x,y;
	exgcd(v,P,x,y);
	x=(x%P+P)%P;
	return x;
}

ll exBSGS(ll a,ll b,ll P)
{
	ll dlt=0,d=0;mp.clear();
	while((d=gcd(a,P))!=1)
	{
		if(b%d)  throw -1;
		++dlt;b/=d;P/=d;
		b=b*inv(a/d,P)%P;
	}
	ll lim=sqrt(P)+5,inva=inv(a,P),Rt=sqrt(P);
	for(ll i=0,cur=b;i<=lim;i++,cur=1ll*cur*inva%P)
		if(!mp.count(cur))
			mp[cur]=i;
	ll stp=ksm(a,Rt,P);
	for(ll k=0,cur=1;k<=lim;k++,cur=1ll*cur*stp%P)
		if(mp.count(cur))
			return mp[cur]+k*Rt+dlt;
	throw -1;
}

bool solve()
{
	ll a,b,P;
	scanf("%lld%lld%lld",&a,&P,&b);
	if(a==0&&b==0&&P==0) return false;
	if(b==0) return puts("0"),true;
	ll Ans=0;
	try	{Ans=exBSGS(a,b,P);}
	catch(int e) {return puts("No Solution"),true;}
	printf("%lld\n",Ans);
	return true;
}

int main() {while(solve());}