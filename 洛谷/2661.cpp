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
#define MAXN 200100
using namespace std;
typedef long long ll;
int DFN[MAXN],LOW[MAXN],to[MAXN];
bool ins[MAXN];
stack<int> s;
int cnt=0;
int ans=100000;
void tarjan(int x)
{
    //printf("%d\n",x);
    LOW[x]=DFN[x]=++cnt;
    s.push(x);ins[x]=1;
    if(DFN[to[x]]==0)
    {
        tarjan(to[x]);
        LOW[x]=min(LOW[to[x]],LOW[x]);
    }else if(ins[to[x]])
        LOW[x]=min(LOW[x],DFN[to[x]]);
    if(DFN[x]==LOW[x])
    {
        int minn=0;
        ins[x]=0;
        while(s.top()!=x)
        {
            minn++;
            ins[s.top()]=0;
            s.pop();
        }
        s.pop();minn++;
        if(minn>1) ans=min(minn,ans);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&to[i]);
    for(int i=1;i<=n;i++) if(DFN[i]==0) tarjan(i);
    printf("%d\n",ans);
}
