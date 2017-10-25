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
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int read()
{
    int ret=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') w=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9')
        ret=(ret<<3)+(ret<<1),ret+=ch-'0',ch=getchar();
    return ret*w;
}
int main()
{
    int t=clock();
    while(1) printf("%d\n",read());
    printf("%ld\n",clock()-t);
}
