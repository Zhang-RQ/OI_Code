#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int P=998244353;
const int g=3;

ll n,s,a[4],A[4],w[4],Ans;

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

void solve()
{
    Ans=0;
    cin>>n>>s>>a[0]>>a[1]>>a[2]>>a[3];
    A[0]=a[n%4];A[1]=a[(n+1)%4];A[2]=a[(n+2)%4];A[3]=a[(n+3)%4];
    for(int i=0;i<4;i++) 
        (Ans+=ksm(4,P-2)*(ksm(w[0]+s,n)*ksm(w[0],i)%P+ksm(w[1]+s,n)*ksm(w[1],i)%P+ksm(w[2]+s,n)*ksm(w[2],i)%P+ksm(w[3]+s,n)*ksm(w[3],i)%P)%P*A[i])%=P;
    cout<<Ans<<endl;
}

int main()
{
    w[0]=ksm(g,(P-1)/4);w[1]=w[0]*w[0]%P;w[2]=w[1]*w[0]%P;w[3]=w[2]*w[0]%P;
    int T;
    for(scanf("%d",&T);T--;solve());
}
