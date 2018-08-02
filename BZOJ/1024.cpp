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

double dfs(double x,double y,int d)
{
    if(d==1) return max(x,y)/min(x,y);
    double dx=x/d,dy=y/d,ret=100000000;
    for(int i=1;i<d;i++)
        ret=min(ret,max(dfs(dx*i,y,i),dfs(x-dx*i,y,d-i)));
    for(int i=1;i<d;i++)
        ret=min(ret,max(dfs(x,dy*i,i),dfs(x,y-dy*i,d-i)));
    return ret;
}

int main()
{
    int x,y,n;
    scanf("%d%d%d",&x,&y,&n);
    printf("%.6lf\n",dfs(x,y,n));
    #ifdef LOCAL
        system("pause");
    #endif
}