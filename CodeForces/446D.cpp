#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=510;
const int MAXS=110;
const int MAXM=1E5+10;
const double EPS=1E-8;

int siz,n,m,k,ban[MAXN],pos[MAXN],U[MAXM],V[MAXM],d[MAXN],id[MAXN];
vector<int> G[MAXN];

struct Mat{
    double a[MAXS][MAXS];

    Mat(){memset(a,0,sizeof a);}
    
    double* operator [](int x){return a[x];}
    const double* operator [](int x) const {return a[x];}

    Mat operator * (const Mat &rhs) const
    {
        Mat ret;
        for(int i=0;i<=siz;i++)
            for(int j=0;j<=siz;j++)
                for(int k=0;k<=siz;k++)
                    ret[i][j]+=a[i][k]*rhs[k][j];
        return ret;
    }
}trans;

Mat ksm(Mat a,ll b)
{
    Mat ret;
    for(int i=0;i<=siz;i++)
        ret[i][i]=1;
    for(;b;b>>=1,a=a*a)
        if(b&1)
            ret=ret*a;
    return ret;
}

double A[MAXN][MAXN<<1],C[MAXN],X[MAXN];

void Guass()
{
    for(int i=1;i<=n;i++)
    {
        int pos=i;
        for(int j=i+1;j<=n;j++)
            if(abs(A[j][i])>abs(A[pos][i]))
                pos=j;
        if(abs(A[pos][i])<EPS)
            throw "No Matrix Inverse";
        for(int j=1;j<=2*n;j++)
            swap(A[pos][j],A[i][j]);
        for(int j=i+1;j<=n;j++)
        {
            if(abs(A[j][i])<EPS)
                continue;
            double coef=A[j][i]/A[i][i];
            for(int k=1;k<=2*n;k++)
                A[j][k]-=A[i][k]*coef;
        }
    }
    for(int i=n;i;i--)
    {
        double inv=1.0/A[i][i];
        for(int j=1;j<=2*n;j++)
            A[i][j]=A[i][j]*inv;
        for(int j=i-1;j;j--)
        {
            double coef=A[j][i]/A[i][i];
            for(int k=1;k<=2*n;k++)
                A[j][k]-=A[i][k]*coef;
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            swap(A[i][j],A[i][j+n]);
}

void solve()
{
    for(int i=1;i<=n;i++)
        X[i]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            X[j]+=C[i]*A[j][i];
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    pos[++siz]=1;id[1]=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&ban[i]);
        if(ban[i])
            pos[++siz]=i,
            id[i]=siz;
    }
    for(int i=1;i<=n;i++)
        A[i][i]=A[i][i+n]=1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&U[i],&V[i]);
        G[U[i]].push_back(V[i]);
        G[V[i]].push_back(U[i]);
        ++d[U[i]];++d[V[i]];
    }
    for(int i=1;i<=m;i++)
    {
        int u=U[i],v=V[i];
        if(!ban[u])
            A[v][u]-=1.0/d[u];
        if(!ban[v])
            A[u][v]-=1.0/d[v];
    }
    Guass();
    for(int i=1;i<=siz;i++)
    {
        memset(C,0,sizeof C);
        int x=pos[i];
        if(x==1)
            C[1]=1,solve();
        else
        {
            C[x]=1;
            for(int v:G[x])
                C[v]+=1.0/d[x];
            solve();
        }
        double tot=1;
        for(int j=1;j<=n;j++)
            if(ban[j]&&j!=x)
                trans[i][id[j]]=X[j],tot-=X[j];
        trans[i][i]=tot;
    }
    trans[siz][0]=1;
    Mat res;
    res[0][1]=1;
    res=res*ksm(trans,k);
    printf("%.10lf\n",res[0][0]);
}
