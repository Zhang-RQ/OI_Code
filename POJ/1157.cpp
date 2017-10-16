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
#define MAX 110
int value[MAX][MAX];
int f[MAX][MAX];
int F,V;
int main()
{
    int i,j;
    scanf("%d%d",&F,&V);
    for(i=1;i<=F;i++)
    {
        for(j=1;j<=V;j++)
        {
            scanf("%d",&value[i][j]);
        }
    }
    f[1][1]=value[1][1];
    for(i=2;i<=V;i++)
    {
        if(f[1][i-1]>value[1][i])
            f[1][i]=f[1][i-1];
        else
            f[1][i]=value[1][i];
    }
    for(i=2;i<=F;i++)
        f[i][i]=f[i-1][i-1]+value[i][i];
    for(i=2;i<=F;i++){
        for(j=i+1;j<=V;j++){
            f[i][j]=f[i][j-1];
            if(f[i-1][j-1]+value[i][j]>f[i][j])
                f[i][j]=f[i-1][j-1]+value[i][j];
        }
    }
    printf("%d\n",f[F][V]);  
    return 0;
}
