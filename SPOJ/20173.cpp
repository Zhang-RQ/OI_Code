#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#define ll long long
ll n,sig[100000005],N,a[200005];
int p[10000005];
bool mark[100000005];
char mul[100000005];
int smu[100000005],L;
int read(){
    int t=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while ('0'<=ch&&ch<='9'){t=t*10+ch-'0';ch=getchar();}
    return t*f;
}
ll Read(){
    ll t=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while ('0'<=ch&&ch<='9'){t=t*10+ch-'0';ch=getchar();}
    return t*f;
}
void Init(int n){
    sig[1]=1;smu[1]=1;mul[1]=1;
    for (int i=2;i<=n;i++){
        if (!mark[i]){
            p[++p[0]]=i;
            mul[i]=-1;
            smu[i]=1;
            sig[i]=2;
        }
        for (int j=1;j<=p[0]&&p[j]*i<=n;j++){
            mark[p[j]*i]=1;
            if (i%p[j]==0){
                sig[p[j]*i]=sig[i]/(smu[i]+1)*(smu[i]+2);
                smu[p[j]*i]=smu[i]+1;
                mul[p[j]*i]=0;
                break;
            }
            sig[p[j]*i]=sig[i]*2;
            smu[p[j]*i]=1;
            mul[p[j]*i]=-mul[i];
        }
    }
    for (int i=1;i<=n;i++) sig[i]+=sig[i-1],smu[i]=smu[i-1]+std::abs((int)mul[i]);
}

ll R(ll x){
    if (x<=L) return sig[x];
    ll res=0;
    for (ll i=1,j;i<=x;i=j+1){
        j=(x/(x/i));
        res+=(j-i+1)*(x/i);
    }
    return res;
}
ll Smu(ll x){
    if (x<=L) return smu[x];
    ll res=0;
    for (ll i=1;i*i<=x;i++)
     if (mul[i]) res+=mul[i]*(x/(i*i));
    return res; 
}
void solve(ll n){
    int m=sqrt(n);
    ll ans=0;
    ll pre=smu[m],tt;
    for (int i=1;i<=m;i++) if (mul[i]) ans+=R(n/i);
    for (ll i=m+1,j;i<=n;i=j+1){
        j=(n/(n/i));
        tt=Smu(j);
        ans+=(tt-pre)*(R(n/i));
        pre=tt;
    }
    printf("%lld\n",ans);
}
int main(){
    int T=read();
    ll mx=0;
    N=1000000000000;
    for (int i=1;i<=T;i++) 
     a[i]=Read(),mx=std::max(mx,a[i]);
    if (mx<=10000) L=10000;else L=pow(N,2.0/3.0);
    Init(L);
    for (int i=1;i<=T;i++){
        solve(a[i]);
    }
}
