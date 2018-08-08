#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll f[20][50][2525];
int num[20],tot,Hash[2525];

ll lcm(ll a,ll b){return b?a/__gcd(a,b)*b:a;}

ll dfs(int x,int lcms,int c,bool lim)
{
    if(!x) return c%lcms==0;
    if(!lim&&~f[x][Hash[lcms]][c]) return f[x][Hash[lcms]][c];
    ll ret=0;int lm=lim?num[x]:9;
    for(int i=0;i<=lm;i++)
        ret+=dfs(x-1,lcm(lcms,i),(c*10+i)%2520,lim&&i==lm);
    if(!lim) f[x][Hash[lcms]][c]=ret;
    return ret;
}

ll solve(ll x)
{
    tot=0;
    while(x) num[++tot]=x%10,x/=10;
    return dfs(tot,1,0,1);
}

int main()
{
    memset(f,-1,sizeof f);
    int T,tmp=0;ll L,R;
    for(int i=1;i<=2520;i++) if(2520%i==0) Hash[i]=++tmp;
    for(scanf("%d",&T);T--;cin>>L>>R,cout<<solve(R)-solve(L-1)<<endl);   
}
