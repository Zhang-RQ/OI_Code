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
const int MAXP=8;
const int pri[]={2,3,5,7,11,13,17,19};

int n,P;
pair<int,int> num[MAXN];
int f[1<<MAXP][1<<MAXP],g[2][1<<MAXP][1<<MAXP];

int main()
{
    scanf("%d%d",&n,&P);
    for(int i=2;i<=n;i++)
    {
        int t=i;
        for(int j=0;j<MAXP;j++)
            while(t%pri[j]==0)
            {
                t/=pri[j];
                num[i].second|=1<<j;
            }
        num[i].first=t;
    }
    f[0][0]=1;
    sort(num+2,num+1+n);
    for(int i=2;i<=n;i++)
    {
        if(i==2||num[i].first==1||num[i].first!=num[i-1].first)
        {
            memcpy(g[0],f,sizeof f);
            memcpy(g[1],f,sizeof f);
        }
        for(int s1=(1<<MAXP)-1;~s1;s1--)
            for(int s2=(1<<MAXP)-1;~s2;s2--)
            {
                if((s2&num[i].second)==0)
                    (g[0][s1|num[i].second][s2]+=g[0][s1][s2])%=P;
                if((s1&num[i].second)==0)
                    (g[1][s1][s2|num[i].second]+=g[1][s1][s2])%=P;
            }
        if(i==n||num[i].first==1||num[i].first!=num[i+1].first)
            for(int s1=(1<<MAXP)-1;~s1;s1--)
                for(int s2=(1<<MAXP)-1;~s2;s2--)
                    f[s1][s2]=((g[0][s1][s2]+g[1][s1][s2]-f[s1][s2])%P+P)%P;
    }
    int ans=0;
    for(int s1=(1<<MAXP)-1;~s1;s1--)
        for(int s2=(1<<MAXP)-1;~s2;s2--)
           if((s1&s2)==0) (ans+=f[s1][s2])%=P;
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}