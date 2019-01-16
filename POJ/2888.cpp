#include<cstdio>
#include<cstring>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=9973;

struct Mat{
    int a[15][15];

    Mat(){memset(a,0,sizeof a);}
    
    int* operator [] (int i) {return a[i];}
    const int* operator [] (int i) const {return a[i];}

    Mat operator * (const Mat &rhs) const 
    {
        Mat ret;
        for(int i=1;i<15;i++)
            for(int j=1;j<15;j++)
                for(int k=1;k<15;k++)
                    ret[i][j]+=a[i][k]*rhs[k][j];
        for(int i=1;i<15;i++)
            for(int j=1;j<15;j++)
                ret[i][j]%=P;
        return ret;
    }
}I,trans;

int n,m,k,Ans;
int pr[40],pk[40],tot;

void exgcd(int a,int b,int &x,int &y)
{
    if(!b) return x=1,y=0,void();
    exgcd(b,a%b,y,x);y-=(a/b)*x;
}

Mat ksm(Mat a,ll b)
{
    Mat ret=I;
    for(;b;a=a*a,b>>=1) if(b&1) ret=ret*a;
    return ret;
}

void dfs(int x,int now,int ph)//ph=phi(n/now)
{
    if(x>tot)
    {
        int tAns=0;
        Mat t=ksm(trans,now);
        for(int i=1;i<=m;i++)
            tAns+=t[i][i];
        tAns%=P;
        (Ans+=1ll*tAns*ph%P)%=P;
        return;
    }
    for(int e=0,pw=1;e<=pk[x];e++,pw*=pr[x])
        dfs(x+1,now*pw,ph/(e==pk[x]?(pw/pr[x]*(pr[x]-1)):pw));
}

void solve()
{
    memset(trans.a,0,sizeof trans.a);
    Ans=0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            trans[i][j]=1;
    for(int i=1,a,b;i<=k;i++)
    {
        scanf("%d%d",&a,&b);
        trans[a][b]=trans[b][a]=0;
    }
    tot=0;int _n=n;
    for(int i=2;1ll*i*i<=n;i++)
        if(!(_n%i))
        {
            ++tot;
            pr[tot]=i;pk[tot]=0;
            while(!(_n%i)) pk[tot]++,_n/=i;
        }
    if(_n!=1) ++tot,pr[tot]=_n,pk[tot]=1;
    int Phi=n;
    for(int i=1;i<=tot;i++)
        Phi=Phi/pr[i]*(pr[i]-1);
    dfs(1,1,Phi);
    int x,y;
    exgcd(n,P,x,y);x=(x+P)%P;
    printf("%d\n",Ans*x%P);//divide n
}

int main()
{
    for(int i=1;i<15;i++) I[i][i]=1;
    int T;
    for(scanf("%d",&T);T--;solve());
}