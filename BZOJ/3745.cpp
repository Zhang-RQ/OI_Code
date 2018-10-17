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

const int MAXN=5E5+10;
const int P=1E9;

int n,a[MAXN];
ll Ans,S1[MAXN],s1[MAXN],S2[MAXN],s2[MAXN],S3[MAXN],s3[MAXN];

void solve(int L,int R)
{
	if(L>R) return;
	if(L==R) return (Ans+=1ll*a[L]*a[L]%P)%=P,void();
	int mid=(L+R)>>1;
	solve(L,mid-1);solve(mid+1,R);
	int mn=1<<30,mx=0;
	S1[L-1]=s1[L-1]=S2[L-1]=s2[L-1]=S3[L-1]=s3[L-1]=0;
	for(int i=mid+1;i<=R;i++)
	{
		mn=min(mn,a[i]);mx=max(mx,a[i]);
		S1[i]=(S1[i-1]+1ll*mn*i%P)%P;
		s1[i]=(s1[i-1]+mn)%P;
		S2[i]=(S2[i-1]+1ll*mx*i%P)%P;
		s2[i]=(s2[i-1]+mx)%P;
		S3[i]=(S3[i-1]+1ll*mx*mn%P*i)%P;
		s3[i]=(s3[i-1]+1ll*mn*mx%P)%P;
	}
	mn=1<<30,mx=0;
	int ptr1=mid,ptr2=mid;//ptr1(mn)
	for(int i=mid,p1,p2;i>=L;i--)
	{
		mn=min(mn,a[i]);mx=max(mx,a[i]);
		while(ptr1<R&&a[ptr1+1]>=mn) ++ptr1;
		while(ptr2<R&&a[ptr2+1]<=mx) ++ptr2;
		(Ans+=1ll*(mid-i+1)*mn%P*mx%P)%=P;
		p1=min(ptr1,ptr2);p2=max(ptr1,ptr2);
		(Ans+=1ll*mn*mx%P*((1ll*(p1+3+mid-2*i)*(p1-mid)/2)%P)%P)%=P; //[mid+1,p1]
		(Ans+=(S3[R]-S3[p2]+P)%P-(s3[R]-s3[p2]+P)%P*(i-1)%P)%=P; //[p2+1,r]
		if(ptr1<ptr2) (Ans+=1ll*mx*((S1[p2]-S1[p1]+P)%P-(s1[p2]-s1[p1]+P)%P*(i-1)%P)%P)%=P;
		else (Ans+=1ll*mn*((S2[p2]-S2[p1]+P)%P-(s2[p2]-s2[p1]+P)%P*(i-1)%P)%P)%=P;
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	solve(1,n);
	printf("%lld\n",Ans);
}