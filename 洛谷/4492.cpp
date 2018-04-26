#include<iostream>
typedef long long ll;
ll C[2010][2010],A[2010][2010],fac[2010],ans,n,P;
int main()
{
    std::cin>>n>>P;
    fac[0]=A[1][1]=C[0][0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%P;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
    for(int i=1;i<=n;i++,A[i][i]=i%P)
        for(int j=i+1;j<=n;j++)
            A[i][j]=A[i][j-1]*j%P;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n-i+1;j++)
            (ans+=C[n-i][j-1]*fac[j]%P*fac[i]%P*(n-j+1==i?1:A[i-1][n-j-1])%P*j*(n-j)%P)%=P;
    std::cout<<ans;
}
