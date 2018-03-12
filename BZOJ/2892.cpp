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
const int P=10007;
int f[P],inv[P];
void init()
{
    f[1]=1;inv[1]=1;
    for(int i=2;i<P;i++)
        f[i]=(f[i-1]*i)%P;
    for(int i=2;i<P;i++)
        inv[i]=(P-(P/i)*inv[P%i]%P)%P;
}
int Lucas(int n,int m)
{
    if(n<m) return 0;
    if(n==m||m==0) return 1;
    if(n<P&&m<P) return ((f[n]*inv[f[m]])%P*inv[f[n-m]])%P;
    return Lucas(n/P,m/P)*Lucas(n%P,m%P)%P;
}
int t,n,m;
int main()
{
    init();
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        printf("%d\n",Lucas(n,m));
    }
}
