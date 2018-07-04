#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
const int MAXN=100010;

const int P=1E9+7;

bool vis[MAXN];
int pri[MAXN],cnt,mu[MAXN],a,b,c,n,tot,du[MAXN];
ll fa[MAXN],fb[MAXN],fc[MAXN],ta[MAXN],tb[MAXN],tc[MAXN],ans;
vector<pair<int,int> > g[MAXN];

struct node{
    int u,v,w;
    node(){}
    node(int _u,int _v,int _w){u=_u;v=_v;w=_w;}
}Edge[MAXN<<4];

bool judge(int i){return du[Edge[i].u]==du[Edge[i].v]?Edge[i].u<Edge[i].v:du[Edge[i].u]<du[Edge[i].v];} //1:u->v

int gcd(int x,int y)
{
    if(!x||!y) return x|y;
    if(x<y) return gcd(x,y%x);
    else return gcd(y,x%y);
}

void sieve()
{
    mu[1]=1;
    for(int i=2;i<=MAXN-1;i++)
    {
        if(!vis[i]) pri[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*pri[j]<=MAXN-1;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) {mu[i*pri[j]]=0;break;}
            else mu[i*pri[j]]=-mu[i];
        }
    }
}

void solve()
{
    scanf("%d%d%d",&a,&b,&c);
    n=max(a,max(b,c));ans=0;
    tot=0;
    for(int i=1;i<=n;i++) g[i].clear();
    memset(fa,0,sizeof fa);
    memset(fb,0,sizeof fb);
    memset(fc,0,sizeof fc);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j+=i)
            fa[i]+=a/j,fb[i]+=b/j,fc[i]+=c/j;
    for(int i=1;i<=n;i++)
        if(mu[i]) ans=(ans+mu[i]*mu[i]*mu[i]*fa[i]*fb[i]%P*fc[i]%P+P)%P;
    for(int i=1;i<=n;i++) //gcd
        for(int j=1;j*i<=n;j++)
        {
            if(!mu[i*j]) continue;
            for(int k=1;i*j*k<=n;k++)
            {
                if(k==j||gcd(j,k)!=1||!mu[i*k]) continue;
                int x=i*j,y=i*k,LCM=i*j*k;
                ll MU=(mu[x]*mu[x]*mu[y]+P)%P;
                (ans+=MU*fa[x]%P*fb[LCM]%P*fc[LCM]%P)%=P;
                (ans+=MU*fa[LCM]%P*fb[x]%P*fc[LCM]%P)%=P;
                (ans+=MU*fa[LCM]%P*fb[LCM]%P*fc[x]%P)%=P;
                if(j>k) Edge[++tot]=node(x,y,LCM),++du[x],++du[y];
            }
        }
    for(int i=1;i<=tot;i++)
        if(judge(i)) g[Edge[i].u].push_back(make_pair(Edge[i].v,Edge[i].w));
        else g[Edge[i].v].push_back(make_pair(Edge[i].u,Edge[i].w));
    for(int i=1;i<=n;i++)
    {
        if(!mu[i]) continue;
        for(uint j=0,y,z;j<g[i].size();j++)
        {
            y=g[i][j].first;z=g[i][j].second;
            ta[y]=fa[z];tb[y]=fb[z];tc[y]=fc[z];
        }
        for(uint j=0,y,w1;j<g[i].size();j++)
        {
            y=g[i][j].first;w1=g[i][j].second;
            ll MU;
            for(uint k=0,z,w2;k<g[y].size();k++)
            {
                z=g[y][k].first;w2=g[y][k].second;
                MU=(mu[i]*mu[y]*mu[z]+P)%P;
                (ans+=MU*ta[z]%P*fb[w1]%P*fc[w2]%P)%=P;
                (ans+=MU*ta[z]%P*fb[w2]%P*fc[w1]%P)%=P;
                (ans+=MU*tb[z]%P*fa[w1]%P*fc[w2]%P)%=P;
                (ans+=MU*tb[z]%P*fa[w2]%P*fc[w1]%P)%=P;
                (ans+=MU*tc[z]%P*fa[w1]%P*fb[w2]%P)%=P;
                (ans+=MU*tc[z]%P*fa[w2]%P*fb[w1]%P)%=P;
            }
        }
        for(uint j=0,y;j<g[i].size();j++)
        {
            y=g[i][j].first;
            ta[y]=tb[y]=tc[y]=0;
        }
    }
    printf("%lld\n",ans%1000000007);
}

int main()
{
    sieve();
    int T;
    for(scanf("%d",&T);T--;solve());
}