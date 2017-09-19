#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define FN "icow"

const int N = 1010;

int n, T, val[N];

int main()
{
    freopen(FN ".in", "r", stdin);
    freopen(FN ".out", "w", stdout);
    scanf("%d%d", &n, &T);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&val[i]);
    }
    if(n==1)
    {
        for(int i=1;i<=T;i++)
        {
            puts("1");
        }
        return 0;
    }
    for(int i=1;i<=T;i++)
    {
        int id=0;
        for(int j=1;j<=n;j++)
        {
            if(val[id]<val[j])
            {
                id=j;
            }
        }
        printf("%d\n", id);
        int w=val[id]/(n-1);
        int md=val[id]%(n-1);
        val[id]=0;
        for(int j=1;j<=n;j++)
        {
            if(j!=id)
            {
                val[j]+=w;
                if(md)
                {
                    md--;
                    val[j]++;
                }
            }
        }
    }
}
