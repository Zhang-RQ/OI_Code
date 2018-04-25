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
char mp[100][100];
int ps[100],vis[100],top,stk[100],n,ans,pp;
void calc()
{
    top=0;
    for(pp=0;pp<n;pp++) ps[pp]=pp,vis[pp]=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(mp[i][j]) ++vis[j];
    for(int t=0;t<5;t++)
    {
        random_shuffle(ps,ps+pp);
        for(int i=0;i<pp;i++)
        {
            int x=ps[i];
            bool ed=1;
            for(int j=0;j<n;j++) if(mp[x][j]>=vis[j]) {ed=0;break;}
            if(ed)
            {
                for(int j=0;j<n;j++) if(mp[x][j]) --vis[j];
                stk[top++]=x;
                ps[i--]=ps[--pp];
            }
        }
        if(pp<ans) ans=pp;
        if(!top) continue;
        int w=rand()%top;
        int x=ps[pp++]=stk[w];
        stk[w]=stk[top--];
        for(int i=0;i<n;i++) if(mp[x][i]) ++vis[i];
    }
}
int main()
{
    srand(1844677);
    int Cs=0;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;i++)
        {
            scanf("%s",mp[i]);
            mp[i][i]='1';
            for(int j=0;j<n;j++) mp[i][j]-='0';
        }
        ans=n;
        for(int i=0;i<200;i++) calc();
        printf("Case %d: %d\n",++Cs,ans);

    }
}
