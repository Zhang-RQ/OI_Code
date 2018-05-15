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
int n,a[11];
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        if(n&1) {puts("1");continue;}
        sort(a+1,a+1+n);
        bool flag=1;
        for(int i=1;i<=n;i+=2)
            if(a[i]!=a[i+1]) flag=0;
        puts(flag?"0":"1");
    }
}
