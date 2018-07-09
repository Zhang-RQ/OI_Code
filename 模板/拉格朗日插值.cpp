#include<cstring>

typedef long long ll;

const int MAXN=1100;

ll f[MAXN],ans[MAXN],tmp[MAXN],m,inv[MAXN],P,g[MAXN];

inline void Lagrange_interpolation() //-> ans
{
    memset(f,0,sizeof f);memset(ans,0,sizeof ans);
    f[0]=1;
    for(int i=1;i<=m+3;i++)
    {
        for(int j=m+3;j>=1;j--)
            f[j]=f[j]*(P-i)%P,f[j]=(f[j]+f[j-1])%P;
        f[0]=f[0]*(P-i)%P;
    }
    for(int i=1;i<=m+3;i++)
    {
        memcpy(tmp,f,sizeof f);
        for(int j=0;j<=m+2;j++)
            tmp[j]=P-tmp[j]*inv[i]%P,tmp[j+1]=(tmp[j+1]-tmp[j]+P)%P;
        ll invv=1;
        for(int j=1;j<=m+3;j++)
            if(j!=i)
            {
                if(j>i) invv=(P-invv*inv[j-i]%P)%P;
                else invv=invv*inv[i-j]%P;
            }
        for(int j=0;j<=m+2;j++)
            (ans[j]+=tmp[j]*g[i]%P*invv%P)%=P;
    }
}
