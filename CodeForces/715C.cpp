#include<bits/stdc++.h>

using namespace std;

const int MAXN=100010;

typedef long long ll;

int n,P,siz[MAXN],mx_rt,rt;
bool vis[MAXN];ll Ans;
ll inv[MAXN],pw[MAXN];
vector<pair<int,int> > g[MAXN];
map<int,int> mp;

int get_phi(int x)
{
    int lim=sqrt(x),ret=x;
    for(int i=2;i<=lim;i++)
    {
        if(x%i==0)
        {
            ret=ret/i*(i-1);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) ret=ret/x*(x-1);
    return ret;
}

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b/=2,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

void get_rt(int x,int fa,int sz)
{
    siz[x]=1;int mx=1;
    for(auto v:g[x])
        if(!vis[v.first]&&v.first!=fa)
            get_rt(v.first,x,sz),
            siz[x]+=siz[v.first],
            mx=max(mx,siz[v.first]);
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) rt=x,mx_rt=mx;
}

void dfs1(int x,int fa,ll cur,int len)
{
    Ans+=mp[1ll*((P-cur)%P+P)%P*inv[len]%P];
    for(auto v:g[x])
        if(!vis[v.first]&&v.first!=fa)
            dfs1(v.first,x,(10*cur+v.second)%P,len+1);
}

void dfs2(int x,int fa,ll cur,int len)
{
    ++mp[cur%P];
    for(auto v:g[x])
        if(!vis[v.first]&&v.first!=fa)
            dfs2(v.first,x,(cur+v.second*pw[len]%P)%P,len+1);
}

void solve(int x)
{
    vis[x]=1;
    mp.clear();mp[0]=1;
    for(auto v:g[x])
        if(!vis[v.first])
            dfs1(v.first,x,v.second,1),
            dfs2(v.first,x,v.second,1);
    reverse(g[x].begin(),g[x].end());
    Ans+=mp[0]-1;
    mp.clear();
    for(auto v:g[x])
        if(!vis[v.first])
            dfs1(v.first,x,v.second,1),
            dfs2(v.first,x,v.second,1);
    for(auto v:g[x])
    {
        if(vis[v.first]) continue;
        mx_rt=1<<30;
        get_rt(v.first,0,siz[v.first]);
        solve(rt);
    }
}

int main()
{
    scanf("%d%d",&n,&P);
    inv[n]=ksm(ksm(10,n),get_phi(P)-1);pw[0]=1;
    for(int i=n-1;i;--i) inv[i]=inv[i+1]*10%P;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*10%P;
    for(int i=1,u,v,w;i<n;i++)
        scanf("%d%d%d",&u,&v,&w),++v,++u,g[u].push_back({v,w}),g[v].push_back({u,w});
    mx_rt=1<<30;get_rt(1,0,n);solve(rt);
    cout<<Ans<<endl;
}
