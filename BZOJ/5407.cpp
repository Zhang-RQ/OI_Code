#include<bits/stdc++.h>

using namespace std;

#define int ull

typedef unsigned long long ull;

const int MAXN=2E5+10;

int n,m,du[MAXN];
unsigned char vis[MAXN];
vector<int> g[MAXN],v[2][MAXN];
pair<int,int> E[MAXN];
ull sum1[MAXN],sum2[MAXN],Ans,A,B,C,n2,Ans1,Ans2,Ans3,s[MAXN],ss[MAXN];

inline bool judge(const int &u,const int &v){return du[u]==du[v]?u<v:du[u]<du[v];}
inline ull S1(const int &L,const int &R) {return sum1[R]-(L>0?sum1[L-1]:0);}
inline ull S2(const int &L,const int &R) {return sum2[R]-(L>0?sum2[L-1]:0);}

signed main()
{
//    freopen("girls.in","r",stdin); 
//    freopen("girls.out","w",stdout);
    ios::sync_with_stdio(0);
    cin>>n>>m;--n;
    n2=(ull)n*n;
    cin>>A>>B>>C;
    for(int i=1,x,y;i<=m;i++)
    {
        cin>>x>>y;++du[x];++du[y];
        if(x>y) swap(x,y);
        v[0][y].push_back(x);
        v[1][x].push_back(y);
        E[i]=make_pair(x,y);
    }
    for(int i=0;i<=n;i++) sort(v[0][i].begin(),v[0][i].end()),sort(v[1][i].begin(),v[1][i].end());
    for(int i=1;i<=m;i++)
        if(judge(E[i].first,E[i].second))
            g[E[i].first].push_back(E[i].second);
        else 
            g[E[i].second].push_back(E[i].first);
    for(int i=1;i<=n+1;i++)
        sum1[i]=sum1[i-1]+i,
        sum2[i]=sum2[i-1]+(ull)i*i;
    for(int i=0;i<=n;i++){
      s[i]=s[i-1]+i*A;
      ss[i]=ss[i-1]+s[i-1]+B*i*i;
      Ans+=ss[i-1]+1ll*i*(i-1)/2*C*i;
  }
//    for(int i=0;i<=n-2;i++)
//        Ans+=A*i*(n*(n-i-1)-S1(i+1,n-1))+((n-i-1)*(C*n2+C*n)+S1(i+1,n-1)*(2*B*n-C)-S2(i+1,n-1)*(C+2*B))/2;
    for(int i=1;i<=m;i++)
    {
        if(E[i].second<n) Ans1+=(n-E[i].second)*(A*E[i].first+B*E[i].second)+C*S1(E[i].second+1,n);
        if(E[i].first+1<E[i].second) Ans1+=(E[i].second-E[i].first-1)*A*E[i].first+S1(E[i].first+1,E[i].second-1)*B+(E[i].second-E[i].first-1)*C*E[i].second;
        if(E[i].first>0) Ans1+=S1(0,E[i].first-1)*A+(E[i].first)*(B*E[i].first+C*E[i].second);
    }
    for(int x=0;x<=n;x++)
    {
        ull sL=0,sR=0;
        for(int X:v[0][x]) sL+=A*X;
        for(int X:v[1][x]) sR+=C*X;
        Ans2+=sL*v[1][x].size()+sR*v[0][x].size()+x*B*v[0][x].size()*v[1][x].size();
        
        int tot=v[0][x].size();
        for(int X:v[0][x])
            --tot,Ans2+=X*tot*A;
        
        tot=0;
        
        for(int X:v[0][x])
            Ans2+=X*tot*B,++tot;
            
        Ans2+=x*C*(v[0][x].size()-1)*v[0][x].size()/2;
        
        tot=v[1][x].size(); 
        for(int X:v[1][x])
            --tot,Ans2+=X*tot*B;
        
        tot=0;
        for(int X:v[1][x])
             Ans2+=X*tot*C,++tot;
        Ans2+=x*A*(v[1][x].size()-1)*v[1][x].size()/2;
    }
    for(int i=0,a,b,c;i<=n;i++)
    {
        for(int v:g[i]) vis[v]=1;
        for(int v:g[i])
            for(int k:g[v])
                if(vis[k])
                {
                    a=min(min(i,v),k);
                    c=max(max(i,v),k);
                    b=i^v^k^a^c;
                    Ans3+=(a*A+b*B+c*C);
                }
        for(int v:g[i]) vis[v]=0;
    }
    cout<<Ans<<endl<<Ans1<<endl<<Ans2<<endl<<Ans3<<endl;
//    cout<<Ans-Ans1+Ans2-Ans3<<endl;
}
