#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;

int n,m;
int s[1000100],t[1000100],d[1000100],r[1000100];
int c[1000100];
bool check(int num)
{
    r[0]=0;
    for(int i=1;i<=n;i++)    c[i]=r[i]-r[i-1];
    for(int i=1;i<=num;i++)
    {
        c[s[i]]-=d[i];
        c[t[i]+1]+=d[i];
    }
    for(int i=1;i<=n;i++)
    {
        c[i]+=c[i-1];
        if(c[i]<0) return false;
    }
    return true;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&r[i]);
    for(int i=1;i<=m;i++)   scanf("%d%d%d",&d[i],&s[i],&t[i]);
    int l,r;
    l=1;r=m;
    int ans=12364565;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(check(mid)) l=mid+1;
        else r=mid,ans=min(ans,r);
    }
    if(ans==12364565) puts("0\n");
    else printf("-1\n%d\n",ans);
}
