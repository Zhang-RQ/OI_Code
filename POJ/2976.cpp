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
#include<iomanip>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1010;
int n,m;
double ans;
struct node{
    int a,b;
    friend bool operator < (node a,node b)
    {
        return 1.0*a.a-a.b*ans>1.0*b.a-b.b*ans;
    }
}arr[MAXN];
bool check(double mid)
{
    double tot_a=0,tot_b=0;
    ans=mid;
    sort(arr+1,arr+1+n);
    for(int i=1;i<=n-m;i++)
        tot_a+=arr[i].a,tot_b+=arr[i].b;
    return tot_a/tot_b>mid;
}
int main()
{
    while(~scanf("%d%d",&n,&m)&&(n||m))
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&arr[i].a);
        for(int i=1;i<=n;i++)
            scanf("%d",&arr[i].b);
        double L=0,R=1;
        while(fabs(L-R)>1e-7)
        {
            double mid=(L+R)/2;
            if(check(mid)) L=mid;
            else R=mid;
        }
        cout<<fixed<<setprecision(0)<<R*100<<endl;
    }
}
