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
const int MAXN=500010;
const double eps=1e-6;
struct line{
    double k,b;
    int id;
    inline friend bool operator < (const line &a,const line &b)
    {
        if(a.k!=b.k) return a.k>b.k;
        return a.b>b.b;
    }
}lin[MAXN],stk[MAXN];
int n,top,ans[MAXN];
double solve(const line &a,const line &b)
{
    double x=(b.b-a.b)/(a.k-b.k);
    return x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&lin[i].k,&lin[i].b),lin[i].id=i;
    sort(lin+1,lin+1+n);
    top=0;
    for(int i=1;i<=n;i++)
    {
        if(i!=1&&fabs(lin[i].k-lin[i-1].k)<eps) continue;
        while(top>1&&solve(lin[i],stk[top-1])>=solve(stk[top],stk[top-1]))
            top--;
        stk[++top]=lin[i];
        ans[top]=lin[i].id;
    }
    sort(ans+1,ans+1+top);
    for(int i=1;i<=top;i++) printf("%d ",ans[i]);
    puts("");
}
