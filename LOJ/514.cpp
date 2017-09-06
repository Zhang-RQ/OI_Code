#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int A[10010],n,m;
int ans[10010];
int x;
int main()
{
    memset(ans,0xcf,sizeof(ans));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]),A[i]+=A[i-1];
    for(x=1;x<= n;x++)
        for(int l=1,r;(r=l+x-1)<=n;l++)
            ans[x]=max(ans[x],A[r]-A[l-1]);
    for(x=n-1;x>=1;x--)
        ans[x] = max(ans[x], ans[x+1]);
    for(int i=1;i<=m;i++)
        scanf("%d",&x),printf("%d\n",ans[x]);
    return 0;
}
