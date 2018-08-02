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

const int MAXN=1E5+10;

int n,a[MAXN];
int t[32];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
    for(int i=1,l;i<=n;i++)
    {
        l=0;
        for(int j=0;j<32;j++) if((a[i]>>j)&1) l=max(l,t[j]);
        l++;
        for(int j=0;j<32;j++) if((a[i]>>j)&1) t[j]=l;
    }
    int ans=0;
    for(int i=0;i<32;i++) ans=max(ans,t[i]);
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}