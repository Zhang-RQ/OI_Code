#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
int mp[110][110];
const int INF=0x3f3f3f3f;
int main()
{
    int n,tmp,v,val;
    int ans=0,ans1;
    while(scanf("%d",&n)&&n!=0)
    {
        ans=0x3f3f3f3f;
        memset(mp,0x3f,sizeof(mp));
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&tmp);
            for(int j=1;j<=tmp;j++) scanf("%d%d",&v,&val),mp[i][v]=val;
        }
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
        for(int i=1;i<=n;i++)
        {
            tmp=-INF;
            for(int j=1;j<=n;j++) if(i!=j) tmp=max(tmp,mp[i][j]);
            if(tmp!=-INF&&tmp<ans)
            {
                ans1=i;
                ans=tmp;
            }
        }
        if(ans!=0x3f3f3f3f) printf("%d %d\n",ans1,ans);
        else printf("disjoint\n");
    }
}
