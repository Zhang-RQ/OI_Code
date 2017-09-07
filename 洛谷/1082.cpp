#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int exgcd(int a,int b,int &x,int &y)
{
    if(!b)
    {
        x=1;
        y=0;
        return a;
    }
    int ret=exgcd(b,a%b,x,y);
    int tx=x;
    x=y;
    y=tx-a/b*y;
    return ret;
}
int cal(int a,int mod)
{
    int x,y;
    exgcd(a,mod,x,y);
    return (x+mod)%mod;
}
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d\n",cal(a,b));
}
