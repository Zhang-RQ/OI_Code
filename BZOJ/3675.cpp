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
typedef unsigned long long ull;
using namespace std;

const int MAXN=100010;
const int MAXK=210;
const double EPS=1E-10;

int n,k;
int s[MAXN];
int frm[MAXN][MAXK];
ll ans;
vector<int> o;

struct dat{
    ll x,y;
    int p;
    dat(){}
    dat(ll _x,ll _y,int _p){x=_x;y=_y;p=_p;}
};

inline double slope(const dat &lhs,const dat &rhs) {return (rhs.y-lhs.y)/(rhs.x-lhs.x+EPS);}

deque<dat> q[MAXK];

int main()
{
    scanf("%d%d",&n,&k);++k;
    for(int i=1,x;i<=n;i++) scanf("%d",&x),s[i]=s[i-1]+x;
    q[0].push_back(dat(0,0,0));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            if(q[j-1].empty()) continue;
            while(q[j-1].size()>1&&slope(*q[j-1].begin(),*(q[j-1].begin()+1))<s[i]) q[j-1].pop_front();
            dat t=q[j-1].front();
            ll f=s[i]*t.x-t.y;
            if(i==n&&j==k) ans=f;
            frm[i][j]=t.p;
            t=dat(s[i],1ll*s[i]*s[i]-f,i);
            while(q[j].size()>1&&slope(*(q[j].end()-1),t)<slope(*(q[j].end()-2),t)) q[j].pop_back();
            q[j].push_back(t);
        }
    }
    int x=n;
    for(int i=k;i>=1;i--) o.push_back(frm[x][i]),x=frm[x][i];
    reverse(o.begin(),o.end());
    printf("%lld\n",ans);
    for(int i=1;i<o.size();i++) printf("%d%c",o[i],i==o.size()-1?'\n':' ');
    #ifdef LOCAL
        system("pause");
    #endif
}