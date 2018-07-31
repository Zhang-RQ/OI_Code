#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>

typedef long long ll;
typedef long double ld;
using namespace std;

const int MAXN=5E5+10;

int n,m;
ld t[MAXN],p,ans;
vector<int> v[MAXN];

void add(int pos,ld val)
{
    for(int i=pos;i<=n;i+=i&(-i))
        t[i]+=val;
}

ld query(int pos)
{
    ld ret=0;
    for(int i=pos;i;i-=i&(-i))
        ret+=t[i];
    return ret;
}

ld ksm(ld a,int b)
{
    ld ret=1;
    for(;b;b>>=1,a*=a) if(b&1) ret*=a;
    return ret;
}

int main()
{
    scanf("%d%d",&n,&m);
    scanf("%Lf",&p);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b),v[a].push_back(b);
    for(int i=n;i;i--)
    {
        if(!v[i].size()) continue;
        ld t=p/(1-ksm(1-p,v[i].size()));
        sort(v[i].begin(),v[i].end());
        for(int j=0;j<v[i].size();j++)
            ans+=query(v[i][j]-1)*t,t*=(1-p);
        t=p/(1-ksm(1-p,v[i].size()));
        for(int j=0;j<v[i].size();j++)
            add(v[i][j],t),t*=(1-p);
    }
    printf("%.2Lf\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}