#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=19940417;
const int inv6=3323403;

template<typename T1,typename T2>
    void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
    void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
    T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
    T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n,m;

ll S1(int n){return 1ll*n*(n+1)/2%P;}
ll S2(int n){return 1ll*n*(n+1)%P*(2*n+1)%P*inv6%P;}

int main()
{
    scanf("%d%d",&n,&m);
    ll calcn=0,calcm=0,Ans=0;
    for(int i=1,pos=0;i<=n;i=pos+1)
    {
        pos=n/(n/i);
        Inc(calcn,1ll*(n/i)*Sub(S1(pos),S1(i-1))%P);
    }
    for(int i=1,pos=0;i<=m;i=pos+1)
    {
        pos=m/(m/i);
        Inc(calcm,1ll*(m/i)*Sub(S1(pos),S1(i-1))%P);
    }
    Ans=1ll*n*m%P*n%P*m%P;
    Dec(Ans,1ll*m*m%P*calcn%P);
    Dec(Ans,1ll*n*n%P*calcm%P);
    Inc(Ans,1ll*calcn*calcm%P);
    int mn=min(n,m);
    Dec(Ans,1ll*mn*n%P*m%P);
    for(int i=1,pos=0;i<=mn;i=pos+1)
    {
        pos=min(n/(n/i),m/(m/i));
        Inc(Ans,1ll*(n/i)*Sub(S1(pos),S1(i-1))%P*m%P);
        Inc(Ans,1ll*(m/i)*Sub(S1(pos),S1(i-1))%P*n%P);
        Dec(Ans,1ll*(n/i)*(m/i)%P*Sub(S2(pos),S2(i-1))%P);
    }
    printf("%lld\n",Ans);
}
