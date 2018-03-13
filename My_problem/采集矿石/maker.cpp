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
char get()
{
    return rand()%2+'a';
}
int main(int argc,char* argv[])
{
    srand((ull)new ull);
    int n;
    sscanf(argv[1],"%d",&n);
    for(int i=1;i<=n;i++)
        putchar(get());
    puts("");
    for(int i=1;i<=n;i++)
        printf("%d ",rand()%3+1);
    puts("");
}
