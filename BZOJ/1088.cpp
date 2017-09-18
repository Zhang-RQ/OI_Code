#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
int n,l2[10010];
int ans=0;
bool judge(bool x)
{
    int b[10010];
    memset(b,0,sizeof(b));
    if(x) b[1]=1;
    b[2]=l2[2]-b[1];
    for(int i=2;i<=n;i++) {b[i+1]=l2[i]-b[i]-b[i-1];}
    for(int i=1;i<=n;i++) if(b[i]!=0&&b[i]!=1) return 0;
    if(b[n+1]) return 0;
    return 1;
}
int main()
{
     scanf("%d",&n);
     for(int i=1;i<=n;i++)
         scanf("%d",&l2[i]);
    for(int i=0;i<=l2[1];i++)
    {
        if(judge(i))    ans++;
    }
    printf("%d\n",ans);
}
