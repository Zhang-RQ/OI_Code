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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll a,b,k,ans;
char tmp[45];
char day[8][45]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
int main()
{
    cin>>tmp>>a>>b;
    ans=1;
    a%=7;
    for(int i=1;i<=b;i++)
        (ans*=a)%=7;
    switch (tmp[0])
    {
        case 'S':
        {
            if(tmp[1]=='a')
                k=6;
            else k=0;
            break;
        }
        case 'M': k=1;break;
        case 'T':
        {
            if(tmp[1]=='u')
                k=2;
            else k=4;
        }
        case 'W': k=3;break;
        case 'F': k=5;break;
    }
    printf("%s\n",day[(ans+k)%7]);
}
