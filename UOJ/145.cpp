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

const int MAXN=510;

int n;
pair<int,int> a[MAXN],b[MAXN];

void solve(int L,int R,int bit)
{
    if(L>=R||bit>(1<<29)) return;
    int l=L,r=R;
    for(int i=L;i<=R;i++)
        if(a[i].first&bit) b[l++]=a[i];
        else b[r--]=a[i];
    for(int i=L;i<=R;i++)
        a[i]=b[i];
    solve(L,l-1,bit<<1);solve(r+1,R,bit<<1);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i].first),a[i].second=i;
    solve(1,n,1);
    for(int i=1;i<=n;i++) printf("%d%c",a[i].second,i==n?'\n':' ');
    #ifdef LOCAL
        system("pause");
    #endif
}