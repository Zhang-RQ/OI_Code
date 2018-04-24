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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=2010;
const int MAXP=2010;
ll f[MAXN][MAXP];
int AP[MAXN],BP[MAXN],AS[MAXN],BS[MAXN],MxP,T,W;
deque<int> q;
int main()
{
    scanf("%d%d%d",&T,&MxP,&W);
    for(int i=1;i<=T;i++)  scanf("%d%d%d%d",&AP[i],&BP[i],&AS[i],&BS[i]);
    memset(f,0xcf,sizeof f);
    for(int i=0;i<=T;i++) f[i][0]=0;
    for(int i=1;i<=T;i++)
    {
        for(int j=0;j<=AS[i];j++) f[i][j]=-1ll*AP[i]*j;
        for(int j=MxP;j>=0;j--) f[i][j]=max(f[i][j],f[i-1][j]);
        if(i-W-1>=0)
        {
            q.clear();
            for(int j=0;j<=MxP;j++)
            {
                while(q.size()&&j-q.front()>AS[i]) q.pop_front();
                while(q.size()&&f[i-W-1][q.back()]+1ll*AP[i]*q.back()<=f[i-W-1][j]+1ll*AP[i]*j) q.pop_back();
                q.push_back(j);
                f[i][j]=max(f[i-W-1][q.front()]-1ll*(j-q.front())*AP[i],f[i][j]);
            }
            q.clear();
            for(int j=MxP;j>=0;j--)
            {
                while(q.size()&&q.front()-j>BS[i]) q.pop_front();
                while(q.size()&&f[i-W-1][q.back()]+1ll*BP[i]*q.back()<=f[i-W-1][j]+1ll*BP[i]*j) q.pop_back();
                q.push_back(j);
                f[i][j]=max(f[i-W-1][q.front()]+1ll*(q.front()-j)*BP[i],f[i][j]);
            }
        }
    }
    ll ans=0;
    for(int i=0;i<=MxP;i++) ans=max(ans,f[T][i]);
    printf("%lld\n",ans);
}
