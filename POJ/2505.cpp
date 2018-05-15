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
double n;
const double EPS=1E-15;
int main()
{
    while(~scanf("%lf",&n)&&fabs(n)>EPS)
    {
        while(n>18) n/=18;
        if(n<=9) puts("Stan wins.");
        else puts("Ollie wins.");
    }
}
