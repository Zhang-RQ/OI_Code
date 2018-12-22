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
#include<iomanip>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=15;

int n;
double a[MAXN],L,R;

double f(double x)
{
    double ret=0,t=1;
    for(int i=0;i<=n;i++,t*=x)
        ret+=a[i]*t;
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>L>>R;
    for(int i=n;~i;i--)
        cin>>a[i];
    for(int i=1;i<=50;i++)
    {
        double mid1=(L+L+R)/3,mid2=(L+R+R)/3;
        if(f(mid1)<f(mid2)) L=mid1;
        else R=mid2;
    }
    cout<<fixed<<setprecision(5)<<L<<endl;
}