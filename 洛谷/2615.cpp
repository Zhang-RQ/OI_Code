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

int A[50][50];

int main()
{
    int n;
    scanf("%d",&n);
    int x=1;
    int y=n/2+1;
    for(int i=1;i<=n*n;i++)
    {
        A[x][y]=i;
        if(x==1&&y!=n) x=n,y++;
        else if(x!=1&&y==n) x--,y=1;
        else if(x==1&&y==n) x++;
        else if(x!=1&&y!=n)
        {
            if(!A[x-1][y+1]) x--,y++;
            else x++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            printf("%d ",A[i][j]);
        printf("\n");
    }
}
