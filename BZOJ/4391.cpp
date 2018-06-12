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
int a[MAXN],n,f[MAXN],g[MAXN];
int ans=0;
set<int> s;
set<int>::iterator it;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=(n<<1);i++) s.insert(i);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),s.erase(a[i]);
    for(int i=1;i<=n;i++)
    {
        f[i]=f[i-1];
        it=s.lower_bound(a[i]);
        if(it!=s.end()) s.erase(it),f[i]++;
    }
    s.clear();
    for(int i=1;i<=(n<<1);i++) s.insert(i);
    for(int i=1;i<=n;i++) s.erase(a[i]);
    for(int i=n;i>=1;i--)
    {
        g[i]=g[i+1];
        it=s.lower_bound(a[i]);--it;
        if(it!=s.end()) s.erase(it),g[i]++;
    }
    int ans=0;
    for(int i=0;i<=n;i++) ans=max(ans,f[i]+g[i+1]);
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}