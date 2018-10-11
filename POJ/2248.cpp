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

int n,Ans[410],tmp[410],Ans_t;
int dep_lim;

void dfs(int x)
{
    if(x>dep_lim||Ans_t!=-1) return;
    if((tmp[x]<<(dep_lim-x))<n) return;
    if(tmp[x]==n)
    {
        Ans_t=x;
        for(int i=1;i<=x;i++)
            Ans[i]=tmp[i];
        return;
    }
    for(int i=1;i<=x;i++)
        {
            tmp[x+1]=tmp[i]+tmp[x];
            dfs(x+1);
        }
}

int main()
{
    while(~scanf("%d",&n)&&n)
    {
        Ans_t=-1;
        for(int i=1;i<=n;i++)
        {
            dep_lim=i;
            tmp[1]=1;dfs(1);
            if(Ans_t!=-1) break;
        }
        for(int i=1;i<=Ans_t;i++)
            printf("%d%c",Ans[i],i==Ans_t?'\n':' ');
    }
}

