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

const int MAXN=50010;
const int MAXQ=2E5+10;
const int MAXI=1000010;

int blksiz,ans,L,R;
int cnt[MAXI],a[MAXN],n,m,Ans[MAXQ];

struct Query{
    int l,r,idx;
    bool operator < (const Query &rhs) const {
        if(l/blksiz!=rhs.l/blksiz) return l/blksiz<rhs.l/blksiz;
        return r<rhs.r;
    }
}q[MAXQ];

inline void addL() {if(!(cnt[a[--L]]++)) ++ans;}
inline void delL() {if(!(--cnt[a[L++]])) --ans;}
inline void addR() {if(!(cnt[a[++R]]++)) ++ans;}
inline void delR() {if(!(--cnt[a[R--]])) --ans;}

int main()
{
    scanf("%d",&n);
    blksiz=sqrt(n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].idx=i;
    sort(q+1,q+1+m);
    L=1;R=0;
    for(int i=1;i<=m;i++)
    {
        while(L<q[i].l) delL();
        while(L>q[i].l) addL();
        while(R<q[i].r) addR();
        while(R>q[i].r) delR();
        Ans[q[i].idx]=ans;
    }
    for(int i=1;i<=m;i++) printf("%d\n",Ans[i]);
    #ifdef LOCAL
        system("pause");
    #endif
}