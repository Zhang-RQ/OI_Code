#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=8388608;
const int MAXM=1505;
const int P=998244353;
const int g[2]={3,(P+1)/3};

char str[MAXN];
int rev[MAXN],n,m,k,mp[MAXM][MAXM],pmp[MAXM][MAXM],mnx,mny,mxx,mxy;
ll G[2][MAXN],A[MAXN],B[MAXN],C[MAXN];
set<pair<int,int> > S;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}


ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

int init(int n)
{
    int tot=1,lg2=0;
    while(tot<=n) tot<<=1,lg2++;
    for(int i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    return tot;
}

void NTT(ll *a,int n,int f)
{
    ll *ed=a+n;
    for(int i=0;i<n;i++)
        if(i>rev[i]) swap(a[i],a[rev[i]]);
    for(int i=2;i<=n;i<<=1)
        for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
            for(int k=0;k<(i>>1);k++)
            {
                ll u=x[k],t=y[k]*G[f][1ll*MAXN/i*k]%P;
                x[k]=Add(u,t);y[k]=Sub(u,t);
            }
    if(f) for(int i=0,inv=ksm(n,P-2);i<n;i++) a[i]=a[i]*inv%P;
}

int main()
{
	G[0][0]=G[1][0]=1;
    G[0][1]=ksm(g[0],(P-1)/MAXN);G[1][1]=ksm(g[1],(P-1)/MAXN);
    for(int i=2;i<MAXN;i++) G[0][i]=G[0][i-1]*G[0][1]%P,G[1][i]=G[1][i-1]*G[1][1]%P;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		for(int j=1;j<=m;j++)
			mp[i][j]=str[j]-'0';
	}
	int nx=0,ny=0;
	scanf("%s",str+1);
	S.insert({nx,ny});
	for(int i=1;i<=k;i++)
	{
		if(str[i]=='w') --nx;
		if(str[i]=='a') --ny;
		if(str[i]=='s') ++nx;
		if(str[i]=='d') ++ny;
		S.insert({nx,ny});
		mnx=min(mnx,nx);
		mny=min(mny,ny);
		mxx=max(mxx,nx);
		mxy=max(mxy,ny);
	}
	for(auto x:S)
		pmp[x.first-mnx+1][x.second-mny+1]=1;
	int len=n*m,lenx=mxx-mnx+1,leny=mxy-mny+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			A[(i-1)*m+j-1]=mp[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			B[(i-1)*m+j-1]=pmp[i][j];
	reverse(B,B+len);
	int tot=init(2*len);
	NTT(A,tot,0);NTT(B,tot,0);
	for(int i=0;i<tot;i++) C[i]=A[i]*B[i]%P;
	NTT(C,tot,1);
	int Ans=0;
	for(int i=1;i<=n-lenx+1;i++)
		for(int j=1;j<=m-leny+1;j++)
			Ans+=!C[len+(i-1)*m+j-2];
	printf("%d\n",Ans);
}
